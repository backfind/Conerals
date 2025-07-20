#pragma once
#include"Mainheader.h"

class GameManager {
public:
    GameManager(const GameManager&)=delete;
    GameManager& operator=(const GameManager&)=delete;
    static GameManager& getInstance(){
        static GameManager instance;
        return instance;
    }
    enum GameState {MAINMENU,FFAMENU,,GAMEOVER}
    GameState currentState=MENU;
private:
    GameManager()=default;
};
