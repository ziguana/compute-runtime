/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

namespace NEO {
enum class AllocationType {
    UNKNOWN = 0,
    BUFFER,
    BUFFER_HOST_MEMORY,
    COMMAND_BUFFER,
    CONSTANT_SURFACE,
    EXTERNAL_HOST_PTR,
    FILL_PATTERN,
    GLOBAL_SURFACE,
    IMAGE,
    INDIRECT_OBJECT_HEAP,
    INSTRUCTION_HEAP,
    INTERNAL_HEAP,
    INTERNAL_HOST_MEMORY,
    KERNEL_ARGS_BUFFER,
    KERNEL_ISA,
    KERNEL_ISA_INTERNAL,
    LINEAR_STREAM,
    MAP_ALLOCATION,
    MCS,
    PIPE,
    PREEMPTION,
    PRINTF_SURFACE,
    PRIVATE_SURFACE,
    PROFILING_TAG_BUFFER,
    SCRATCH_SURFACE,
    SHARED_BUFFER,
    SHARED_CONTEXT_IMAGE,
    SHARED_IMAGE,
    SHARED_RESOURCE_COPY,
    SURFACE_STATE_HEAP,
    SVM_CPU,
    SVM_GPU,
    SVM_ZERO_COPY,
    TAG_BUFFER,
    GLOBAL_FENCE,
    TIMESTAMP_PACKET_TAG_BUFFER,
    WRITE_COMBINED,
    RING_BUFFER,
    SEMAPHORE_BUFFER,
    DEBUG_CONTEXT_SAVE_AREA,
    DEBUG_SBA_TRACKING_BUFFER,
    DEBUG_MODULE_AREA,
    UNIFIED_SHARED_MEMORY,
    WORK_PARTITION_SURFACE,
    GPU_TIMESTAMP_DEVICE_BUFFER,
    SW_TAG_BUFFER,
    COUNT
};
} // namespace NEO
