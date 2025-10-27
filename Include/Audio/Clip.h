#pragma once

#include <string>

class Clip
{
private:
    std::string audioFilePath;
    float volume;

    friend class AudioSource;

public:
    Clip();
    Clip(const std::string &audioFile, float volume = 1.0f);

    void SetVolume(float newVolume);
    float GetVolume();
    void SetAudioFile(const std::string &audioFile);
};
