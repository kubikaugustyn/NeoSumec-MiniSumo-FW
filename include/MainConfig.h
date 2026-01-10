//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once

// Hardware to build for - enables different pin definitions
// Pins are then defined in include/hardware/Pins.h
#define PINOUT_NEOSUMEC_PINS_MK5
// #define PINOUT_NEOSUMEC_PINS_SOME_FUTURE_1
// #define PINOUT_NEOSUMEC_PINS_SOME_FUTURE_2

// The strategy to use
// #define STRATEGY_NEOSUMEC_2025_01_KEEP_RING
#define STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET

// Include all strategy headers. Only the single one enabled above will be compiled and used.
#include "strategy/2025_01_KeepRing.h"
#include "strategy/2026_01_FollowTarget.h"
