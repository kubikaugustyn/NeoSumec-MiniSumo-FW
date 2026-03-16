//
// Created by Jakub Augustýn on 16.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// RC5 protocol specification: https://www.sbprojects.net/knowledge/ir/rc5.php
// ESP32 example: https://github.com/espressif/esp-idf/blob/v4.4/examples/peripherals/rmt/ir_protocols/main/ir_protocols_main.c
//
// We can't use the new version of RMT:
// https://docs.espressif.com/projects/esp-idf/en/v5.5.3/esp32/api-reference/peripherals/rmt.html
// due to PlatformIO's junk code not allowing whitespaces in the lib path and not allowing installation elsewhere.
// Thus, we have to use the old version included in the Arduino framework - rmt.h...
// At least the official example library it took me like two hours to find looks great!

#pragma once
#include "driver/rmt.h"
#include "freertos/ringbuf.h"
#include "lib/infrared_tools/ir_tools.h"

struct RC5Message {
    uint32_t address;
    uint32_t command;
    bool repeat;
};

class RC5Receiver {
private:
    uint8_t pin = 0;
    rmt_channel_t channel = RMT_CHANNEL_0;
    RingbufHandle_t ringbuf = nullptr;
    ir_parser_t *parser = nullptr;

public:
    using Handler = void (*)(const RC5Message &msg);

    RC5Receiver() = default;

    void begin(uint8_t receiverPin, rmt_channel_t ch, Handler h);

    void onReceive(Handler h);

    void update() const;

    ~RC5Receiver();

private:
    Handler handler = nullptr;
};
