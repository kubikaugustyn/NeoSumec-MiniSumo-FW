//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/interrupts.h"

// All interrupts
#include "strategy/interrupts/KeepInRing.h"

bool processInterrupts(StateMachine *machine) {
#ifndef INTERRUPT_KEEP_IN_RING_DISABLE
    if (processKeepInRingInterrupt(machine)) return true;
#endif

    return false;
}
