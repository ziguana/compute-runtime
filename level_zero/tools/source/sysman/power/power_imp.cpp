/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero/tools/source/sysman/power/power_imp.h"

#include "shared/source/helpers/debug_helpers.h"

#include "level_zero/core/source/device/device.h"

#include <chrono>

namespace L0 {

void powerGetTimestamp(uint64_t &timestamp) {
    std::chrono::time_point<std::chrono::steady_clock> ts = std::chrono::steady_clock::now();
    timestamp = std::chrono::duration_cast<std::chrono::microseconds>(ts.time_since_epoch()).count();
}

ze_result_t PowerImp::powerSetEnergyThreshold(double threshold) {
    return (pOsPower->setEnergyThreshold(threshold));
}

ze_result_t PowerImp::powerGetProperties(zes_power_properties_t *pProperties) {
    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

ze_result_t PowerImp::powerGetEnergyCounter(zes_power_energy_counter_t *pEnergy) {

    ze_result_t result = pOsPower->getEnergyCounter(pEnergy->energy);

    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    powerGetTimestamp(pEnergy->timestamp);

    return result;
}

ze_result_t PowerImp::powerGetLimits(zes_power_sustained_limit_t *pSustained, zes_power_burst_limit_t *pBurst, zes_power_peak_limit_t *pPeak) {
    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}

ze_result_t PowerImp::powerSetLimits(const zes_power_sustained_limit_t *pSustained, const zes_power_burst_limit_t *pBurst, const zes_power_peak_limit_t *pPeak) {
    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
}
ze_result_t PowerImp::powerGetEnergyThreshold(zes_energy_threshold_t *pThreshold) {
    return (pOsPower->getEnergyThreshold(pThreshold));
}

PowerImp::PowerImp(OsSysman *pOsSysman) {
    pOsPower = OsPower::create(pOsSysman);
    UNRECOVERABLE_IF(nullptr == pOsPower);

    init();
}

void PowerImp::init() {
    this->initSuccess = pOsPower->isPowerModuleSupported();
}

PowerImp::~PowerImp() {
    if (nullptr != pOsPower) {
        delete pOsPower;
        pOsPower = nullptr;
    }
}

} // namespace L0
