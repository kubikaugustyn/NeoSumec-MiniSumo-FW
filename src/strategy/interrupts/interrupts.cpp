//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/interrupts.h"

// All interrupts
#include "strategy/interrupts/StartRobot.h"
#include "strategy/interrupts/KeepInRingFront.h"
#include "strategy/interrupts/KeepInRingBack.h"

bool processInterrupts(StateMachine *machine) {
#ifndef INTERRUPT_KEEP_IN_RING_DISABLE
    // The rear QRE has the highest priority
    if (processKeepInRingBackInterrupt(machine)) return true;
    // Then come the front QREs
    if (processKeepInRingFrontInterrupt(machine)) return true;
#endif

    return false;
}
