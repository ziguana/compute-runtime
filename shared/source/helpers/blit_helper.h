/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/helpers/common_types.h"
#include "shared/source/helpers/vec.h"

#include <functional>

namespace NEO {

class GraphicsAllocation;

enum class BlitOperationResult {
    Unsupported,
    Fail,
    Success,
    GpuHang
};

namespace BlitHelperFunctions {
using BlitMemoryToAllocationFunc = std::function<BlitOperationResult(const Device &device,
                                                                     GraphicsAllocation *memory,
                                                                     size_t offset,
                                                                     const void *hostPtr,
                                                                     const Vec3<size_t> &size)>;
extern BlitMemoryToAllocationFunc blitMemoryToAllocation;
} // namespace BlitHelperFunctions

struct BlitHelper {
    static BlitOperationResult blitMemoryToAllocation(const Device &device, GraphicsAllocation *memory, size_t offset, const void *hostPtr,
                                                      const Vec3<size_t> &size);
    static BlitOperationResult blitMemoryToAllocationBanks(const Device &device, GraphicsAllocation *memory, size_t offset, const void *hostPtr,
                                                           const Vec3<size_t> &size, DeviceBitfield memoryBanks);
};

} // namespace NEO