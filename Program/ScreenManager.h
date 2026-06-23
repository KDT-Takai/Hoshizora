#pragma once
#include <iostream>
#include "ScreenBase.h"

class ScreenManager
{
protected:
    ScreenManager();
    virtual ~ScreenManager() = default;
public:
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    static ScreenManager& Instance() {
        static ScreenManager instance;
        return instance;
    }

protected:

    std::unique_ptr<ScreenBase> screen;
    std::unique_ptr<ScreenBase> next;
    bool changeFlag = false;

public:

    void Update();
    void Draw();

    template <typename T, typename... Args>
    void ChangeScreen(Args&&... args)
    {
        next = std::make_unique<T>(std::forward<Args>(args)...);
        changeFlag = true;
    }
};