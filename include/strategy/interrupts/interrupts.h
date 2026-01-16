//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "MainConfig.h" // Don't remove!

bool processInterrupts(StateMachine *machine);

struct InterruptResultData {
    InterruptCause cause;
};