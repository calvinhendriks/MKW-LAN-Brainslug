#include <ParamsHolder.hpp>
#include <CustomCtrl.hpp>
#include <project.hpp>

CustomCtrlBuilder *CustomCtrlBuilder::sHooks = NULL;

void CreateCustomRaceCtrls(RaceScreen *raceScreen, u32 controlCount)
{
   u32 customctrlCount = CustomCtrlBuilder::Count();
   raceScreen->InitControlGroup(controlCount + customctrlCount);
   CustomCtrlBuilder::CreateCustomCtrls(raceScreen, controlCount);
   return;
}
kmCall(0x808562d0, &CreateCustomRaceCtrls);

u32 CountSOM(){
   u32 localPlayerCount = raceData->main.scenarios[0].localPlayerCount;
   MenuType menuId = menuData->curScene->menuId;
   if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) localPlayerCount+= 1;
   return localPlayerCount;
}
void CreateSOM(Screen *screen, u32 index){
   u32 localPlayerCount = raceData->main.scenarios[0].localPlayerCount;
   MenuType menuId = menuData->curScene->menuId;
   if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) localPlayerCount+= 1;
   u8 speedoType = (localPlayerCount == 3) ? 4 : localPlayerCount;
   for (int i = 0; i < localPlayerCount; i++){
      CtrlRaceSpeedo *som = new(CtrlRaceSpeedo);
      screen->AddControl(index + i, som, 0); //If 0x9 screens, in solo localplayer = 1, 
      char variant[0x20];
      snprintf(variant, 0x20, "CtrlRaceSpeedo_%1d_%1d", speedoType, i);
      som->Load(variant, i);
   }
}

u32 CountDEBUG(){
   u32 panelSetting = ParamsHolder::sInstance->settings.radioSetting[RADIO_PANEL];
   return ((panelSetting == RADIO_PANEL_LIGHT) || (panelSetting == RADIO_PANEL_FULL)) ? 1 : 0;
}
void CreateDEBUG(Screen *screen, u32 index){
      CtrlRaceDebug *debug = new(CtrlRaceDebug);
      screen->AddControl(index, debug, 0); //If 0x9 screens, in solo localplayer = 1,
      debug->Load();
}

u32 CountOFFROAD(){
   u32 panelSetting = ParamsHolder::sInstance->settings.radioSetting[RADIO_PANEL];
   return (panelSetting == RADIO_PANEL_OFFROAD) ? 1 : 0;
}
void CreateOFFROAD(Screen *screen, u32 index){
      CtrlRaceOffroad *offroad = new(CtrlRaceOffroad);
      screen->AddControl(index, offroad, 0); //If 0x9 screens, in solo localplayer = 1,
      offroad->Load();
}

u32 CountINFODISPLAY(){
   u32 gamemode = raceData->main.scenarios[0].settings.gamemode;
   if ((gamemode == MODE_VS_RACE) || (gamemode == MODE_PUBLIC_VS)|| (gamemode == MODE_PRIVATE_VS)) return 1;
   return 0;
}
void CreateINFODISPLAY(Screen *screen, u32 index){
   CtrlRaceTrackInfoDisplay *info = new(CtrlRaceTrackInfoDisplay);
   screen->AddControl(index, info, 0);
   info->Load();

}

/* SPEEDOMETER */
void CtrlRaceSpeedo::Load(char* variant, u8 id){ //blatant copy
   this->hudSlotId = id;
   ControlLoader loader(this);
   const char* anims[10] = {"eHundreds", "texture_pattern_0_9_0", NULL, "eTens", "texture_pattern_0_9_1", NULL, "eUnits", "texture_pattern_0_9_2", NULL, NULL};

   loader.Load("game_image", "speedometer", variant, anims);
   PaneGroup *paneGroup = this->animator.PaneGroupById(0);
   paneGroup->DisplayAnimation(0, 0.0f);

   paneGroup = this->animator.PaneGroupById(1);
   paneGroup->DisplayAnimation(0, 0.0f);

   paneGroup = this->animator.PaneGroupById(2);
   paneGroup->DisplayAnimation(0, 0.0f);
   return;
}

void CtrlRaceSpeedo::Init(){
   this->HudSlotColorEnabled("speed0", true);
   this->HudSlotColorEnabled("speed1", true);
   this->HudSlotColorEnabled("speed2", true);
   this->HudSlotColorEnabled("kmh", true);
   LayoutUIControl::Init();
}

void CtrlRaceSpeedo::OnUpdate(){
   this->UpdatePausePosition();
   u8 id = this->getPlayerId();
   u32 engineSpeed = (u32) (fabs((playerHolder->players[id]->pointers.playerSub10->vehicleSpeed)) + 0.5f);
   float hundreds = (float) (engineSpeed % 1000 / 100);
   float tens = (float) (engineSpeed % 100 / 10);
   float units = (float) (engineSpeed % 10 / 1);
   if (engineSpeed < 10){
      hundreds = 10.0f;
      tens = 10.0f;
   }
   else if (engineSpeed < 100) {
      hundreds = 10.0f;
   }

   PaneGroup *paneGroup = this->animator.PaneGroupById(3);
   
   paneGroup = this->animator.PaneGroupById(2); //third digit
   paneGroup->DisplayAnimation(0, units);

   paneGroup = this->animator.PaneGroupById(1); //second digit
   paneGroup->DisplayAnimation(0, tens);

   paneGroup = this->animator.PaneGroupById(0); //first digit
   paneGroup->DisplayAnimation(0, hundreds);
   return;
}


bool isDebugPanelVisible = false;
void CtrlRaceDebug::Load(){
   this->hudSlotId = 0;
   ControlLoader loader(this);
   if (ParamsHolder::sInstance->settings.radioSetting[RADIO_PANEL] == RADIO_PANEL_LIGHT){
      loader.Load("game_image", "DebugLight", "DebugLight", 0);
   }
   else loader.Load("game_image", "DebugFull", "DebugFull", 0);

   return;
}

void CtrlRaceDebug::Init(){
   LayoutUIControl::Init();
   this->isHidden = isDebugPanelVisible;
   return;
}

void CtrlRaceDebug::OnUpdate(){
   this->UpdatePausePosition();
   u8 id = this->getPlayerId();
   RaceinfoPlayer *raceinfoPlayer = raceInfo->players[id];
   RealControllerHolder *controllerHolder = (RealControllerHolder*) raceinfoPlayer->controllerHolder;
   u16 curFrameInputs = controllerHolder->inputStates[0].buttonRaw;
   u16 prevFrameInputs = controllerHolder->inputStates[1].buttonRaw;

   ControllerType type = (ControllerType) (menuData->sub.controllerInfos[0].controllerSlotAndTypeActive & 0xFF);

   s8 iterator = 0x0;

   if (CheckButtonPressed(controllerHolder, type, true, BUTTON_DPAD_UP)) iterator = 1;
   else if (CheckButtonPressed(controllerHolder, type, true, BUTTON_DPAD_DOWN)) iterator = -1;

   bool togglePanel = false;
   switch(type){
      case(CLASSIC):
         togglePanel = CheckButtonPressed(controllerHolder, type, true, BUTTON_MINUS);
         break;
      case(GCN):
         togglePanel = CheckButtonPressed(controllerHolder, type, true, BUTTON_Y);
         break;
      default:
         togglePanel = CheckButtonPressed(controllerHolder, type, true, BUTTON_MINUS);
   }

   if (togglePanel) isDebugPanelVisible = !isDebugPanelVisible;
   this->isHidden= !isDebugPanelVisible;
   if(isDebugPanelVisible){
      u8 respawn = raceinfoPlayer->respawn;
      u8 cp = raceinfoPlayer->checkpoint;
      u8 kcp = raceinfoPlayer->currentKCP;
      u8 maxkcp = raceinfoPlayer->maxKCP;
      float raceComp = raceinfoPlayer->raceCompletion;
      u8 ITPT = itemHolder->players[id].itemPoint.ITPT;
      
      PlayerPointers *pointers = &playerHolder->players[id]->pointers;
      PlayerSound *sound = pointers->playerSound;
      u16 kclFlag = sound->kclFlag;
      u16 kclVariant = sound->variant;

      wchar_t *trick = L"Can't  Trick";
      u32 collisionType = pointers->wheels[0]->wheelPhysics->hitboxGroup->collisionData.types;
      if (kclFlag == 0x7 || kclFlag == 0x6 || (collisionType & 0x8)) trick = L"Can  Trick";

      wchar_t *drop = L"Can  Drop";
      u16 billSettings = KMP::controller->itemPoint->pointArray[ITPT]->raw->setting2;
      if (billSettings & 1) drop = L"Can't Drop";

      wchar_t debugPanel[0x200];
      const wchar_t *format;
      u32 length = 0;
      if (ParamsHolder::sInstance->settings.radioSetting[RADIO_PANEL] == RADIO_PANEL_LIGHT){
         format = L"Respawn %2d\nCurCP    %3d\nCurKCP   %2d\nRace%%    %01.3f\nITPT      %3d\nKCL %02x %02x\n%ls\n%ls";
         length = swprintf(debugPanel, 0x200, format, respawn, cp, maxkcp, raceComp, ITPT, kclFlag, kclVariant, trick, drop);
      }
      else if (ParamsHolder::sInstance->settings.radioSetting[RADIO_PANEL] == RADIO_PANEL_FULL){
         Vec3 *position = &pointers->playerGraphics->playerPhysicsHolder->playerPhysics->position;
         format = L"X %5.0f\nY %5.0f\nZ %5.0f\nRespawn %2d\nCurCP    %3d\nCur/MaxKCP %2d %2d\nRace%%    %01.3f\nITPT      %3d\nKCL %02x %02x\n%ls\n%ls";
         length = swprintf(debugPanel, 0x200, format, position->x, position->y, position->z, respawn, cp, kcp, maxkcp, raceComp, ITPT, kclFlag, kclVariant, trick, drop);
      }

      for (u32 i = 0; i<length; i++){
         if (debugPanel[i] >= 0x30 && debugPanel[i] <= 0x39) debugPanel[i] += 0x2430;
      }

      ScreenText text;
      text.strings[0] = debugPanel;
      this->SetMsgId(0x600, &text);
   }
   return;
}


void CtrlRaceOffroad::Load(){
   this->hudSlotId = 0;
   ControlLoader loader(this);
   loader.Load("game_image", "OffroadInfo", "OffroadInfo", 0);
   return;
}

void CtrlRaceOffroad::Init(){
   LayoutUIControl::Init();
   u8 id = this->getPlayerId();
   this->offroadFrames = 0;
   this->minOffSpeed = playerHolder->players[id]->pointers.playerSub10->baseSpeed;
   return;
}

void CtrlRaceOffroad::OnUpdate(){
   this->UpdatePausePosition();
   u8 id = this->getPlayerId();
   PlayerPointers *pointers = &playerHolder->players[id]->pointers;
   
   PlayerSub10 *sub10 = pointers->playerSub10;
   float speedMult = sub10->kclWheelSpeedFactor * 100.0f;

   float vehicleSpd = fabs(sub10->vehicleSpeed);
   u16 kclFlag = pointers->playerSound->kclFlag;
   if ((0x2 <= kclFlag) &&(kclFlag <= 0x4) && (vehicleSpd < sub10->baseSpeed) && (speedMult < 100.0f) && (menuData->curScene->isPaused == false)){
      this->offroadFrames++;
      if (vehicleSpd < this->minOffSpeed) this->minOffSpeed = vehicleSpd;
   }

   wchar_t *format = L"Off Frames %4d\nKCLFlag Mul %-4.1f%%\nMin Off Speed %4.1f\n";
   wchar_t offroadPanel[0x100];
   u32 length = swprintf(offroadPanel, 0x100, format, this->offroadFrames, speedMult, this->minOffSpeed);
   for (u32 i = 0; i<length; i++){
      if (offroadPanel[i] >= 0x30 && offroadPanel[i] <= 0x39) offroadPanel[i] += 0x2430;
   }
   ScreenText text;
   text.strings[0] = offroadPanel;
   u32 bmgId = (this->offroadFrames > 0) ? 0x602 : 0x601;
   this->SetMsgId(bmgId, &text);
}

extern void *LeCodeID;

int asm GetLECODEID(){ //get the offset to the lecode func from a bl, add it to the bl address, and call the function to get the id
    ASM(
        stwu sp, -0x10 (sp);
        mflr r0;
        stw r0, 0x14 (sp);
        lis r3, LeCodeID@h;
        ori r3, r3, LeCodeID@l;
        lwz r4, 0 (r3);
        rlwinm r4, r4, 0, 6, 29;
        add r3, r3, r4;
        mtctr r3;
        bctrl;
        mr r3, r4;
        lwz r0, 0x14 (sp);
        mtlr r0;
        addi sp, sp, 0x10;
        blr;
    )
}

void CtrlRaceTrackInfoDisplay::Load(){
   this->hudSlotId = 0;
   ControlLoader loader(this);
   loader.Load("game_image", "CTInfo", "Info", 0);
   this->textBox_00 = this->layout.GetPaneByName("TextBox_00");
   u32 id = GetLECODEID();
   u32 bmgId = 0x7000 + id;
   this->SetMsgId(bmgId, 0);
}