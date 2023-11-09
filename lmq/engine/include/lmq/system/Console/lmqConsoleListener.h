#pragma once

class lmqConsole;

class lmqConsoleListener
{
public:
    virtual ~lmqConsoleListener() {}

    virtual void OnConsoleInput(const char* line) = 0;
};