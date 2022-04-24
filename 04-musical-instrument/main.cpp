#include "sound.h"
#include "window.h"
#include <SDL.h>
#include <thread>


int main(int, char **)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
    {
        printf("SDL failed to initialize :  %s\n", SDL_GetError());
        return -1;
    }

    {
        Sound sound;
        Window window;

        auto callback = [&](const ImGuiIO &io) {
            float relativeMousePositionX = io.MousePos.x / io.DisplaySize.x;
            float relativeMousePositionY = io.MousePos.y / io.DisplaySize.y;

            if (relativeMousePositionX >= 0.0 && relativeMousePositionX <= 1.0 && relativeMousePositionY >= 0.0 && relativeMousePositionY <= 1.0)
            {
                ImVec4 backroundColor{ relativeMousePositionX, 0.3f, relativeMousePositionY, 1.00f };
                window.SetBackgroundColor(backroundColor);

                if (io.MouseDown[0])
                {
                    sound.SetVolume(relativeMousePositionX);

                    // Tone between 27.5 - 3520
                    const double highestTone = 3520;
                    const double lowestTone = 27.5;
                    printf("Debug %f %f %f\n", relativeMousePositionX, relativeMousePositionY, (highestTone - lowestTone) * (1.0 - relativeMousePositionY));
                    sound.SetTone(lowestTone + (highestTone - lowestTone) * (1.0 - relativeMousePositionY));

                    sound.Play(true);
                }
                else
                {
                    sound.Play(false);
                }
            }
            else
            {
                sound.Play(false);
            }
        };

        window.SetCallback(callback);
        window.Display();
    }


    SDL_Quit();
    return 0;
}
