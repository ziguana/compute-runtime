/*
 * Copyright (C) 2019-2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/core/source/cmdlist/cmdlist.h"
#include "level_zero/core/source/device/device.h"
#include "level_zero/core/source/driver/driver_handle.h"
#include <level_zero/ze_api.h>

struct _ze_event_handle_t {};

struct _ze_event_pool_handle_t {};

namespace L0 {
typedef uint64_t FlushStamp;
struct EventPool;
struct MetricStreamer;

struct Event : _ze_event_handle_t {
    virtual ~Event() = default;
    virtual ze_result_t destroy();
    virtual ze_result_t hostSignal() = 0;
    virtual ze_result_t hostSynchronize(uint64_t timeout) = 0;
    virtual ze_result_t queryStatus() = 0;
    virtual ze_result_t reset() = 0;
    virtual ze_result_t queryKernelTimestamp(ze_kernel_timestamp_result_t *dstptr) = 0;

    enum State : uint32_t {
        STATE_SIGNALED = 0u,
        STATE_CLEARED = static_cast<uint32_t>(-1),
        STATE_INITIAL = STATE_CLEARED
    };

    static Event *create(EventPool *eventPool, const ze_event_desc_t *desc, Device *device);

    static Event *fromHandle(ze_event_handle_t handle) { return static_cast<Event *>(handle); }

    inline ze_event_handle_t toHandle() { return this; }

    virtual NEO::GraphicsAllocation &getAllocation();

    uint64_t getGpuAddress() { return gpuAddress; }
    uint64_t getOffsetOfEventTimestampRegister(uint32_t eventTimestampReg);

    void *hostAddress = nullptr;
    uint64_t gpuAddress;

    ze_event_scope_flags_t signalScope; // Saving scope for use later
    ze_event_scope_flags_t waitScope;

    bool isTimestampEvent = false;

    // Metric streamer instance associated with the event.
    MetricStreamer *metricStreamer = nullptr;

    NEO::CommandStreamReceiver *csr = nullptr;

  protected:
    NEO::GraphicsAllocation *allocation = nullptr;
};

struct KernelTimestampEvent {
    uint32_t contextStart = Event::STATE_INITIAL;
    uint32_t globalStart = Event::STATE_INITIAL;
    uint32_t contextEnd = Event::STATE_INITIAL;
    uint32_t globalEnd = Event::STATE_INITIAL;
};

struct EventPool : _ze_event_pool_handle_t {
    static EventPool *create(DriverHandle *driver, uint32_t numDevices, ze_device_handle_t *phDevices, const ze_event_pool_desc_t *desc);
    virtual ~EventPool() = default;
    virtual ze_result_t destroy() = 0;
    virtual ze_result_t getIpcHandle(ze_ipc_event_pool_handle_t *pIpcHandle) = 0;
    virtual ze_result_t closeIpcHandle() = 0;
    virtual ze_result_t createEvent(const ze_event_desc_t *desc, ze_event_handle_t *phEvent) = 0;
    virtual Device *getDevice() = 0;

    static EventPool *fromHandle(ze_event_pool_handle_t handle) {
        return static_cast<EventPool *>(handle);
    }

    inline ze_event_pool_handle_t toHandle() { return this; }

    virtual NEO::GraphicsAllocation &getAllocation() { return *eventPoolAllocation; }

    virtual uint32_t getEventSize() = 0;

    bool isEventPoolUsedForTimestamp = false;

  protected:
    NEO::GraphicsAllocation *eventPoolAllocation = nullptr;
};

} // namespace L0
