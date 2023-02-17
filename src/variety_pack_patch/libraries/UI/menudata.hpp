/*
MenuData is the class that holds the information about the current displayed Menu.
Documentation:
kHacker35000vr
Melg
People
*/

#pragma once
#include <Kamek/kamek.hpp>
#include <Input/inputdata.hpp>
#include <Misc/Mii.hpp>

class Screen;
class ControllerHolder;

typedef enum ControllerType{
    WHEEL=0x11,
    NUNCHUCK=0x12,
    CLASSIC=0x13,
    GCN=0x24
};

typedef enum GhostType {
    BEST_TIME=0x1,
    CONTINENTAL_RECORD=0x2,
    WORLD_RECORD=0x2,
    FLAG_GHOST=0x4,
    GHOST_RACE=0x6,
    EASY_STAFF_GHOST=0x25,
    EXPERT_STAFF_GHOST=0x26
};

typedef enum MenuCategory {
    CATEGORY_ACTION=0x0,
    CATEGORY_MENU=0x1,
    CATEGORY_GAMEPLAY=0x2,
    CATEGORY_TEST=0x3,
    CATEGORY_ONLINE_MENU=0x4,
    CATEGORY_UNK5=0x5,
    CATEGORY_UNK6=0x6,
    CATEGORY_UNK7=0x7,
    CATEGORY_UNK8=0x8,
    CATEGORY_UNK9=0x9,
    CATEGORY_UNK10=0xa,
    CATEGORY_UNK11=0xb
};

typedef enum MenuState {
    NO_TRANSITION=0x0,
    SET_TRANSITION=0x1,
    SCREEN_DISABLED=0x2,
    MENU_ENDTRANSITION=0x3,
    SCREEN_ENDTRANSITION=0x4
};

typedef enum ScreenType {
SCREEN_NONE                                            =0xFFFFFFFF,
EMPTY                                                  =0x00,
ESRB_NOTICE                                            =0x01,
HZ60_SUGGESTION                                        =0x02,
DATA_CORRUPT                                           =0x03,
CANT_SAVE                                              =0x04,
SYSTEM_MEMORY_CORRUPT                                  =0x05,
MII_DATA_CORRUPT                                       =0x06,
GRAND_PRIX_PAN_OVERLAY                                 =0x07,
VS_PAN_OVERLAY                                         =0x08,
BATTLE_PAN_OVERLAY                                     =0x09,
MISSION_PAN_OVERLAY                                    =0x0A,
TOURNAMENT_PAN_OVERLAY                                 =0x0B,
GRAND_PRIX_INTERFACE                                   =0x0C,
TIME_TRIAL_INTERFACE                                   =0x0D,
P1_VS_RACE_INTERFACE                                   =0x0E,
P2_VS_RACE_INTERFACE                                   =0x0F,
P3_VS_RACE_INTERFACE                                   =0x10,
P4_VS_RACE_INTERFACE                                   =0x11,
P1_BATTLE_INTERFACE                                    =0x12,
P2_BATTLE_INTERFACE                                    =0x13,
P3_BATTLE_INTERFACE                                    =0x14,
P4_BATTLE_INTERFACE                                    =0x15,
MISSION_AND_TOURNAMENT_INTERFACE                       =0x16,
GRAND_PRIX_PAUSE_MENU                                  =0x17,
VS_RACE_PAUSE_MENU                                     =0x18,
TIME_TRIAL_PAUSE_MENU                                  =0x19,
BATTLE_PAUSE_MENU                                      =0x1A,
TOURNAMENT_PAUSE_MENU                                  =0x1B,
GHOST_RACE_PAUSE_MENU                                  =0x1C,
ABANDON_GHOST_RACE                                     =0x1D,
QUIT_GHOST_RACE                                        =0x1E,
GHOST_REPLAY_PAUSE_MENU                                =0x1F,
GRAND_PRIX_END_SCREEN_NEXT_RACE_WATCH_REPLAY_QUIT      =0x20,
TIME_TRIAL_END_SCREEN_RETRY_CHANGE_COURSE_ETC          =0x21,
VS_RACE_END_SCREEN_NEXT_RACE_QUIT                      =0x22,
BATTLE_END_SCREEN_NEXT_BATTLE_QUIT                     =0x23,
BATTLE_END_SCREEN_NEXT_ONLY_TO_FINAL_RESULTS           =0x24,
MISSION_END_SCREEN_RETRY_CHOOSE_MISSION_QUIT_UNUSED    =0x25,
TOURNAMENT_END_SCREEN                                  =0x26,
GHOST_RACE_END_SCREEN_NEXTQUIT                         =0x27,
GO_TO_FRIEND_ROSTER                                    =0x28,
YOU_BEAT_YOUR_FRIEND_RECORD_SEND_YOUR_GHOST            =0x29,
SEND_TOURNEY_RECORD                                    =0x2A,
CHECK_RANKINGS                                         =0x2B,
ARE_YOU_SURE_YOU_WANT_TO_QUIT                          =0x2C,
SPLITS_AFTER_TT                                        =0x2D,
LEADERBOARD_AFTER_TT                                   =0x2E,
GPVS_SCORE_UPDATE_SCREEN                               =0x2F,
GPVS_SCORE_OVERALL_SCREEN                              =0x30,
ONLINE_RACE_POINT_UPDATE_SCREEN                        =0x31,
TEAM_VS_POINT_OVERALL_SCREEN                           =0x32,
BATTLE_POINT_UPDATE_SCREEN                             =0x33,
BATTLE_POINT_OVERALL_SCREEN                            =0x34,
COMPETITION_PERSONAL_LEADERBOARD                       =0x35,
GRAND_PRIX_REPLAY_INTERFACE                            =0x36,
GHOST_RACE_INTERFACE                                   =0x37,
GRAND_PRIX_REPLAY_PAUSE                                =0x38,
TT_IMMEDIATE_REPLAY_PAUSE                              =0x39,
SUPPORTING_PANEL_PRESENT_IN_MANY_MODES_INRACE          =0x3A,
PROBABLY_AWARD_INTERFACE_UNTESTED                      =0x3B,
PROBABLY_CONGRATS_SCREEN_UNTESTED                      =0x3C,
CREDITS_VS_INTERFACE_UNTESTED                          =0x3D,
CREDITS_LATTER_INTERFACE_UNTESTED                      =0x3E,
CONGRATS_AFTER_CREDITS                                 =0x3F,
WIFI_RACE_INTERFACE                                    =0x40,
P2_WIFI_RACE_INTERFACE                                 =0x41,
WIFI_FRIEND_ROOM_RACE_INTERFACE                        =0x42,
WIFI_FRIEND_ROOM_TEAM_RACE_INTERFACE                   =0x43,
CONGRATUATIONS_AT_END_OF_FRIEND_ROOM_UNTESTED          =0x44,
DUMMY_SEEMS_TO_IMMEDIATELY_LOAD_0X46                   =0x45,
ONLINE_RACE_END_NEXT_RACE_QUIT_FRIEND_ROSTER           =0x46,
QUIT_ONLINE_RACE                                       =0x47,
END_OF_ONLINE_RACE_PLEASE_WAIT_TEXT                    =0x48,
LIVE_VS_VIEW_INTERFACE                                 =0x49,
LIVE_BATTLE_VIEW_INTERFACE_UNTESTED                    =0x4A,
START_GAME_OKAY                                        =0x4B,
TEXT_BOX_WITH_SPINNER                                  =0x4C,
DRIFT_EXPLANATION_MESSAGE_BOX                          =0x4D,
VOTERANDOM_MESSAGE_BOX                                 =0x4E,
READING_GHOST_DATASCREEN_WITH_TEXT__SPINNER            =0x4F,
CONNECTING_TO_NINTENDO_WFC                             =0x50,
GENERIC_TEXT_BOX_FULL_SCREEN_PRESS_A                   =0x51,
TEXT_BOX_WITH_ONE_PROMPT_MULTIPLE_USES                 =0x52,
POST_PHOTO_TO_WII_MESSAGE_BOARD                        =0x53,
BEHIND_MAIN_MENU                                       =0x54,
DUMMY_MAYBE_NOT_LOW_BATTERY_GOES_TO_5A                 =0x55,
LOW_BATTERY_NOTIFICATION                               =0x56,
TITLE_SCREEN                                           =0x57,
BEHIND_MAIN_MENU2                                      =0x58,
OPENING_MOVIE                                          =0x59,
MAIN_MENU                                              =0x5A,
BEHIND_UNLOCKS                                         =0x5B,
FLAG_BACKGROUND                                        =0x5C,
BEHIND_DISCONNECTSOPTIONS                              =0x5D,
TOP_MENU_OVERLAY                                       =0x5E,
BLINKING_PRESS_A                                       =0x5F,
SELECT_MII                                             =0x60,
ACTIVE_CONTROLLER_DISPLAY                              =0x61,
PLAYER_CONTROLLER_OPT_IN                               =0x62,
PAIR_WII_REMOTES                                       =0x63,
PLAYER_CONTROLLER_OPT_IN_COMPLETE_OKCHANGE             =0x64,
LICENSE_SELECT                                         =0x65,
MII_CHANGED                                            =0x66,
LICENSE_SETTINGS                                       =0x67,
ERASE_LICENSE                                          =0x68,
SINGLE_PLAYER_MENU                                     =0x69,
GRAND_PRIX_CLASS_SELECT                                =0x6A,
CHARACTER_SELECT                                       =0x6B,
VEHICLE_SELECT                                         =0x6C,
DRIFT_SELECT                                           =0x6D,
CUP_SELECT                                             =0x6E,
COURSE_SELECT_SUB_SCREEN                               =0x6F,
SELECT_GHOST                                           =0x70,
SELECT_GHOST2                                          =0x71,
SELECT_SOLOTEAM_VS                                     =0x72,
VS_SETTINGS                                            =0x73,
TEAMS_OVERVIEW                                         =0x74,
SELECT_BATTLE_MODE                                     =0x75,
SELECT_VEHICLE_BATTLE                                  =0x76,
SELECT_BATTLE_RULES                                    =0x77,
SELECT_BATTLE_CUP                                      =0x78,
SELECT_BATTLE_COURSE                                   =0x79,
MISSION_LEVEL_SELECT_UNUSED                            =0x7A,
MISSION_SELECT_SUB_SCREEN                              =0x7B,
MISSION_INFORMATION_PROMPT                             =0x7C,
DRIFT_SELECT_WITH_ONE_OPTION                           =0x7D,
MISSION_TUTORIAL                                       =0x7E,
PRESENT_ON_SINGLE_PLAYER_MENUS                         =0x7F,
MULTIPLAYER_MENU_VSBT                                  =0x80,
MULTIPLAYER_VEHICLE_SELECT                             =0x81,
MULTIPLAYER_DRIFT_SELECT                               =0x82,
MULTIPLAYER_TEAM_SELECT                                =0x83,
PART_OF_CONNECTING                                     =0x84,
WFC_FIRST_PLAY                                         =0x85,
ALLOW_DATA_TO_BE_SENT                                  =0x86,
DISCONNECTS_YOU                                        =0x87,
SEEMS_TO_DRAW_BEHIND_ONLINE_RACES_PANEL_2              =0x88,
ERROR_CONNECTING_TO_WFC                                =0x89,
DUMMY_SEEMS_TO_REDIRECT_TO_0X52                        =0x8A,
WFC_MENU                                               =0x8B,
WFC_VSBATTLE_SELECT                                    =0x8C,
FRIENDS_MENU                                           =0x8D,
FRIENDS_MENU_MARIO_KART_CHANNEL                        =0x8E,
GLOBAL_SEARCH_MANAGER_DOESNT_RENDER                    =0x8F,
TIMER                                                  =0x90,
PLAYER_LIST_VR_SCREEN                                  =0x91,
COURSESTAGE_VOTES                                      =0x92,
PRESENT_IN_LIVE_VIEW                                   =0x93,
PRESENT_IN_ONLINE_RACE                                 =0x94,
PRESENT_IN_ONLINE_MENUS                                =0x95,
FRIEND_ROSTER                                          =0x96,
NOT_FRIENDS_YET                                        =0x97,
REMOVE_FRIEND_CODE                                     =0x98,
REMOVING_FRIEND_CODE                                   =0x99,
SEEMS_TO_PREPARE_THE_FRIENDS_LIST                      =0x9A,
FRIEND_ROOM_WAITING_TEXT                               =0x9B,
FRIEND_ROOM_MANAGER_DOESNT_RENDER                      =0x9C,
FRIEND_ROOM                                            =0x9D,
FRIEND_ROOM_MESSAGES                                   =0x9E,
MARIO_KART_CHANNEL                                     =0xA2,
RANKINGS_MENU                                          =0xA3,
CHANNEL_GHOSTS_SCREEN                                  =0xA4,
DUMMY_LOADS_0XA6                                       =0xA5,
ENTER_FC                                               =0xA6,
GHOST_LIST_MANAGER                                     =0xA7,
MARIO_KART_CHANNEL_GHOST_HISTOGRAM_SCREEN              =0xA8,
MARIO_KART_CHANNEL_BEHIND_0XAD                         =0xAC,
MARIO_KART_CHANNEL_WITH_A_SELECTED_GHOST_CHALLENGEWATCH=0xAD,
RESIDES_BEHIND_0X4F_LOADS_0XB4                         =0xB3,
MARIO_KART_CHANNEL_DOWNLOADED_GHOST_LIST               =0xB4,
MARIO_KART_CHANNEL_ERASE_GHOST                         =0xB5,
COMPETITION_FOR_WII_WHEELS_ONLY                        =0xBA,
OPTIONS                                                =0xC0,
NINTENDO_WIFI_CONNECTION_OPTIONS                       =0xC1,
INFORMATION_BOX_WITH_NEXT_CAN_CHAIN_TO_SELF            =0xC2,
INFORMATION_BOX_WITH_2_BUTTONS_PROMPT                  =0xC3,
INFORMATION_BOX_WITH_3_PROMPTS_                        =0xC4,
RETURN_TO_SYSTEM_MENU_TO_SET_REGION                    =0xC5,
FLAGREGION_DISPLAY                                     =0xC6,
LARGE_INFO_BOX_WITH_SPINNER                            =0xC7,
LARGE_INFO_BOX_WITH_A_PROMPT                           =0xC8,
INFO_BOX_WITH_OK_PROMPT                                =0xC9,
ADD_MARIO_KART_CHANNEL                                 =0xCA,
ADD_MARIO_KART_CHANNEL_PROMPT                          =0xCB,
DRAWS_BENEATH_OPTIONS_MENU                             =0xCC,
OVERALL_RECORDS                                        =0xCE,
FAVOURITES                                             =0xCF,
FRIEND_RECORDS                                         =0xD0,
WFC_RECORDS                                            =0xD1,
OTHER_RECORDS                                          =0xD2                 
};


typedef enum MenuType {
    POWER_OFF_WII=0x0,
    RETURN_TO_WII_MENU_1=0x4,
    RETURN_TO_WII_MENU_2=0x5,
    TEST_6=0x6,
    TEST_7=0x7,
    TEST_8=0x8,
    TEST_9=0x9,
    TEST_A=0xa,
    TEST_B=0xb,
    TEST_C=0xc,
    TEST_D=0xd,
    TEST_E=0xe,
    TEST_F=0xf,
    CREATE_NEW_SAVE=0x10,
    CORRUPTED_SAVE=0x11,
    COUNTRY_CHANGED=0x12,
    GAME_CANNOT_BE_SAVED=0x13,
    CANNOT_ACCESS_SYSTEM_MEMORY=0x14,
    CANNOT_ACCESS_MII_DATA=0x15,
    ESRB_NOTICE_MENU=0x16,
    RECOMMEND_60HZ_1=0x17,
    RECOMMEND_60HZ_2=0x18,
    GRAND_PRIX_PANORAMA=0x19,
    VS_RACE_PANORAMA=0x1a,
    BALLOON_BATTLE_PANORAMA=0x1b,
    MISSION_BOSS_PANORAMA=0x1c,
    COMPETITON_BOSS_PANORAMA=0x1d,
    GRAND_PRIX_GAMEPLAY=0x1e,
    TIME_TRIAL_GAMEPLAY=0x1f,
    P1_VS_RACE_GAMEPLAY=0x20,
    P2_VS_RACE_GAMEPLAY=0x21,
    P3_VS_RACE_GAMEPLAY=0x22,
    P4_VS_RACE_GAMEPLAY=0x23,
    P1_TEAM_VS_RACE_GAMEPLAY=0x24,
    P2_TEAM_VS_RACE_GAMEPLAY=0x25,
    P3_TEAM_VS_RACE_GAMEPLAY=0x26,
    P4_TEAM_VS_RACE_GAMEPLAY=0x27,
    P1_BATTLE_GAMEPLAY=0x28,
    P2_BATTLE_GAMEPLAY=0x29,
    P3_BATTLE_GAMEPLAY=0x2a,
    P4_BATTLE_GAMEPLAY=0x2b,
    MISSION_MODE_GAMEPLAY=0x2c,
    TOURNAMENT_GAMEPLAY=0x2d,
    GRAND_PRIX_REPLAY=0x2e,
    TIME_TRIAL_REPLAY=0x2f,
    GHOST_RACE_GAMEPLAY_1=0x30,
    GHOST_RACE_GAMEPLAY_2=0x31,
    WATCH_GHOST_FROM_CHANNEL=0x32,
    WATCH_GHOST_FROM_DOWNLOADS=0x33,
    WATCH_GHOST_FROM_MENU=0x34,
    GRAND_PRIX_AWARD=0x35,
    VS_RACE_AWARD=0x36,
    AWARD_37=0x37,
    AWARD_38=0x38,
    ENDING_NORMAL_A=0x39,
    ENDING_TRUE_A=0x3a,
    ENDING_NORMAL_B=0x3b,
    ENDING_TRUE_B=0x3c,
    CONGRATULATIONS=0x3d,
    CONGRATULATIONS_COMPLETE=0x3e,
    MAIN_MENU_FROM_BOOT=0x3f,
    MAIN_MENU_FROM_RESET=0x40,
    MAIN_MENU_FROM_MENU=0x41,
    MAIN_MENU_FROM_NEW_LICENSE=0x42,
    MAIN_MENU_FROM_LICENSE_43=0x43,
    DEMO=0x44,
    MII_SELECT_1=0x45,
    MII_SELECT_2=0x46,
    LICENSE_SETTINGS_MENU=0x47,
    SINGLE_PLAYER_FROM_MENU=0x48,
    SINGLE_PLAYER_TT_CHANGE_CHARA=0x49,
    SINGLE_PLAYER_TT_CHANGE_COURSE=0x4a,
    SINGLE_PLAYER_VS_NEXT_RACE=0x4b,
    SINGLE_PLAYER_BT_NEXT_BATTLE=0x4c,
    SINGLE_PLAYER_MR_CHOOSE_MISSION=0x4d,
    SINGLE_PLAYER_CHAN_RACE_GHOST=0x4e,
    SINGLE_PLAYER_LB_RACE_GHOST=0x4f,
    SINGLE_PLAYER_LIST_RACE_GHOST=0x50,
    SEND_GHOST_TO_FRIEND=0x51,
    RACE_GHOST_FROM_CHAN_BOOT=0x52,
    WATCH_REPLAY_FROM_CHAN_BOOT=0x53,
    LOCAL_MULTIPLAYER=0x54,
    P1_WIFI=0x55,
    P1_WIFI_GLOBE_DISCONNECT=0x56,
    P1_WIFI_FROM_FIND_FRIEND=0x57,
    P1_WIFI_VS_VOTING=0x58,
    P1_WIFI_BATTLE_VOTING=0x59,
    P2_WIFI_SELECT_MII=0x5a,
    P2_WIFI=0x5b,
    P2_WIFI_GLOBE_DISCONNECT=0x5c,
    UNKNOWN_5D=0x5d,
    P2_WIFI_VS_VOTING=0x5e,
    P2_WIFI_BATTLE_VOTING=0x5f,
    P1_WIFI_FRIEND_ROOM_VS_VOTING=0x60,
    P1_WIFI_FRIEND_ROOM_TEAM_VS_VOTING=0x61,
    P1_WIFI_FRIEND_ROOM_BALLOON_VOTING=0x62,
    P1_WIFI_FRIEND_ROOM_COIN_VOTING=0x63,
    P2_WIFI_FRIEND_ROOM_VS_VOTING=0x64,
    P2_WIFI_FRIEND_ROOM_TEAM_VS_VOTING=0x65,
    P2_WIFI_FRIEND_ROOM_BALLOON_VOTING=0x66,
    P2_WIFI_FRIEND_ROOM_COIN_VOTING=0x67,
    P1_WIFI_VS_GAMEPLAY=0x68,
    P2_WIFI_VS_GAMEPLAY=0x69,
    P1_WIFI_VS_LIVE_VIEW=0x6a,
    P2_WIFI_VS_LIVE_VIEW=0x6b,
    P1_WIFI_BT_GAMEPLAY=0x6c,
    P2_WIFI_BT_GAMEPLAY=0x6d,
    P1_WIFI_BT_LIVE_VIEW=0x6e,
    P2_WIFI_BT_LIVE_VIEW=0x6f,
    P1_WIFI_FRIEND_VS_GAMEPLAY=0x70,
    P1_WIFI_FRIEND_TEAM_VS_GAMEPLAY=0x71,
    P1_WIFI_FRIEND_BALLOON_BT_GAMEPLAY=0x72,
    P1_WIFI_FRIEND_COIN_BT_GAMEPLAY=0x73,
    P2_WIFI_FRIEND_VS_GAMEPLAY=0x74,
    P2_WIFI_FRIEND_TEAM_VS_GAMEPLAY=0x75,
    P2_WIFI_FRIEND_BALLOON_BT_GAMEPLAY=0x76,
    P2_WIFI_FRIEND_COIN_BT_GAMEPLAY=0x77,
    WIFI_DISCONNECT_ERROR=0x78,
    WIFI_DISCONNECT_GENERAL=0x79,
    CHANNEL_FROM_MENU=0x7a,
    CHANNEL_FROM_CHECK_RANKINGS=0x7b,
    CHANNEL_FROM_DOWNLOADS=0x7c,
    TIME_TRIAL_LEADERBOARDS=0x7d,
    TOURNAMENT_LEADERBOARDS=0x7e,
    GHOST_RACE_WITH_DATA=0x7f,
    GHOST_RACE_WITHOUT_DATA=0x80,
    GHOST_RACE_NEXT_RACE=0x81,
    DOWNLOADED_GHOST_DATA=0x82,
    FRIENDS_LIST_1=0x83,
    FRIENDS_LIST_2=0x84,
    TOURNAMENT=0x85,
    TOURNAMENT_CHANGE_CHARA=0x86,
    TOURNAMENT_SUBMIT_RECORD=0x87,
    TOURNAMENT_WII_WHEEL_ONLY=0x88,
    TOURNAMENT_WII_WHEEL_ONLY_BOSSES=0x89,
    INVITE_FRIENDS_FROM_MSG_BOARD=0x8a,
    DOWNLOAD_LATEST_DATA=0x8b,
    OPTIONS_MENU=0x8c,
    INSTALL_CHANNEL=0x8d,
    CHOOSE_REGION=0x8e,
    JOIN_MESSAGE_SERVICE=0x8f,
    MSG_UNLOCK_ORANGE1=0x90,
    MSG_UNLOCK_ORANGE2=0x91,
    MSG_UNLOCK_BLUE=0x92,
    MSG_UNLOCK_YELLOW=0x93,
    BROKEN_MISSION_MODE_MENU=0x94,
    MENU_NONE=0xFFFFFFFF
};

struct ControllerInfo{
    u32 controllerSlotAndType;
    u32 controllerSlotAndTypeActive;
    u32 wantsController;
    ControllerHolder * controllerHolder; // see inputdata.h
}; // datasize 0x10


struct Scene {
public:
    Scene(); //0x80621d0c
    ~Scene(); //0x80621d84
    void Init(MenuType menuId); //0x80621e00
    void BuildScreens(MenuType menuId); //0x8062c3a4
    void CreateScreen(ScreenType screenId); //0x80622d08
    Screen CreateScreenById(u32 screenId); //0x80623390
    MenuType menuId;
    u32 openingAnimIdx;
    Screen *screens[0xD2]; //https://wiki.tockdom.com/wiki/List_of_Identifiers#Screen_Identifiers
    Screen *activeScreens[11];
    u32 layerCount; //0x37C
    void *controllerDisconnectedScreen;
    void *cursor;
    bool hideCursor; /* ? */
    bool pauseGame;
    bool controllerDcPause;
    bool isPaused;
	u8 unknown_0x38C[0x390 - 0x38C];

	u8 drawInfo[0x54];
    u32 * layoutHeap;
    u32 * *arcResourceAccessor;
    void * *iconLayout;
    float pointerTranslationBoxSize[2];
    float pointerScale[2];
    u32 videoPlayer;
    u32 friendList;

};//Total Size 0x408

struct MenuData98{
public:
	u8 unknown_0x0[0x60];
	u32 vsRaceLimit;
	u32 raceCount;
	u8 unknown_0x68[0x124 - 0x68];
	u32 humanPlayerCount;
	u8 unknown_0x128[0x12c - 0x128];
    CharacterId characters[4];
    VehicleId vehicles[4];
	u32 lastSelectedCourse;
	u32 lastSelectedStage;
	u8 unknown_0x154[0x188 - 0x154];
    MiiGroup playerMiis;
	s32 selCharacter;
	s32 selVehicle;
	s8 starRank;
	u8 unknown_0x229[0x238 - 0x229];
    MiiGroup localPlayerMiis;
	u32 currentRaceNumber;
	u8 unknown_0x2D4[0x3C4 - 0x2D4];
	GhostType ghostType;
	CourseId courseId;
	u8 unknown_0x3CC[0x4B4 - 0x3CC];
    u32 willGhostSave; //0x4B4
    u8 unknown_0x4B8[0x4E8-0x4B8];
	u8 licenseNum;
	u8 unknown_0x4e9[0x510 - 0x4E9];
}; //Total Size 0x510


class MenuDataSub{
public:
    virtual int vtableTemp();
	//vtable 0x808BB44
	ControllerInfo controllerInfos[4];
	u8 unknown_0x44[0x58 - 0x44];
	u32 isTransitionDone;
}; //Total size 0x5C



class MenuData {
public:
    void StartTransition(u32 delay, u32 r5);
    Scene* curScene; /* http://wiki.tockdom.com/wiki/List_of_Identifiers#Menu_Identifiers */
    MenuType menuType[2];
    u32 nextMenuId;
    u32 prevMenuId;
    u32 openingTransitionAnimIdx;
    u32 transitionAnimIdx;
    u32 transitionDelay;
    bool firstLoad;
	u8 unknown_0x21[3];

    u32 homeMenuAction;
    u32 transitionParam;
    u32 transitionFrame;
    MenuState transitionState;
    MenuDataSub sub; /* length is uncertain */
    u32 *field17_0x90; /* 0x128 struct */
    u32 *field18_0x94; /* 0x14 struct */
    MenuData98 *menudata98;
}; //Total Size 0x9C


extern "C"{
    void SetupMenuLoad();
}

extern MenuData *menuData;