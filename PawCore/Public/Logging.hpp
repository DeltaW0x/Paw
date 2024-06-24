
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

#pragma once
#include <spdlog/spdlog.h>

#ifdef _WIN32
#define DBG_BREAK() __debugbreak()
#else
#include <csignal>
#define DBG_BREAK() raise(SIGTRAP)
#endif

#ifdef NDEBUG
    #define LOG_INFO(message,...)
#else
    #define LOG_INFO(message,...) spdlog::info(message,##__VA_ARGS__)
#endif

#define LOG_WARN(message,...) spdlog::warn(message,##__VA_ARGS__)
#define LOG_ERROR(message,...) spdlog::error(message,##__VA_ARGS__)
#define LOG_CRITICAL(message,...) spdlog::critical(message,##__VA_ARGS__)
#define ASSERT(cond,message,...) if(!(cond)) {spdlog::critical(message,##__VA_ARGS__); DBG_BREAK();}
