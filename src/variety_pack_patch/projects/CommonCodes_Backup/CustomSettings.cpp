#include <Kamek/kamek.hpp>
#include <customsettings.hpp>

#ifdef CUSTOMSETTINGS

void AddSettingsScreen(Scene *scene, ScreenType id){
    scene->CreateScreen(id);
    scene->CreateScreen(VS_SETTINGS);
}
kmCall(0x8062fe24, &AddSettingsScreen);

ExpandedOptionsScreen *CreateExpandedOptionsScreen(){
    return new(ExpandedOptionsScreen);
};
kmCall(0x8062453c, &CreateExpandedOptionsScreen);
kmWrite32(0x80624530,0x60000000); //nop the original new
kmWrite32(0x805fd754,0x60000000); //nop the InitControl call in the init func

void ExpandedOptionsScreen::OnInit(){
    this->InitControlGroup(5 + customButtons);
    OptionsScreen::OnInit();
    this->AddControl(this->controlGroup.controlCount - 1, &newButton, 0);

    this->newButton.InitButton("button", "OptionTopButton", "Settings", 1, 0, false);

    this->newButton.buttonId = 5;
    this->newButton.SetOnClickHandler(&this->onClick, 0);
}

void ExpandedOptionsScreen::ExpandedHandleClick(PushButton *pushButton, u32 r5){
    if (pushButton->buttonId == 5){
        this->nextScreenId = (ScreenType) 0x73;
        this->EndStateAnimate(pushButton->GetAnimationFrameSize(), 0);
    }
    else{
        this->HandleClick(pushButton, r5);
    }
}

CustomSettingsPanel::CustomSettingsPanel(u32 radioButtonsCount, u32 scrollerButtonsCount, u8 buttonsPerRow[6], u8 optionsPerScroller[6]){
    externObjectsCount = 1;
    layoutCount = radioButtonsCount + scrollerButtonsCount;
    hasBackButton = false;
    titleBmgId = 0x3FFF;
    nextScreenId = SCREEN_NONE;
    prevScreenId = OPTIONS;
    nextMenu = MENU_NONE;
    controlSources = 2;
    loadPrevMenuHandler.ptmf = (&InteractableScreen::LoadPrevMenu);
    //initThpPtmf.ptmf.vtableOffset = 0; //virtual func to be defined
    videoStartFrame = -1;
    extraControlNumber = 0;
    isLocked = false;
    onNextScreenButtonPress.subject = this;
    onNextScreenButtonPress.ptmf = (&CustomSettingsPanel::HandleNextScreenButtonPress);

    onNextScreenButtonSelect.subject = this;
    onNextScreenButtonSelect.ptmf = (&CustomSettingsPanel::OnSelectChange);

    onNextScreenButtonDeselect.subject = this;
    onNextScreenButtonDeselect.ptmf = (&CustomSettingsPanel::OnNextScreenButtonDeselect);

    onBackPress.subject = this;
    onBackPress.ptmf = (&CustomSettingsPanel::HandleBackPress);
    onStartPress.subject = this;
    onStartPress.ptmf = (&CustomSettingsPanel::HandleStartPress);

    this->screenActionController.Init(1, false);
    this->SetActionController(&screenActionController);
    this->screenActionController.SetHandler(START_PRESS, (ptmfHolder*)(&onStartPress), false, false);
    this->screenActionController.SetHandler(BACK_PRESS, (ptmfHolder*)(&onBackPress), false, false);   
    localPlayerCount = 1;
    radioCount = radioButtonsCount;
    scrollersCount = scrollerButtonsCount;
    rowButtonCount[6];
    memcpy(rowButtonCount, buttonsPerRow, sizeof(rowButtonCount));
    rowOptionCount[6];
    memcpy(rowOptionCount, optionsPerScroller, sizeof(rowOptionCount));
};

CustomSettingsPanel::~CustomSettingsPanel(){
    delete[] radioButtonControls;
    delete[] upDownControls;
    delete[] textUpDownwID;
}

void CustomSettingsPanel::OnInit(){
    this->radioButtonControls = new RadioButtonControl[this->radioCount];
    this->upDownControls =  new UpDownControl[this->scrollersCount];
    this->textUpDownwID =  new TextUpDownValueControlwID[this->scrollersCount];
 
    this->onRadioButtonChangeHandler = new(RadioButtonChangeHandler);
    this->onRadioButtonChangeHandler->onChangeHandler.subject = this;
    this->onRadioButtonChangeHandler->onChangeHandler.ptmf = static_cast<void (Screen::*)(RadioButtonControl*, u32, u32)>(&CustomSettingsPanel::HandleOnRadioButtonChange);

    this->onRadioButtonSelectHandler = new(RadioButtonSelectHandler);
    this->onRadioButtonSelectHandler->onSelectHandler.subject = this;
    this->onRadioButtonSelectHandler->onSelectHandler.ptmf = static_cast<void (Screen::*)(RadioButtonControl*, u32, u32)>(&CustomSettingsPanel::HandleOnRadioButtonSelect);

    this->onUpDownChangeHandler = new(UpDownChangeHandler);
    this->onUpDownChangeHandler->onChangeHandler.subject = this;
    this->onUpDownChangeHandler->onChangeHandler.ptmf = static_cast<void (Screen::*)(UpDownControl*, u32, u32)>(&CustomSettingsPanel::HandleOnUpDownChange);
    
    this->onUpDownClickHandler = new(UpDownClickHandler);
    this->onUpDownClickHandler->onClickHandler.subject = this;
    this->onUpDownClickHandler->onClickHandler.ptmf = static_cast<void (Screen::*)(UpDownControl*, u32)>(&CustomSettingsPanel::HandleOnUpDownClick);

    this->onUpDownElementSelectHandler = new(UpDownElementSelectHandler);
    this->onUpDownElementSelectHandler->onElementSelectHandler.subject = this;
    this->onUpDownElementSelectHandler->onElementSelectHandler.ptmf = static_cast<void (Screen::*)(UpDownControl*, u32)>(&CustomSettingsPanel::HandleOnUpDownElementSelect);

    this->textOnScrollHandler = new(UpDownDisplayedTextScrollHandler);
    this->textOnScrollHandler->onTextScrollHandler.subject = this;
    this->textOnScrollHandler->onTextScrollHandler.ptmf = static_cast<void (Screen::*)(TextUpDownValueControlTextControl*, u32)>(&CustomSettingsPanel::HandleOnTextBoxSelect);

    this->Init();
    this->SetTransitionSound(0, 0);
};

void CustomSettingsPanel::InitExternalLayout(u32 id){
    PushButton *button = new(PushButton);
    this->AddControl(this->controlCount, button, 0);
    this->controlCount++;
    button->InitButton("button", "Settings", "ButtonSAVE", this->localPlayerCount, 0, false);
    //has BMG 0x7D0 for OK
};

void CustomSettingsPanel::InitLayout(u32 id){
    ParamsHolder *params = ParamsHolder::sInstance;
    if (id < this->radioCount){
        RadioButtonControl *radioButtonControl = &this->radioButtonControls[id];
        this->AddControl(this->controlCount, radioButtonControl, 0);
        this->controlCount++;
        char *variant = "RadioRow0";
        
        const char* optionVariantsRow0[5] = {"Row0Option0", "Row0Option1", "Row0Option2", "Row0Option3", NULL};
        const char* optionVariantsRow1[5] = {"Row1Option0", "Row1Option1", "Row1Option2", "Row1Option3", NULL};
        const char* optionVariantsRow2[5] = {"Row2Option0", "Row0Option1", "Row2Option2", "Row2Option3", NULL};
        const char* optionVariantsRow3[5] = {"Row3Option0", "Row3Option1", "Row3Option2", "Row3Option3", NULL};
        const char **optionVariants = optionVariantsRow0;
        if (id == 1){
            variant = "RadioRow1";
            optionVariants = optionVariantsRow1;
        }
        else if(id == 2){
            variant = "RadioRow2";
            optionVariants = optionVariantsRow2;
        }
        else if(id == 3){
            variant = "RadioRow3";
            optionVariants = optionVariantsRow3;
        }
        radioButtonControl->InitLayout(rowButtonCount[id], params->settings.radioSetting[id], "control", "SettingsRadioBase", variant, "SettingsRadioOption", optionVariants, 1, 0, 0);
        radioButtonControl->SetOnChangeHandler(this->onRadioButtonChangeHandler);
        radioButtonControl->SetOnSelectHandler(this->onRadioButtonSelectHandler);
        radioButtonControl->id = id;
        //screen text
        //VSSettingRadioBase has BMG for left text (Class/CPU/Items etc...)
        //VSSettingRadioOption has the BMG for radio buttons
    }
    else if (id < (this->radioCount + this->scrollersCount)){
        id -= this->radioCount;
        UpDownControl *upDownControl = &this->upDownControls[id];
        this->AddControl(this->controlCount, upDownControl, 0);
        this->controlCount++;
        
        char *variant = "UpDown0";
        if (id == 1) variant = "UpDown1";

        upDownControl->InitLayout(rowOptionCount[id], params->settings.scrollSetting[id], "control", "SettingsUpDownBase", variant, "SettingsUpDownButtonR", "RightButton",
        "SettingsUpDownButtonL", "LeftButton", (UpDownDisplayedText*) &this->textUpDownwID[id], 1, 0, false, true, true);
        //edit the brctr variants if there are multiple scrollers

        upDownControl->SetOnChangeHandler(this->onUpDownChangeHandler);
        upDownControl->SetOnClickHandler(this->onUpDownClickHandler);
        upDownControl->SetOnElementSelectHandler(this->onUpDownElementSelectHandler);
        upDownControl->id = id;

        TextUpDownValueControlwID *valueControl = &this->textUpDownwID[id];

        valueControl->InitLayout("control", "SettingsUpDownValue", "Value", "SettingsUpDownText", "Text");
        valueControl->SetOnSelectHandler(this->textOnScrollHandler);
        valueControl->id = id;
    }
    return;
}

void CustomSettingsPanel::OnLoad(){
    ParamsHolder *params = ParamsHolder::sInstance;
    

    for (int i = 0; i< this->radioCount; i++){
        this->radioButtonControls[i].Init(0);
        this->radioButtonControls[i].selectedButtonID = params->settings.radioSetting[i];
        this->radioButtonControls[i].hoveredButtonID = params->settings.radioSetting[i];
    };
    for (int i = 0; i < scrollersCount; i++){
       this->upDownControls[i].currentlySelectedOption = params->settings.scrollSetting[i];
    }
    InteractableScreen::OnLoad();
    //DO STUFF WITH TEXT
    return;
}

int CustomSettingsPanel::GetStaticInstanceAddr(){
    return VSSettingsStaticAddr;
}

void CustomSettingsPanel::OnSelectChange(PushButton *button, u32 r5){
    u32 bmgId = 0;
    if (button -> buttonId != 0xFF9C) bmgId = 0x2700;
    this->bottomText->SetText(bmgId, 0);
}

void CustomSettingsPanel::LoadPrevMenuAndSaveSettings(PushButton *button){
    this->LoadPrevScreen(button);
    ParamsHolder *params = ParamsHolder::sInstance;
    params->SaveSettings();
}

void CustomSettingsPanel::HandleBackPress(){
    PushButton *okButton = this->externObjects[0];
    okButton->SelectFocus();
    this->LoadPrevMenuAndSaveSettings(okButton);
}

void CustomSettingsPanel::HandleNextScreenButtonPress(PushButton *button){
    this->LoadPrevMenuAndSaveSettings(button);
}

void CustomSettingsPanel::HandleOnRadioButtonChange(RadioButtonControl *radioButtonControl, u32 r5, u32 optionId){
    u32 id = radioButtonControl->id;
    ParamsHolder *params = ParamsHolder::sInstance;
    params->settings.radioSetting[id] = optionId;
    return;
}

void CustomSettingsPanel::HandleOnRadioButtonSelect(RadioButtonControl *radioButtonControl, u32 r5, u32 optionId){
    u32 bmgId = 0x3010 + ((radioButtonControl->id + 1) << 8) + optionId;
    this->bottomText->SetText(bmgId, 0);
    //HandleOnRadioButtonSelect__19CustomSettingsPanelFP18RadioButtonControlUiUi = 0x8085389c do stuff with bmg IDs
    return;
}

void CustomSettingsPanel::HandleOnUpDownChange(UpDownControl *upDownControl, u32 r5, u32 optionId){
    u32 id = upDownControl->id;
    ParamsHolder *params = ParamsHolder::sInstance;
    params->settings.scrollSetting[id] = optionId;
    return;
}

void CustomSettingsPanel::HandleOnUpDownClick(UpDownControl *upDownControl, u32 r5){
    PushButton *okButton = this->externObjects[0];
    okButton->SelectButton(0); //0 is the id
    //HandleOnRadioButtonSelect__19CustomSettingsPanelFP18RadioButtonControlUiUi = 0x8085389c do stuff with bmg IDs
    return;
}

void CustomSettingsPanel::HandleOnTextBoxSelect(TextUpDownValueControlTextControl *text, u32 optionId){
    TextUpDownValueControlwID *valueControl = (TextUpDownValueControlwID*) text->parentCtrl->parentControl;
    u32 bmgId = 0x4000 + ((valueControl->id + 1) << 8)+ optionId;
    text->SetText(bmgId, 0); //might need to figure out a way to pass the id
    bmgId += 0x10;
    this->bottomText->SetText(bmgId, 0);
    //TEXT HERE 80853a10
    return;
};

void CustomSettingsPanel::HandleOnUpDownElementSelect(UpDownControl *upDownControl, u32 r5){
    u32 bmgId = 0x4010 + ((upDownControl->id + 1) << 8) + upDownControl->currentlySelectedOption;
    this->bottomText->SetText(bmgId, 0);
    //upDownControl
    //0x80853988 do stuff with bmg IDs
    return;
}

void TextUpDownValueControlwID::SetMsgIDOnLoad(u32 optionId){
    TextUpDownValueControlTextControl *text = this->activeTextValueControl;
    u32 bmgId = 0x4000 + ((this->id + 1) << 8)+ optionId;
    text->SetText(bmgId, 0); //might need to figure out a way to pass the id
}

#endif