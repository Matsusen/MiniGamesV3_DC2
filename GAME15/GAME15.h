#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME15
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        void play();
        void move();
        void draw();
    private:
        class PLAYER* Player{};
    };
}
