/* The gobot is a robot simulation platform. 
 * Copyright(c) 2021-2023, RobSimulatorGroup, Qiqi Wu<1258552199@qq.com>.
 * Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.
 * This version of the GNU Lesser General Public License incorporates the terms and conditions of version 3 of the GNU General Public License.
 * This file is created by Qiqi Wu, 23-3-18
*/

#include "gobot/rendering/render_pass.hpp"
#include "gobot/rendering/frame_buffer_cache.hpp"
#include "gobot/rendering/default_view_id.hpp"

namespace gobot {


RenderPass::RenderPass(const String& name, ViewId view_id)
    : view_id_(view_id)
{
    bgfx::resetView(view_id_);
    bgfx::setViewName(view_id_, name.toStdString().c_str());
}

void RenderPass::Bind(const RenderRID& frame_buffer_rid) const {
    bgfx::setViewMode(view_id_, bgfx::ViewMode::Sequential);
    if(frame_buffer_rid.IsValid()) {
        const auto size = FrameBufferCache::GetInstance()->GetSize(frame_buffer_rid);
        const auto width = size[0];
        const auto height = size[1];
        bgfx::setViewRect(view_id_, std::uint16_t(0), std::uint16_t(0), std::uint16_t(width), std::uint16_t(height));
        bgfx::setViewScissor(view_id_, std::uint16_t(0), std::uint16_t(0), std::uint16_t(width), std::uint16_t(height));

        bgfx::setViewFrameBuffer(view_id_, FrameBufferHandle{frame_buffer_rid.GetID()});
    } else {
        bgfx::setViewFrameBuffer(view_id_, FrameBufferHandle{bgfx::kInvalidHandle});
    }
    Touch();
}

void RenderPass::Touch() const {
    bgfx::touch(view_id_);
}

void RenderPass::Clear(RenderClearFlags clear_flags,
                       const Color& color,
                       float depth,
                       uint8_t stencil) const {
    bgfx::setViewClear(view_id_, ENUM_UINT_CAST(clear_flags), color.GetPackedRgbA(), depth, stencil);
    Touch();
}

void RenderPass::Clear() const {
    USING_ENUM_BITWISE_OPERATORS;
    Clear(RenderClearFlags::Color | RenderClearFlags::Depth | RenderClearFlags::Stencil, {0.f, 0.f, 0.f, 1.f}, 1.0f, 0);
}

void RenderPass::SetViewTransform(const Matrix4f& view, const Matrix4f& proj) const {
    bgfx::setViewTransform(view_id_, view.data(), proj.data());
}


}