/*
 *   Copyright (c) 2023 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#pragma once

#include "renderer/pipeline/graphics_pipeline.hpp"
#include "renderer/pipeline/pipeline_set.hpp"
#include "renderer/command_buffer.hpp"
#include "renderer/device.hpp"
#include "renderer/instance_manager.hpp"
#include "renderer/shader_set.hpp"
#include "renderer/swapchain.hpp"
#include "renderer/window.hpp"

#include <volk/volk.h>

#include <vector>
#include <memory>

namespace mcvk::Renderer {
    class Renderer {
    public:
        Renderer(const Window &window);
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        inline const Device &GetDevice() const { return _device; }
        inline const PipelineSet &Pipelines() const { return _pipeline_set; }

        void WaitDeviceIdle();

        CommandBuffer *BeginDrawCommandBuffer();

    private:
        friend class CommandBuffer;

        void _RecreateSwapchain();
        void _CreatePipelines();
        void _CreateCommandBuffers();

        const Window &_window;
        const VkSurfaceKHR &_surface;

        InstanceManager _instance_mgr;
        Device _device;
        PipelineSet _pipeline_set;

        std::unique_ptr<Swapchain> _swapchain;
        CommandBuffer _draw_command_buffer;
    };
}
