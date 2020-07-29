/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "global_operations_imp.h"

#include "shared/source/helpers/basic_math.h"
#include "shared/source/helpers/debug_helpers.h"

#include "level_zero/core/source/device/device.h"

namespace L0 {

ze_result_t GlobalOperationsImp::processesGetState(uint32_t *pCount, zes_process_state_t *pProcesses) {
    std::vector<zes_process_state_t> pProcessList;
    ze_result_t result = pOsGlobalOperations->scanProcessesState(pProcessList);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    if ((*pCount > 0) && (*pCount < pProcessList.size())) {
        result = ZE_RESULT_ERROR_INVALID_SIZE;
    }
    if (pProcesses != nullptr) {
        uint32_t limit = std::min(*pCount, static_cast<uint32_t>(pProcessList.size()));
        for (uint32_t i = 0; i < limit; i++) {
            pProcesses[i].processId = pProcessList[i].processId;
            pProcesses[i].engines = pProcessList[i].engines;
            pProcesses[i].memSize = pProcessList[i].memSize;
        }
    }
    *pCount = static_cast<uint32_t>(pProcessList.size());

    return result;
}

ze_result_t GlobalOperationsImp::reset() {
    return pOsGlobalOperations->reset();
}

void GlobalOperationsImp::init() {
    if (pOsGlobalOperations == nullptr) {
        pOsGlobalOperations = OsGlobalOperations::create(pOsSysman);
    }
    UNRECOVERABLE_IF(nullptr == pOsGlobalOperations);
}

GlobalOperationsImp::~GlobalOperationsImp() {
    if (nullptr != pOsGlobalOperations) {
        delete pOsGlobalOperations;
    }
}

} // namespace L0
