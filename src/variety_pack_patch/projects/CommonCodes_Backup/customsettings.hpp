#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/SpecificScreens/Options.hpp>
#include <UI/Ctrl/Action.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <UI/Screen/SpecificScreens/VSSettings.hpp>
#include <paramsholder.hpp>

extern u32 VSSettingsStaticAddr;

class ExpandedOptionsScreen : public OptionsScreen {
public:
    ExpandedOptionsScreen(){
        this->onClick.ptmf = static_cast<void (OptionsScreen::*)(PushButton*, u32)> (&ExpandedOptionsScreen::ExpandedHandleClick);
    }
    virtual void OnInit();
    void ExpandedHandleClick(PushButton *pushButton, u32 r5);

    PushButton newButton;
};

class TextUpDownValueControlwID : public TextUpDownValueControl{
public:
    TextUpDownValueControlwID(){};
    virtual void SetMsgIDOnLoad(u32 optionId); //this is needed because usually the bottom message does not vary while scrolling
    u32 id; //the onScroll handler doesn't pass the ID
};

class CustomSettingsPanel : public InteractableScreen {
public:
    CustomSettingsPanel(u32 radioCount, u32 scrollersCount, u8 buttonsPerRow[6], u8 optionsPerScroller[6]);
    virtual ~CustomSettingsPanel();
    virtual void OnInit(); //To be defined
    virtual void ClearInstance(); //80853a8c

    virtual void OnLoad(); //8085354c TO BE DEFINED
    
    virtual void AfterChildUpdate(); //80853650

    virtual int GetStaticInstanceAddr(); //80853bd8
    
    virtual void OnSelectChange(PushButton  *button, u32 r5); //80853684

    virtual int GetLocalPlayerCount(); //80853aa4
    virtual int GetUnk6C0(); //80853a9c
    virtual ScreenActionController GetScreenActionController(); //offset 0x70

    virtual void ResetSelection(u32 buttonId); //808375f0
    virtual void SetSelection(u32 buttonId); //8083752c

    virtual void Unk_0x7C(); //just a blr
    virtual void OnActionsLoaded(); //808372e8
   
    virtual void InitExternalLayout(u32 id); //0x84 80853028
    virtual void InitLayout(u32 id); //0x88 TO BE DEFINED 808530b8
    virtual void InitExternalObject(PushButton *pushButton); //80853aac 0x8C
    virtual ScreenText GetScreenText(); //808372e0 0x90
    virtual void InitVideos(); //808387f8 0x94
    
    virtual void OnNextScreenButtonDeselect(); //808536b0

    void HandleNextScreenButtonPress(PushButton *pushButton); //80853654
    void HandleBackPress(); //808536b4
    void HandleStartPress(); //80838b14

    void HandleOnRadioButtonChange(RadioButtonControl *radioButtonControl, u32 r5, u32 optionId);
    void HandleOnRadioButtonSelect(RadioButtonControl *radioButtonControl, u32 r5, u32 optionId);

    void HandleOnUpDownChange(UpDownControl *upDownControl, u32 r5, u32 optionId);
    void HandleOnUpDownClick(UpDownControl *upDownControl, u32 r5);
    void HandleOnUpDownElementSelect(UpDownControl *upDownControl, u32 r5);

    void HandleOnTextBoxSelect(TextUpDownValueControlTextControl *text, u32 optionId);
    void LoadPrevMenuAndSaveSettings(PushButton *button);

    ScreenActionController screenActionController;
    u32 controlCount; //0x654
    PtmfHolder_1A<CustomSettingsPanel, void, PushButton*> onNextScreenButtonPress; //0x658 vtable 808bd18c 80853654
    PtmfHolder_2A<CustomSettingsPanel, void, PushButton*, u32> onNextScreenButtonSelect; //0x66C vtable 808bd18c virtual off 0x64
    PtmfHolder_0A<CustomSettingsPanel, void> onNextScreenButtonDeselect; //0x680 vtable 808bd18c 808536b0
    PtmfHolder_0A<CustomSettingsPanel, void> onBackPress; //0x694 vtable 808bd18c 808536b4
    PtmfHolder_0A<CustomSettingsPanel, void> onStartPress; //0x6A8 vtable 808bd18c virtual off 0x7C
    u32 localPlayerCount;
    u32 unknown_0x6C0;

    RadioButtonControl *radioButtonControls;
    RadioButtonChangeHandler *onRadioButtonChangeHandler;
    RadioButtonSelectHandler *onRadioButtonSelectHandler;
    u32 radioCount;
    UpDownControl *upDownControls;
    UpDownChangeHandler *onUpDownChangeHandler; //0x1E00 //when you scroll
    UpDownClickHandler *onUpDownClickHandler; //0x1E04
    UpDownElementSelectHandler *onUpDownElementSelectHandler; //0x1E08
    TextUpDownValueControlwID *textUpDownwID; //0x1984
    UpDownDisplayedTextScrollHandler *textOnScrollHandler; //when you scroll
    u32 scrollersCount;

    u8 rowButtonCount[6];
    u8 rowOptionCount[6];
};
