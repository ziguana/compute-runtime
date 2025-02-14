/*
 * Copyright (C) 2020-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/source/helpers/common_types.h"
#include "shared/source/memory_manager/memory_manager.h"
#include "shared/source/utilities/stackvec.h"

#include "level_zero/core/source/context/context.h"

#include <map>

namespace L0 {
struct StructuresLookupTable;
struct DriverHandleImp;
struct Device;

#pragma pack(1)
struct IpcMemoryData {
    uint64_t handle = 0;
    uint8_t type = 0;
};
#pragma pack()
static_assert(sizeof(IpcMemoryData) <= ZE_MAX_IPC_HANDLE_SIZE, "IpcMemoryData is bigger than ZE_MAX_IPC_HANDLE_SIZE");

struct ContextImp : Context {
    ContextImp(DriverHandle *driverHandle);
    ~ContextImp() override = default;
    ze_result_t destroy() override;
    ze_result_t getStatus() override;
    DriverHandle *getDriverHandle() override;
    ze_result_t allocHostMem(const ze_host_mem_alloc_desc_t *hostDesc,
                             size_t size,
                             size_t alignment,
                             void **ptr) override;
    ze_result_t allocDeviceMem(ze_device_handle_t hDevice,
                               const ze_device_mem_alloc_desc_t *deviceDesc,
                               size_t size,
                               size_t alignment, void **ptr) override;
    ze_result_t allocSharedMem(ze_device_handle_t hDevice,
                               const ze_device_mem_alloc_desc_t *deviceDesc,
                               const ze_host_mem_alloc_desc_t *hostDesc,
                               size_t size,
                               size_t alignment,
                               void **ptr) override;
    ze_result_t freeMem(const void *ptr) override;
    ze_result_t freeMem(const void *ptr, bool blocking) override;
    ze_result_t freeMemExt(const ze_memory_free_ext_desc_t *pMemFreeDesc,
                           void *ptr) override;
    ze_result_t makeMemoryResident(ze_device_handle_t hDevice,
                                   void *ptr,
                                   size_t size) override;
    ze_result_t evictMemory(ze_device_handle_t hDevice,
                            void *ptr,
                            size_t size) override;
    ze_result_t makeImageResident(ze_device_handle_t hDevice, ze_image_handle_t hImage) override;
    ze_result_t evictImage(ze_device_handle_t hDevice, ze_image_handle_t hImage) override;
    ze_result_t getMemAddressRange(const void *ptr,
                                   void **pBase,
                                   size_t *pSize) override;
    ze_result_t closeIpcMemHandle(const void *ptr) override;
    ze_result_t getIpcMemHandle(const void *ptr,
                                ze_ipc_mem_handle_t *pIpcHandle) override;
    ze_result_t openIpcMemHandle(ze_device_handle_t hDevice,
                                 const ze_ipc_mem_handle_t &handle,
                                 ze_ipc_memory_flags_t flags,
                                 void **ptr) override;

    ze_result_t
    getIpcMemHandles(
        const void *ptr,
        uint32_t *numIpcHandles,
        ze_ipc_mem_handle_t *pIpcHandles) override;

    ze_result_t
    openIpcMemHandles(
        ze_device_handle_t hDevice,
        uint32_t numIpcHandles,
        ze_ipc_mem_handle_t *pIpcHandles,
        ze_ipc_memory_flags_t flags,
        void **pptr) override;

    ze_result_t getMemAllocProperties(const void *ptr,
                                      ze_memory_allocation_properties_t *pMemAllocProperties,
                                      ze_device_handle_t *phDevice) override;
    ze_result_t getImageAllocProperties(Image *image,
                                        ze_image_allocation_ext_properties_t *pAllocProperties) override;
    ze_result_t createModule(ze_device_handle_t hDevice,
                             const ze_module_desc_t *desc,
                             ze_module_handle_t *phModule,
                             ze_module_build_log_handle_t *phBuildLog) override;
    ze_result_t createSampler(ze_device_handle_t hDevice,
                              const ze_sampler_desc_t *pDesc,
                              ze_sampler_handle_t *phSampler) override;
    ze_result_t createCommandQueue(ze_device_handle_t hDevice,
                                   const ze_command_queue_desc_t *desc,
                                   ze_command_queue_handle_t *commandQueue) override;
    ze_result_t createCommandList(ze_device_handle_t hDevice,
                                  const ze_command_list_desc_t *desc,
                                  ze_command_list_handle_t *commandList) override;
    ze_result_t createCommandListImmediate(ze_device_handle_t hDevice,
                                           const ze_command_queue_desc_t *desc,
                                           ze_command_list_handle_t *commandList) override;
    ze_result_t activateMetricGroups(zet_device_handle_t hDevice,
                                     uint32_t count,
                                     zet_metric_group_handle_t *phMetricGroups) override;
    ze_result_t reserveVirtualMem(const void *pStart,
                                  size_t size,
                                  void **pptr) override;
    ze_result_t freeVirtualMem(const void *ptr,
                               size_t size) override;
    ze_result_t queryVirtualMemPageSize(ze_device_handle_t hDevice,
                                        size_t size,
                                        size_t *pagesize) override;
    ze_result_t createPhysicalMem(ze_device_handle_t hDevice,
                                  ze_physical_mem_desc_t *desc,
                                  ze_physical_mem_handle_t *phPhysicalMemory) override;
    ze_result_t destroyPhysicalMem(ze_physical_mem_handle_t hPhysicalMemory) override;
    ze_result_t mapVirtualMem(const void *ptr,
                              size_t size,
                              ze_physical_mem_handle_t hPhysicalMemory,
                              size_t offset,
                              ze_memory_access_attribute_t access) override;
    ze_result_t unMapVirtualMem(const void *ptr,
                                size_t size) override;
    ze_result_t setVirtualMemAccessAttribute(const void *ptr,
                                             size_t size,
                                             ze_memory_access_attribute_t access) override;
    ze_result_t getVirtualMemAccessAttribute(const void *ptr,
                                             size_t size,
                                             ze_memory_access_attribute_t *access,
                                             size_t *outSize) override;
    ze_result_t openEventPoolIpcHandle(const ze_ipc_event_pool_handle_t &ipcEventPoolHandle,
                                       ze_event_pool_handle_t *eventPoolHandle) override;
    ze_result_t createEventPool(const ze_event_pool_desc_t *desc,
                                uint32_t numDevices,
                                ze_device_handle_t *phDevices,
                                ze_event_pool_handle_t *phEventPool) override;
    ze_result_t createImage(ze_device_handle_t hDevice,
                            const ze_image_desc_t *desc,
                            ze_image_handle_t *phImage) override;

    std::map<uint32_t, ze_device_handle_t> &getDevices() {
        return devices;
    }

    void freePeerAllocations(const void *ptr, bool blocking, Device *device);

    ze_result_t handleAllocationExtensions(NEO::GraphicsAllocation *alloc, ze_memory_type_t type,
                                           void *pNext, struct DriverHandleImp *driverHandle);

    RootDeviceIndicesContainer rootDeviceIndices;
    std::map<uint32_t, NEO::DeviceBitfield> deviceBitfields;

    bool isDeviceDefinedForThisContext(Device *inDevice);
    bool isShareableMemory(const void *exportDesc, bool exportableMemory, NEO::Device *neoDevice) override;
    void *getMemHandlePtr(ze_device_handle_t hDevice, uint64_t handle, NEO::AllocationType allocationType, ze_ipc_memory_flags_t flags) override;

    void initDeviceHandles(uint32_t numDevices, ze_device_handle_t *deviceHandles) {
        this->numDevices = numDevices;
        if (numDevices > 0) {
            this->deviceHandles.assign(deviceHandles, deviceHandles + numDevices);
        }
    }
    void addDeviceHandle(ze_device_handle_t deviceHandle) {
        this->deviceHandles.push_back(deviceHandle);
        this->numDevices = static_cast<uint32_t>(this->deviceHandles.size());
    }

  protected:
    bool isAllocationSuitableForCompression(const StructuresLookupTable &structuresLookupTable, Device &device, size_t allocSize);
    size_t getPageSizeRequired(size_t size);

    std::map<uint32_t, ze_device_handle_t> devices;
    std::vector<ze_device_handle_t> deviceHandles;
    DriverHandleImp *driverHandle = nullptr;
    uint32_t numDevices = 0;
};

} // namespace L0
