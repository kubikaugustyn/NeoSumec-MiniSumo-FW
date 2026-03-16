//
// Created by Jakub Augustýn on 16.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "hardware/RC5Receiver.h"

#include "strategy/debug/logging.h"

void RC5Receiver::begin(const uint8_t receiverPin, const rmt_channel_t ch, const Handler h) {
    pin = receiverPin;
    channel = ch;
    handler = h;

    const rmt_config_t rmt_rx_config = RMT_DEFAULT_CONFIG_RX(static_cast<gpio_num_t>(pin), channel);
    rmt_config(&rmt_rx_config);
    rmt_driver_install(channel, 1000, 0);
    ir_parser_config_t ir_parser_config = IR_PARSER_DEFAULT_CONFIG(reinterpret_cast<ir_dev_t>(channel));
    ir_parser_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using an extended IR protocol
    parser = ir_parser_rmt_new_rc5(&ir_parser_config);

    // Get the RMT RX ringbuffer
    rmt_get_ringbuf_handle(channel, &ringbuf);
    // assert(ringbuf != NULL);

    // Start receiving
    rmt_rx_start(channel, true);
}

void RC5Receiver::onReceive(const Handler h) {
    handler = h;
}

void RC5Receiver::update() const {
    if (!ringbuf)
        return;

    size_t length = 0;
    const auto items = static_cast<rmt_item32_t *>(xRingbufferReceive(ringbuf, &length, portMAX_DELAY));
    if (!items) return;
    const size_t count = length / sizeof(rmt_item32_t); // one RMT = 4 Bytes
    if (parser->input(parser, items, count) == ESP_OK) {
        RC5Message msg;
        if (parser->get_scan_code(parser, &msg.address, &msg.command, &msg.repeat) == ESP_OK) {
            // ESP_LOGI(TAG, "Scan Code %s --- addr: 0x%04x cmd: 0x%04x", repeat ? "(repeat)" : "", addr, cmd);
            LOG_DEBUG_PRINTF("Scan Code %s --- addr: 0x%04x cmd: 0x%04x", repeat ? "(repeat)" : "", addr, cmd);
            if (handler)
                handler(msg);
        }
    }

    // After parsing the data, we must return memory to the ring buffer.
    vRingbufferReturnItem(ringbuf, items);
}

RC5Receiver::~RC5Receiver() {
    parser->del(parser);
    rmt_driver_uninstall(channel);
}
