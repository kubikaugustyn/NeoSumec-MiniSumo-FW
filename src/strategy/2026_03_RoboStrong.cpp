//
// Created by Jakub Augustýn on 28.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "MainConfig.h"
#include "strategy/2026_03_RoboStrong.h"

#ifdef STRATEGY_NEOSUMEC_2026_03_ROBO_STRONG

void RoboStrongState::enter() {
    robot.drive.driveStraight(1.0f);
}

#endif // STRATEGY_NEOSUMEC_2026_03_ROBO_STRONG
