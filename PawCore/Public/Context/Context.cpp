// Paw Engine
// Copyright (c) 2024 Luca Cassarino(DeltaWave0x)
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include <Context/Context.hpp>
#include <Logging.hpp>
#include <SDL3/SDL.h>

static void SDL_LoggerBridge(void *userdata, int category, SDL_LogPriority priority, const char *message) {
    switch(priority) {
        case SDL_LOG_PRIORITY_INFO:
            LOG_INFO(message);
        break;
        case SDL_LOG_PRIORITY_WARN:
            LOG_WARN(message);
        break;
        case SDL_LOG_PRIORITY_ERROR:
            LOG_ERROR(message);
        break;
        case SDL_LOG_PRIORITY_CRITICAL:
            LOG_CRITICAL(message);
        break;
        default:
            break;
    }
}

namespace PawCore {
    Context::Context(RendererConfig *rConfig,WindowConfig *wConfig,const bool debug) {
        SDL_SetLogOutputFunction(&SDL_LoggerBridge,NULL);

        ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "failed to init SDL: {0}", SDL_GetError());

        m_pWindows = SDL_CreateWindow(wConfig->windowTitle, wConfig->windowWidth, wConfig->windowHeight,wConfig->windowFlags);
        ASSERT(m_pWindows != NULL, "Failed to create Window: {0}", SDL_GetError());

        m_pRenderer = new Renderer(rConfig,m_pWindows,debug);
    }
}
