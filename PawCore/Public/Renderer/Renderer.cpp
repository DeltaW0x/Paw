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

namespace PawCore {
    Renderer::Renderer(RendererConfig *config, SDL_Window *window, const bool debug) : m_pWindow(window),
        m_currentRenderScale(config->renderScale) {
        m_pGpuDevice = SDL_GpuCreateDevice(config->backend, debug);

        if (config->swapchainComposition != SDL_GPU_SWAPCHAINCOMPOSITION_SDR) {
            if (!SDL_GpuSupportsSwapchainComposition(m_pGpuDevice, window, config->swapchainComposition)) {
                switch (config->swapchainComposition) {
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
                config->swapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
            }
        }
        if (config->presentMode != SDL_GPU_PRESENTMODE_VSYNC) {
            if (!SDL_GpuSupportsPresentMode(m_pGpuDevice, window, config->presentMode)) {
                switch (config->presentMode) {
                    case SDL_GPU_PRESENTMODE_MAILBOX:
                        LOG_ERROR("Mailbox is not a supported presentation mode, reverting to VSync");
                        break;
                    case SDL_GPU_PRESENTMODE_IMMEDIATE:
                        LOG_ERROR("Immediate is not a supported presentation mode, reverting to VSync");
                        break;
                }
                config->presentMode = SDL_GPU_PRESENTMODE_VSYNC;
            }
        }
        ASSERT(m_pGpuDevice != NULL, "Failed to create GPU Device");
        ASSERT(SDL_GpuClaimWindow(m_pGpuDevice,window,config->swapchainComposition,config->presentMode) == SDL_TRUE,
               "Failed to claim Window");

        SetupMainRT(config->mssaCount);
    }

    void Renderer::Present() {
        SDL_GpuCommandBuffer* cmd = SDL_GpuAcquireCommandBuffer(m_pGpuDevice);
        SDL_GpuTexture* swpTex = SDL_GpuAcquireSwapchainTexture(cmd,m_pWindow,&m_swapchainWidth,&m_swapchainHeight);
        if(swpTex != NULL) {

        }
    }


    void Renderer::SetupMainRT(SDL_GpuSampleCount msaa) {
        int width, height;
        SDL_GetWindowSize(m_pWindow, &width, &height);
        m_swapchainWidth = width;
        m_swapchainHeight = height;

        width /= m_currentRenderScale;
        height /= m_currentRenderScale;

        m_renderWidth = width;
        m_renderHeight = height;

        SDL_GpuTextureCreateInfo rtInfo = {};
        rtInfo.isCube = SDL_FALSE;
        rtInfo.width = width;
        rtInfo.height = height;
        rtInfo.depth = 1;
        rtInfo.layerCount = 1;
        rtInfo.levelCount = 1;
        rtInfo.sampleCount = msaa;
        rtInfo.usageFlags = SDL_GPU_TEXTUREUSAGE_SAMPLER_BIT | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET_BIT;
        rtInfo.format = SDL_GPU_TEXTUREFORMAT_R16G16B16A16;

        m_pMainRT = SDL_GpuCreateTexture(m_pGpuDevice, &rtInfo);
        ASSERT(m_pMainRT != NULL, "Failed to create main render target");
    }
}
