/* The gobot is a robot simulation platform. 
 * Copyright(c) 2021-2023, RobSimulatorGroup, Qiqi Wu<1258552199@qq.com>.
 * Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.
 * This version of the GNU Lesser General Public License incorporates the terms and conditions of version 3 of the GNU General Public License.
 * This file is created by Qiqi Wu, 23-2-8
*/

#pragma once

#include "gobot/core/types.hpp"

namespace gobot {

enum class RenderAPI : std::uint8_t
{
    OpenGL,
    Vulkan,   // Unsupported right now
    Direct3D, // Unsupported right now
    Metal     // Unsupported right now
};

class GraphicsContext
{
public:
    virtual ~GraphicsContext() = default;

//    static void SetRenderAPI(RenderAPI api);
//
//    static GraphicsContext* Create();

    virtual void Init() = 0;

    virtual void Present() = 0;

    virtual float GetGPUMemoryUsed() = 0;

    virtual float GetTotalGPUMemory() = 0;

    [[nodiscard]] virtual std::size_t GetMinUniformBufferOffsetAlignment() const = 0;

    [[nodiscard]] virtual bool FlipImGUITexture() const = 0;

    virtual void WaitIdle() const = 0;

    virtual void OnImGui() = 0;

};

}