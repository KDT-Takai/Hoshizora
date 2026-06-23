#include "ScreenManager.h"

#include "Tittle.h"
#include "Home.h"
#include "Game.h"

ScreenManager::ScreenManager()
{
    screen = std::make_unique<Tittle>();
}

void ScreenManager::Update()
{
    screen->Update();
    if (changeFlag) {
        screen = std::move(next);
        next.reset();
        changeFlag = false;
    }
}

void ScreenManager::Draw()
{
    screen->Draw();
}