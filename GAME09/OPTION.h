#pragma once
#include "SCENE.h"
#include "KEYCONFIG.h"
#include "../../libOne/inc/VECTOR2.h"

namespace GAME09 {
    class OPTION :
        public SCENE
    {
    public:
        enum OPTION_KINDS {
            GENERAL,
            KEY_BIND,
            COLOR,
            NUM_KINDS
        };
        struct DATA {
            VECTOR2 optionStrPos;
            float optionStrSize;
            float optionUnderBar;
            float kindButtonY;
            float kindButtonOfstX;
            float kindUnderBar;
            float typeButtonY;
            float typeButtonOfstX;
            float typeUnderBar;
            VECTOR2 keyButtonPos;
            VECTOR2 keyButtonOfst;
        };
    private:
        DATA Option;
        OPTION_KINDS OptionKind;
        //KEYCONFIG::KEY_BIND_TYPE KeyBindType;
        class OPTION_RELATED_BUTTON* KindButtons[NUM_KINDS];
        class OPTION_RELATED_BUTTON* BindTypeButtons[KEYCONFIG::NUM_KEY_BIND_TYPE];
        class OPTION_RELATED_BUTTON* KeyButtons[6][6];
        void UpdateGeneral();
        void UpdateKeyBind();
        void UpdateColor();
        void UpdateKeyButtons();
        void DrawGeneral();
        void DrawKeyBind();
        void DrawColor();
        void DrawKeyButtons();
    public:
        OPTION(class GAME* game);
        ~OPTION();
        void create();
        void init();
        void update();
        void draw();
        void nextScene();
    };
}