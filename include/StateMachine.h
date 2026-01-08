//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include <cstdint>
#include <cstddef>
#include <type_traits>
#include "hardware/Robot.h"

//---------------- State Forward Declaration ----------------
class StateMachine;

//------------------ Abstract State Class  ------------------
class State {
protected:
    StateMachine &machine;
    Robot &robot;

    State(StateMachine &m, Robot &r) : machine(m), robot(r) {
    }

public:
    State() = delete;

    // States are static, never deleted!!!
    virtual ~State() = default;

    virtual void enter() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};

/*
Usage:
class MyNewState : public BaseState {
    using BaseState::BaseState;
    void enter() override; // Used
    void update() override; // Used
    void exit() override {}; // For example unused
};
*/
class BaseState : public State {
public:
    BaseState(StateMachine &m, Robot &r) : State(m, r) {
    }
};

//---------------------- State Machine ----------------------
class StateMachine {
    Robot &robot;
    // The next state contains a pointer to the current state unless a transition is requested
    State *currentState = nullptr, *nextState = nullptr;
    // Scratch buffer, shared for all states
    alignas(std::max_align_t) uint8_t scratch[64]{};
    unsigned long stateStartTime = 0, currentStateDuration = 0;

public:
    StateMachine() = delete;

    explicit StateMachine(Robot &r) : robot(r) {
    }

    /**
     * @brief Sets the next state of the state machine.
     *
     * Creates a static instance of the specified state type and schedules it as the next state.
     * The transition will occur during the next update() call.
     *
     * The static instance ensures that we don't create new instances of states during runtime;
     * all states exist as static objects created at compile-time.
     *
     * @tparam StateType The type of the state to transition to. Must be derived from the State class.
     */
    template<typename StateType>
    void setState() {
        // This template function must be defined here in the header, otherwise the compiler will complain
        static_assert(std::is_base_of<State, StateType>::value, "StateType must derive from State");

        static StateType stateInstance(*this, robot);

        // Schedule the next state (for the next call of update())
        nextState = &stateInstance;
    }

    /**
     * @brief Clears the current state of the state machine.
     *
     * Sets the state machine's scheduled next state to nullptr, effectively clearing the
     * current state after the next update() call.
     */
    void clearState();

    /**
     * @brief Updates the state of the state machine.
     *
     * Executes the scheduled transition to the next state if one is requested.
     *
     * If transitioning, the current state's `exit()` method is called before transitioning to
     * the next state, and the next state's `enter()` method is called.
     *
     * Once the potential transition is complete, updates currentStateDuration and
     * calls the current state's `update()` method.
     */
    void update();

    // Funkce, která vezme typ a vrátí reference na něj z bufferu
    template<typename T>
    T &scratchRef() {
        static_assert(sizeof(T) <= sizeof(scratch), "Type too big for scratch buffer");
        static_assert(alignof(T) <= alignof(std::max_align_t), "Alignment too strict for scratch buffer");
        return *reinterpret_cast<T *>(scratch);
    }

    /**
     * @brief Returns the duration of the current state in milliseconds.
     * 
     * Calculates how long the state machine has been in its current state by tracking
     * the time elapsed since the last state transition.
     * 
     * @return The duration of the current state in milliseconds.
     */
    unsigned long getStateDuration() const;

    /**
     * @brief Returns a pointer to the current state of the state machine.
     * 
     * This method provides access to the current state object.
     * 
     * @return A pointer to the current State object, or nullptr if no state is set.
     */
    State *getState() const;

    /**
     * @brief Returns a pointer to the expected next state of the state machine.
     *
     * This method provides access to the expected next state object. This is the state
     * the machine will transition to when the `update()` method is called.
     *
     * It can still be changed by calling `setState()` before the next call to `update()`.
     *
     * @return A pointer to the expected next State object, or nullptr if no state is set.
     */
    State *getNextState() const;
};
