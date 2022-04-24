#pragma once

#include <SDL_audio.h>
#include <atomic>
#include <cctype>

class Sound
{
public:
    Sound();
    ~Sound();
    Sound(const Sound &) = delete;
    Sound &operator=(const Sound &) = delete;

    void Play(bool on);
    void SetTone(double tone);// Tone in Hz
    void SetVolume(double volume);// Volume between 0 - 1

private:
    void Initialize();
    void Terminate();
    static void Callback(void *userdata, unsigned char *stream, int length);
    void SilenceBuffer(unsigned char *stream, int length);
    void FillBuffer(Sint16 *stream, int length);

    static double Tone(double hz, unsigned time);
    static Sint16 Format(double sample, double amplitude);

    SDL_AudioSpec m_spec{};
    SDL_AudioDeviceID m_device = 0;
    bool m_playing = false;
    std::atomic<double> m_tone = 440;// Hz
    std::atomic<double> m_amplitude = 0.5;// 0 - 1
    unsigned m_time = 0;

    static constexpr unsigned FREQUENCY = 48000;
    static constexpr Uint16 SAMPLES = 4096;
    static constexpr double PI = 3.14159265;
};
