//
// Created by Jakub Augustýn on 16.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

// IRremote import and configuration
#define RAW_BUFFER_LENGTH 100
// These are not necessary, as we specify the protocols we want
// #define EXCLUDE_EXOTIC_PROTOCOLS
// #define EXCLUDE_UNIVERSAL_PROTOCOLS
// #define DEBUG // FIXME Remove
#define DECODE_RC5
#define TOLERANCE_FOR_DECODERS_MARK_OR_SPACE_MATCHING 30
#include <IRremote.hpp>

// Other imports
#include "hardware/RC5Receiver.h"

#include "MainConfig.h"
#include "strategy/debug/logging.h"

RC5Receiver *RC5Receiver::instance = nullptr;

void RC5Receiver::begin(const uint8_t receiverPin, const Handler h) {
    // https://github.com/Arduino-IRremote/Arduino-IRremote/blob/b40476b8443decb6ad97c1b96da0d4d1cbae1466/examples/CallbackDemo/CallbackDemo.ino#L76-L95
    assert(instance == nullptr);
    instance = this;
    pin = receiverPin;
    handler = h;

    // Start the receiver
    IrReceiver.begin(pin, DISABLE_LED_FEEDBACK);

    // Tell the ISR to call this function when a complete frame has been received
    // IrReceiver.registerReceiveCompleteCallback(receiveCompleteCallback);

#if LOG_LEVEL >= LOG_DEBUG
    LOG_DEBUG_PRINT("Ready to receive IR signals of protocols: ");
    printActiveIRProtocols(&Serial);
    LOG_DEBUG_PRINTF("at pin %d", pin);
    // LOG_DEBUG_PRINT("Using callback function for processing received data");
#endif
}

void RC5Receiver::onReceive(const Handler h) {
    handler = h;
}

void RC5Receiver::update() const {
    if (IrReceiver.decode()) {
        LOG_DEBUG_PRINT("RC5Receiver::update(): Decoded!!!");
        IrReceiver.resume();
        IrReceiver.printIRResultShort(&Serial);
    }
}

void RC5Receiver::receiveCompleteCallback() {
    // https://github.com/Arduino-IRremote/Arduino-IRremote/blob/b40476b8443decb6ad97c1b96da0d4d1cbae1466/examples/CallbackDemo/CallbackDemo.ino#L139-L173
    IrReceiver.decode();
    LOG_DEBUG_PRINT("RC5Receiver::receiveCompleteCallback()");
    if (IrReceiver.decodedIRData.protocol == RC5) {
        const RC5Message message = {
            .address = IrReceiver.decodedIRData.address,
            .command = IrReceiver.decodedIRData.command,
            .repeat = false
        };
        LOG_DEBUG_PRINTF("Received a RC5 payload: address=%d, command=%d", message.address, message.command);

        if (instance->handler != nullptr)
            instance->handler(message);
    }

    IrReceiver.resume();
}

RC5Receiver::~RC5Receiver() {
}
