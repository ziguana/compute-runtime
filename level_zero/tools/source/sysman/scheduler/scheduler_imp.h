/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/helpers/non_copyable_or_moveable.h"

#include <level_zero/zes_api.h>

#include "os_scheduler.h"
#include "scheduler.h"

namespace L0 {

class SchedulerImp : public Scheduler, NEO::NonCopyableOrMovableClass {
  public:
    void init() override;
    ze_result_t getCurrentMode(zes_sched_mode_t *pMode) override;
    ze_result_t getTimeoutModeProperties(ze_bool_t getDefaults, zes_sched_timeout_properties_t *pConfig) override;
    ze_result_t getTimesliceModeProperties(ze_bool_t getDefaults, zes_sched_timeslice_properties_t *pConfig) override;
    ze_result_t setTimeoutMode(zes_sched_timeout_properties_t *pProperties, ze_bool_t *pNeedReboot) override;
    ze_result_t setTimesliceMode(zes_sched_timeslice_properties_t *pProperties, ze_bool_t *pNeedReboot) override;
    ze_result_t setExclusiveMode(ze_bool_t *pNeedReboot) override;
    ze_result_t setComputeUnitDebugMode(ze_bool_t *pNeedReboot) override;

    SchedulerImp() = default;
    OsScheduler *pOsScheduler = nullptr;
    SchedulerImp(OsSysman *pOsSysman) : pOsSysman(pOsSysman) { pOsScheduler = nullptr; };
    ~SchedulerImp() override;

  private:
    OsSysman *pOsSysman = nullptr;
};

} // namespace L0
