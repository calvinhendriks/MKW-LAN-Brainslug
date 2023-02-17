#include <Kamek/kamek.hpp>
#include <Input/inputdata.hpp>
#include <UI/menudata.hpp>

#define CHECK_BUTTON(universal, specific) \
    case universal: return (inputs & specific) != 0;

bool CheckButtonPressed(RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button){
    u16 inputs = controllerHolder->inputStates[0].buttonRaw;
    if (onlyCheckNewButtons) inputs = (inputs & ~controllerHolder->inputStates[1].buttonRaw);

    float horizontalCStick;
    float verticalCStick;
    if (controllerType == WHEEL){
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, WHEEL_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, WHEEL_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, WHEEL_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, WHEEL_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, WHEEL_A)
            CHECK_BUTTON(BUTTON_B, WHEEL_B)
            CHECK_BUTTON(BUTTON_MINUS, WHEEL_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, WHEEL_PLUS)
            CHECK_BUTTON(BUTTON_HOME, WHEEL_HOME)
            CHECK_BUTTON(BUTTON_1, WHEEL_1)
            CHECK_BUTTON(BUTTON_2, WHEEL_2)
            default:
                return false;
        }
    }
    else if (controllerType == NUNCHUCK){
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, NUNCHUCK_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, NUNCHUCK_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, NUNCHUCK_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, NUNCHUCK_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, NUNCHUCK_A)
            CHECK_BUTTON(BUTTON_B, NUNCHUCK_B)
            CHECK_BUTTON(BUTTON_MINUS, NUNCHUCK_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, NUNCHUCK_PLUS)
            CHECK_BUTTON(BUTTON_HOME, NUNCHUCK_HOME)
            CHECK_BUTTON(BUTTON_1, NUNCHUCK_1)
            CHECK_BUTTON(BUTTON_2, NUNCHUCK_2)
            CHECK_BUTTON(BUTTON_C, NUNCHUCK_C)
            CHECK_BUTTON(BUTTON_Z, NUNCHUCK_Z)
            default:
                return false;
        }
        
    }
    else if (controllerType == CLASSIC){
        WiiController *wiiController = (WiiController*) controllerHolder->controller;
        horizontalCStick = wiiController->kpadStatus[0].cStickHorizontal;
        verticalCStick = wiiController->kpadStatus[0].cStickVertical;
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, CLASSIC_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, CLASSIC_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, CLASSIC_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, CLASSIC_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, CLASSIC_A)
            CHECK_BUTTON(BUTTON_B, CLASSIC_B)
            CHECK_BUTTON(BUTTON_X, CLASSIC_X)
            CHECK_BUTTON(BUTTON_Y, CLASSIC_Y)
            CHECK_BUTTON(BUTTON_MINUS, CLASSIC_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, CLASSIC_PLUS)
            CHECK_BUTTON(BUTTON_HOME, CLASSIC_HOME)
            CHECK_BUTTON(BUTTON_L, CLASSIC_L)
            CHECK_BUTTON(BUTTON_R, CLASSIC_R)
            CHECK_BUTTON(BUTTON_ZL, CLASSIC_ZL)
            CHECK_BUTTON(BUTTON_Z, CLASSIC_Z)
        }
        
    }
    else if (controllerType == GCN){
        GCNController *gcnController = (GCNController*) controllerHolder->controller;
        horizontalCStick = gcnController->cStickHorizontal;
        verticalCStick = gcnController->cStickVertical;
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, GCN_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, GCN_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, GCN_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, GCN_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, GCN_A)
            CHECK_BUTTON(BUTTON_B, GCN_B)
            CHECK_BUTTON(BUTTON_X, GCN_X)
            CHECK_BUTTON(BUTTON_Y, GCN_Y)
            CHECK_BUTTON(BUTTON_Z, GCN_Z)
            CHECK_BUTTON(BUTTON_PLUS, GCN_START)
            CHECK_BUTTON(BUTTON_L, GCN_L)
            CHECK_BUTTON(BUTTON_R, GCN_R)
        }
    }
    if (button >= C_STICK_UP_EIGHT && button <= C_STICK_UPLEFT_EIGHT){
        const float const1 = 0.92387953251;
        const float const2 = 0.38268343236;
        switch (button){
            case(C_STICK_UP_EIGHT): return (verticalCStick >= const1);
            case(C_STICK_UPRIGHT_EIGHT): return (verticalCStick >=const2 && horizontalCStick >= const2);
            case(C_STICK_RIGHT_EIGHT): return (horizontalCStick >= const1);
            case(C_STICK_DOWNRIGHT_EIGHT): return (verticalCStick <= -const2 && horizontalCStick >= const2);
            case(C_STICK_DOWN_EIGHT): return (verticalCStick <= -const1);
            case(C_STICK_DOWNLEFT_EIGHT): return (verticalCStick <= -const2 && horizontalCStick <= -const2);
            case(C_STICK_LEFT_EIGHT): return (horizontalCStick <= -const1);
            case(C_STICK_UPLEFT_EIGHT): return (verticalCStick >=const2 && horizontalCStick <= -const2);
        }
    }
    return false;
}

bool CheckButtonCombination(RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, UniversalButtons buttonMask){
    bool pressed = true;
    for (int i = 0; i < 32; i++) {
        int iMask = 1 << i;
        if (buttonMask & iMask)
            if (!CheckButtonPressed(controllerHolder, controllerType, onlyCheckNewButtons, (UniversalButtons) iMask)) pressed = false;
        }
    return pressed;
}