#pragma once

#include <SDL_video.h>
#include <functional>
#include <imgui.h>


class Window
{
public:
    Window();
    ~Window();
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    // Set callback passing ImGui IO
    void SetCallback(std::function<void(const ImGuiIO &)> callback);
    // Main loop, display window until closed
    void Display();

    void SetBackgroundColor(const ImVec4 &color);

private:
    void Initialize();
    void Terminate();

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_GlContext = nullptr;
    ImVec4 m_backroundColor{ 0.45f, 0.55f, 0.60f, 1.00f };
    std::function<void(const ImGuiIO &)> m_callback;
};
