#pragma once

#include <chrono>

class Time
{
private:
    friend class Time;
    Time() { StartTime = std::chrono::system_clock::now(); }

    std::chrono::system_clock::time_point StartTime;
    std::chrono::duration<double> DeltaTime;

public:
    static float TimeScale;
    static double deltaTime;

    Time(const Time&) = delete;
    void operator=(const Time&) = delete;

    static Time& GetInstance();

    static void Tick();
    static void Reset();
};