#include "sound.h"
#include <SDL.h>
#include <math.h>
#include <stdio.h>

Sound::Sound()
{
    this->Initialize();
}

Sound::~Sound()
{
    this->Initialize();
}

void Sound::Initialize()
{
    m_spec.freq = FREQUENCY;
    m_spec.format = AUDIO_S16SYS;// Signed 16 bit integer format
    m_spec.channels = 1;
    m_spec.samples = SAMPLES;
    m_spec.callback = Sound::Callback;
    m_spec.userdata = this;

    m_device = SDL_OpenAudioDevice(NULL, 0, &m_spec, NULL, 0);
}

void Sound::Terminate()
{
    SDL_CloseAudioDevice(m_device);
    SDL_Quit();
}

void Sound::Play(bool on)
{
    if (!m_playing && on)
    {
        m_time = 0;
        // Unpause the device, this starts playback (the callback function starts getting called)
        SDL_PauseAudioDevice(m_device, 0);
        m_playing = true;
    }
    else if (m_playing && !on)
    {
        SDL_PauseAudioDevice(m_device, 1);
        m_playing = false;
    }
}

void Sound::SetTone(double tone)
{
    if (tone > 0)
    {
        m_tone = tone;
    }
}

void Sound::SetVolume(double volume)
{
    if (volume >= 0.0 && volume <= 1.0)
    {
        m_amplitude = volume;
    }
}

void Sound::Callback(void *userdata, unsigned char *stream, int length)
{
    Sound *sound = reinterpret_cast<Sound *>(userdata);
    sound->SilenceBuffer(stream, length);
    sound->FillBuffer(reinterpret_cast<Sint16 *>(stream), length / sizeof(Sint16));
}

void Sound::SilenceBuffer(unsigned char *stream, int length)
{
    // Silence the whole stream in case we don't touch some parts of it
    // This fills the stream with the silence value (almost always just 0)
    // SDL implements the standard library (SDL_memset, SDL_memcpy etc.) to support more platforms
    SDL_memset(stream, m_spec.silence, length);
}

void Sound::FillBuffer(Sint16 *stream, int length)
{
    double tone = m_tone;
    double period = FREQUENCY / tone;
    printf("Playing tone %f Hz\n", tone);

    for (int i = 0; i < length; i++)
    {
        // Get current tone
        stream[i] = Sound::Format(Sound::Tone(tone, m_time), m_amplitude);

        // Increase time, check period
        ++m_time;
        if (m_time > period)
        {
            // Period reached, reset time, set current tone and calculate new period
            m_time = 0;
            tone = m_tone;
            period = FREQUENCY / tone;
            printf("Playing tone %f Hz\n", tone);
        }
    }
}

double Sound::Tone(double hz, unsigned time)
{
    return sin(time * hz * PI * 2 / FREQUENCY);
}

Sint16 Sound::Format(double sample, double amplitude)
{
    return static_cast<Sint16>(sample * SDL_MAX_SINT16 * amplitude);
}
