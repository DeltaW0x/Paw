#include <PawCore.hpp>
#include <SDL3/SDL.h>

#include "Context/Context.hpp"

int main(void) {

    PawCore::RendererConfig rendererConfig;
    rendererConfig.backend = SDL_GPU_BACKEND_ALL;
    rendererConfig.presentMode = SDL_GPU_PRESENTMODE_MAILBOX;
    rendererConfig.swapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2048;
    rendererConfig.renderScale = 1;

    PawCore::WindowConfig windowConfig;
    windowConfig.windowTitle = "Paw Editor";
    windowConfig.windowWidth = 1280;
    windowConfig.windowHeight = 720;
    windowConfig.windowFlags = SDL_WINDOW_RESIZABLE;

    PawCore::Context context(&rendererConfig,&windowConfig,true);

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    SDL_Quit();
                    return 0;
            }
        }
    }
}
