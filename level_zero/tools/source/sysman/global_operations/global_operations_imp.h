/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/helpers/non_copyable_or_moveable.h"

#include <level_zero/zet_api.h>

#include "global_operations.h"
#include "os_global_operations.h"

#include <vector>

namespace L0 {

class GlobalOperationsImp : public GlobalOperations, NEO::NonCopyableOrMovableClass {
  public:
    void init() override;
    ze_result_t reset() override;
    ze_result_t processesGetState(uint32_t *pCount, zes_process_state_t *pProcesses) override;

    OsGlobalOperations *pOsGlobalOperations = nullptr;
    ze_device_handle_t hCoreDevice = {};

    GlobalOperationsImp() = default;
    GlobalOperationsImp(OsSysman *pOsSysman, ze_device_handle_t hCoreDevice) : hCoreDevice(hCoreDevice),
                                                                               pOsSysman(pOsSysman){};
    ~GlobalOperationsImp() override;

  private:
    OsSysman *pOsSysman = nullptr;
};

} // namespace L0
