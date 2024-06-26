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


#include <Renderer/Renderer.hpp>
#include <Logging.hpp>

namespace pawcore {
    Renderer::Renderer(RendererConfig *config, SDL_Window *window, const bool debug) : m_pWindow(window) {
        m_pGpuDevice = SDL_GpuCreateDevice(config->backend, debug);


        config->presentMode = CheckPresentMode(config->presentMode);
        config->swapchainComposition = CheckSwapchainComposition(config->swapchainComposition);
        ASSERT(m_pGpuDevice != NULL, "Failed to create GPU Device");
        ASSERT(SDL_GpuClaimWindow(m_pGpuDevice,window,config->swapchainComposition,config->presentMode) == SDL_TRUE,
               "Failed to claim Window");
    }

    void Renderer::Present()
    {

    }

    SDL_GpuPresentMode Renderer::CheckPresentMode(SDL_GpuPresentMode mode) {
        if (mode != SDL_GPU_PRESENTMODE_VSYNC) {
            if (!SDL_GpuSupportsPresentMode(m_pGpuDevice, m_pWindow, mode)) {
                switch (mode) {
                    case SDL_GPU_PRESENTMODE_MAILBOX:
                        LOG_ERROR("Mailbox is not a supported presentation mode, reverting to VSync");
                    break;
                    case SDL_GPU_PRESENTMODE_IMMEDIATE:
                        LOG_ERROR("Immediate is not a supported presentation mode, reverting to VSync");
                    break;
                }
                return SDL_GPU_PRESENTMODE_VSYNC;
            }
        }
        return mode;
    }

    SDL_GpuSwapchainComposition Renderer::CheckSwapchainComposition(SDL_GpuSwapchainComposition composition) {
        if (composition != SDL_GPU_SWAPCHAINCOMPOSITION_SDR) {
            if (!SDL_GpuSupportsSwapchainComposition(m_pGpuDevice, m_pWindow, composition)) {
                switch (composition) {
                    case SDL_GPU_SWAPCHAINCOMPOSITION_SDR_LINEAR:
                        LOG_ERROR("SDR Linear is not a supported swapchain format, reverting to SDR NONLINEAR");
                    break;
                    case SDL_GPU_SWAPCHAINCOMPOSITION_HDR10_ST2048:
                        LOG_ERROR("HDR10 is not a supported swapchain format, reverting to SDR NONLINEAR");
                    break;
                    case SDL_GPU_SWAPCHAINCOMPOSITION_HDR_EXTENDED_LINEAR:
                        LOG_ERROR(
                            "Extended HDR Linear is not a supported swapchain format, reverting to SDR NONLINEAR");
                    break;
                }
                return SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
            }
        }
        return composition;
    }
}
