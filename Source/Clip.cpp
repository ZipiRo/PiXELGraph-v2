#include "Audio/Clip.h"

Clip::Clip()
{
    volume = 1.0f;
}

Clip::Clip(const std::string &audioFile, float volume)
{
    audioFilePath = audioFile;
    this->volume = volume;
}

void Clip::SetVolume(float newVolume)
{
    volume = newVolume;
}

float Clip::GetVolume()
{
    return volume;
}

void Clip::SetAudioFile(const std::string &audioFile)
{
    audioFilePath = audioFile;
}
