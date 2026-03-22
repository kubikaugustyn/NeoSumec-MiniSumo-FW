//
// Created by Jakub Augustýn on 16.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// RC5 protocol specification: https://www.sbprojects.net/knowledge/ir/rc5.php
// ESP32 example: https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/CallbackDemo/CallbackDemo.ino#L126

#pragma once

struct RC5Message {
    uint16_t address;
    uint16_t command;
    bool repeat;
};

class RC5Receiver {
private:
    static RC5Receiver *instance;

    uint8_t pin = 0;
    RC5Message message; // So we don't reallocate memory

    static void receiveCompleteCallback();

public:
    using Handler = void (*)(const RC5Message *msg);

    RC5Receiver() = default;

    void begin(uint8_t receiverPin, Handler h);

private:
    Handler handler = nullptr;
};
