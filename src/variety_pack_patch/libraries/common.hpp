#pragma once

class Timer {
public:
  Timer(); // 8051c374
  // vtable 808b2d44
  virtual ~Timer(); // 8051c334
  u16 minutes;
  u8 seconds;
  // padding 0x7
  u16 milliseconds;
  Timer operator -(Timer *other);
  u8 unknown_0xa[2];
}; // Total size 0xc

enum VehicleId{
	STANDARD_KART_S	    =0X00,
	STANDARD_KART_M	    =0X01,
	STANDARD_KART_L	    =0X02,
	BABY_BOOSTER        =0X03,
	CLASSIC_DRAGSTER    =0X04,
	OFFROADER		    =0X05,
	MINI_BEAST		    =0X06,
	WILD_WING		    =0X07,
	FLAME_FLYER		    =0X08,
	CHEEP_CHARGER	    =0X09,
	SUPER_BLOOPER	    =0X0A,
	PIRANHA_PROWLER	    =0X0B,
	RALLY_ROMPER	    =0X0C,
	ROYAL_RACER		    =0X0D,
	JETSETTER		    =0X0E,
	BLUE_FALCON		    =0X0F,
	SPRINTER		    =0X10,
	HONEYCOUPE		    =0X11,
	STANDARD_BIKE_S	    =0X12,
	STANDARD_BIKE_M	    =0X13,
	STANDARD_BIKE_L	    =0X14,
	BULLET_BIKE		    =0X15,
	MACH_BIKE		    =0X16,
	BOWSER_BIKE		    =0X17,
	BIT_BIKE		    =0X18,
	BON_BON		        =0X19,
	WARIO_BIKE		    =0X1A,
	QUACKER			    =0X1B,
	RAPIDE			    =0X1C,
	SHOOTING_STAR	    =0X1D,
	MAGIKRUISER		    =0X1E,
	NITROCYCLE		    =0X1F,
	SPEAR			    =0X20,
	JET_BUBBLE		    =0X21,
	DOLPHIN_DASHER	    =0X22,
	PHANTOM			    =0X23
};


enum CharacterId{
	MARIO		    	    =0X00,
    BABY_PEACH	    	    =0X01,
    WALUIGI		    	    =0X02,
    BOWSER		    	    =0X03,
    BABY_DAISY	    	    =0X04,
    DRY_BONES	    	    =0X05,
    BABY_MARIO	    	    =0X06,
    LUIGI		    	    =0X07,
    TOAD		    	    =0X08,
    DONKEY_KONG	    	    =0X09,
    YOSHI		    	    =0X0A,
    WARIO		    	    =0X0B,
    BABY_LUIGI	    	    =0X0C,
    TOADETTE	    	    =0X0D,
    KOOPA_TROOPA	    	=0X0E,
    DAISY		    	    =0X0F,
    PEACH		    	    =0X10,
    BIRDO		    	    =0X11,
    DIDDY_KONG	    	    =0X12,
    KING_BOO		    	=0X13,
    BOWSER_JR	    		=0X14,
    DRY_BOWSER	    		=0X15,
    FUNKY_KONG	    		=0X16,
    ROSALINA	    		=0X17,
    MII_S_A_MALE	        =0X18,
    MII_S_A_FEMALE	        =0X19,
    MII_S_B_MALE	        =0X1A,
    MII_S_B_FEMALE	        =0X1B,
    MII_S_C_MALE	        =0X1C,
    MII_S_C_FEMALE	        =0X1D,
    MII_M_A_MALE	        =0X1E,
    MII_M_A_FEMALE          =0X1F,
    MII_M_B_MALE	        =0X20,
    MII_M_B_FEMALE	        =0X21,
    MII_M_C_MALE	        =0X22,
    MII_M_C_FEMALE          =0X23,
    MII_L_A_MALE	        =0X24,
    MII_L_A_FEMALE	        =0X25,
    MII_L_B_MALE	        =0X26,
    MII_L_B_FEMALE	        =0X27,
    MII_L_C_MALE 	        =0X28,
    MII_L_C_FEMALE	        =0X29,
    MII_M			        =0X2A,
    MII_S			        =0X2B,
    MII_L			        =0X2C,
    PEACH_BIKER		        =0X2D,
    DAISY_BIKER		        =0X2E,
    ROSALINA_BIKER		    =0X2F
};

enum CourseId{
    LUIGI_CIRCUIT = 0X08,
    MOO_MOO_MEADOWS = 0X01,
    MUSHROOM_GORGE = 0X02,
    TOADS_FACTORY = 0X04,

    MARIO_CIRCUIT = 0X00,
    COCONUT_MALL = 0X05,
    DK_SUMMIT = 0X06,
    WARIOS_GOLD_MINE = 0X07,

    DAISY_CIRCUIT = 0X09,
    KOOPA_CAPE = 0X0F,
    MAPLE_TREEWAY = 0X0B,
    GRUMBLE_VOLCANO = 0X03,

    DRY_DRY_RUINS = 0X0E,
    MOONVIEW_HIGHWAY = 0X0A,
    BOWSERS_CASTLE = 0X0C,
    RAINBOW_ROAD = 0X0D,

    GCN_PEACH_BEACH = 0X10,
    DS_YOSHI_FALLS = 0X14,
    SNES_GHOST_VALLEY_2 = 0X19,
    N64_MARIO_RACEWAY = 0X1A,

    N64_SHERBET_LAND = 0X1B,
    GBA_SHY_GUY_BEACH = 0X1F,
    DS_DELFINO_SQUARE = 0X17,
    GCN_WALUIGI_STADIUM = 0X12,

    DS_DESERT_HILLS = 0X15,
    GBA_BOWSER_CASTLE_3 = 0X1E,
    N64_DKS_JUNGLE_PARKWAY = 0X1D,
    GCN_MARIO_CIRCUIT = 0X11,

    SNES_MARIO_CIRCUIT_3 = 0X18,
    DS_PEACH_GARDENS = 0X16,
    GCN_DK_MOUNTAIN = 0X13,
    N64_BOWSERS_CASTLE = 0X1C,

    BLOCK_PLAZA = 0X21,
    DELFINO_PIER = 0X20,
    FUNKY_STADIUM = 0X23,
    CHAIN_CHOMP_ROULETTE = 0X22,
    THWOMP_DESERT = 0X24,

    SNES_BATTLE_COURSE_4 = 0X27,
    GBA_BATTLE_COURSE_3 = 0X28,
    N64_SKYSCRAPER = 0X29,
    GCN_COOKIE_LAND = 0X25,
    DS_TWILIGHT_HOUSE = 0X26,

    GALAXY_COLOSSEUM = 0X36,
    SUNSET_LUIGI_CIRCUIT = 0X3A,

    WINNING_DEMO = 0X37,
    LOSING_DEMO = 0X38,
    DRAW_DEMO = 0X39
};

enum ControllerId {
    CONTROLLER_Wii_WHEEL = 0x0,
    CONTROLLER_NUNCHUCK = 0x1,
    CONTROLLER_CLASSIC = 0x2,
    CONTROLLER_GCN = 0x3
};


enum ItemObjectId{
    OBJ_GREEN_SHELL=0x0,
    OBJ_RED_SHELL=0x1,
    OBJ_BANANA=0x2,
    OBJ_FAKE_ITEM_BOX=0x7,
    OBJ_MUSHROOM=0x3,
    OBJ_BOBOMB=0x9,
    OBJ_BLUE_SHELL=0x5,
    OBJ_LIGHTNING=0x6,
    OBJ_STAR=0x4,
    OBJ_GOLDEN_MUSHROOM=0xC,
    OBJ_MEGA_MUSHROOM=0x8,
    OBJ_BLOOPER=0xA,
    OBJ_POW_BLOCK=0xB,
    OBJ_THUNDER_CLOUD=0xE,
    OBJ_BULLET_BILL=0xD
};

enum ItemId{
    GREEN_SHELL=0x0,
    RED_SHELL=0x1,
    BANANA=0x2,
    FAKE_ITEM_BOX=0x3,
    MUSHROOM=0x4,
    TRIPLE_MUSHROOM=0x5,
    BOBOMB=0x6,
    BLUE_SHELL=0x7,
    LIGHTNING=0x8,
    STAR=0x9,
    GOLDEN_MUSHROOM=0xA,
    MEGA_MUSHROOM=0xB,
    BLOOPER=0xC,
    POW_BLOCK=0xD,
    THUNDER_CLOUD=0xE,
    BULLET_BILL=0xF,
    TRIPLE_GREEN_SHELL=0x10,
    TRIPLE_RED_SHELL=0x11,
    TRIPLE_BANANA=0x12,
    UNKNOWN_0X13=0x13,
    NONE=0x14,
};

enum RadioSettings {
    RADIO_FASTMENUS = 0x0,
    RADIO_PANEL = 0x1,
    RADIO_SPEEDUP = 0x2,
    RADIO_GHOST = 0x3,
};

enum ScrollerSettings {
    SCROLLER_BOOT = 0x0,
    SCROLLER_INFO = 0x1
};

enum RadioFASTMENUS {
    RADIO_FASTMENUS_DISABLED = 0x0,
    RADIO_FASTMENUS_ENABLED = 0x1,
};

enum RadioPANEL {
    RADIO_PANEL_DISABLED = 0x0,
    RADIO_PANEL_LIGHT = 0x1,
    RADIO_PANEL_FULL = 0x2,
    RADIO_PANEL_OFFROAD = 0x3
};

enum RadioSPEEDUP {
    RADIO_SPEEDUP_DISABLED = 0x0,
    RADIO_SPEEDUP_ENABLED = 0x1
};

enum RadioGHOST {
    RADIO_GHOST_DISABLED = 0x0,
    RADIO_GHOST_ENABLED = 0x1
};

enum ScrollerBOOT {
    SCROLLER_BOOT_DEFAULT = 0x0,
    SCROLLER_BOOT_TTCUP = 0x1,
    SCROLLER_BOOT_1PMENU = 0x2,
    SCROLLER_BOOT_ONLINE = 0x3
};

enum ScrollerINFO {
    SCROLLER_INFO_NONE = 0x0,
    SCROLLER_INFO_CHECKPOINT = 0x1,
    SCROLLER_INFO_ITPT = 0x2,
    SCROLLER_INFO_AREA = 0x3
};

struct ptmf{
    int this_delta;
    int vtableOffset;
    void *functionPointer;
};//total size 0xc

struct ptmfHolder{
    u32 vtable;
    void* subject; //Pointer to the class instance, most times the class inheriting from PushButton (such as the class for the buttons of the selectionScreen)
    ptmf ptmf;
};//total size 0x14


template <typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolderBase_3A {
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) = 0;
};
template <class Subject, typename Ret, typename A1, typename A2, typename A3>
struct PtmfHolder_3A : PtmfHolderBase_3A<Ret, A1, A2, A3> {
    Subject * subject;
    Ret (Subject::*ptmf)(A1, A2, A3);
    virtual Ret operator()(A1 a1, A2 a2, A3 a3) {
        return (subject->*ptmf)(a1, a2, a3);
    }
};

template <typename Ret, typename A1, typename A2>
struct PtmfHolderBase_2A {
    virtual Ret operator()(A1 a1, A2 a2) = 0;
};
template <class Subject, typename Ret, typename A1, typename A2>
struct PtmfHolder_2A : PtmfHolderBase_2A<Ret, A1, A2> {
    Subject * subject;
    Ret (Subject::*ptmf)(A1, A2);
    virtual Ret operator()(A1 a1, A2 a2) {
        return (subject->*ptmf)(a1, a2);
    }
};

template <typename Ret, typename A1>
struct PtmfHolderBase_1A {
    virtual Ret operator()(A1 a1) = 0;
};

template <class Subject, typename Ret, typename A1>
struct PtmfHolder_1A : PtmfHolderBase_1A<Ret, A1> {
    Subject * subject;
    Ret (Subject::*ptmf)(A1);
    virtual Ret operator()(A1 a1) {
        return (subject->*ptmf)(a1);
    }
};

template <typename Ret>
struct PtmfHolderBase_0A {
    virtual Ret operator()() = 0;
};

template <class Subject, typename Ret>
struct PtmfHolder_0A : PtmfHolderBase_0A<Ret> {
    Subject * subject;
    Ret (Subject::*ptmf)();
    virtual Ret operator()() {
        return (subject->*ptmf)();
    }
};

extern u32 ptmfVtable;