/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include "renderer/pipeline/pipeline_factory.hpp"
#include "renderer/device.hpp"
#include "renderer/swapchain.hpp"

#include <volk/volk.h>

#include <vector>

namespace mcvk::Renderer {
    class Renderer;

    class CommandBuffer {
    public:
        CommandBuffer(const Device &device, const std::unique_ptr<Swapchain> &swapchain);
        ~CommandBuffer();

        CommandBuffer(const CommandBuffer &) = delete;
        CommandBuffer &operator=(const CommandBuffer &) = delete;

        void End();

        void BeginRenderPass();
        void EndRenderPass();

        void BindPipeline(const GraphicsPipeline &pipeline);

        void UpdateViewportAndScissor();

    private:
        friend class Renderer;

        void _Initialise(Renderer *const renderer);

        void _Begin();

        const Device &_device;
        const std::unique_ptr<Swapchain> &_swapchain;
        Renderer *_renderer{nullptr};

        std::vector<VkCommandBuffer> _cmdbufs;
        VkCommandBuffer _cb;

        uint32_t _current_image_index{0};
        int32_t _current_frame_index{0};
        bool _frame_started{false};
    };
}