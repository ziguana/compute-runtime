/*
 * Copyright (C) 2020-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/direct_submission/dispatchers/dispatcher.h"

namespace NEO {

struct RootDeviceEnvironment;

template <typename GfxFamily>
class BlitterDispatcher : public Dispatcher<GfxFamily> {
  public:
    static void dispatchPreemption(LinearStream &cmdBuffer);
    static size_t getSizePreemption();

    static void dispatchMonitorFence(LinearStream &cmdBuffer,
                                     uint64_t gpuAddress,
                                     uint64_t immediateData,
                                     const HardwareInfo &hwInfo,
                                     bool useNotifyEnable,
                                     bool partitionedWorkload,
                                     bool dcFlushRequired);
    static size_t getSizeMonitorFence(const HardwareInfo &hwInfo);

    static void dispatchCacheFlush(LinearStream &cmdBuffer, const RootDeviceEnvironment &rootDeviceEnvironment, uint64_t address);
    static void dispatchTlbFlush(LinearStream &cmdBuffer, uint64_t address, const HardwareInfo &hwInfo);
    static size_t getSizeCacheFlush(const HardwareInfo &hwInfo);
    static size_t getSizeTlbFlush();
    static bool isMultiTileSynchronizationSupported() {
        return false;
    }
};
} // namespace NEO
