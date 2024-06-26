#include <PawCore.hpp>
#include <SDL3/SDL.h>


int main(void) {

    pawcore::RendererConfig rendererConfig;
    rendererConfig.backend = SDL_GPU_BACKEND_ALL;
    rendererConfig.presentMode = SDL_GPU_PRESENTMODE_MAILBOX;
    rendererConfig.swapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2048;
    rendererConfig.renderScale = 1;

    pawcore::WindowConfig windowConfig;
    windowConfig.windowTitle = "Paw Editor";
    windowConfig.windowWidth = 1280;
    windowConfig.windowHeight = 720;
    windowConfig.windowFlags = SDL_WINDOW_RESIZABLE;

    pawcore::Context context(&rendererConfig,&windowConfig,true);

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
