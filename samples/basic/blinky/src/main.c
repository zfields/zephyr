/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

// Include Notecard note-c library
#include "note.h"

// Notecard node-c helper methods
#include "notecard.h"

// Set your ProductUID Here
#define PRODUCT_UID "com.zakoverflow.test"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   10000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void)
{
	int ret;

    // Initialize note-c references
    NoteSetFnDefault(malloc, free, platform_delay, platform_millis);
    NoteSetFnI2C(NOTE_I2C_ADDR_DEFAULT, NOTE_I2C_MAX_DEFAULT, noteI2cReset,
                 noteI2cTransmit, noteI2cReceive);

    // Send a Notecard hub.set using note-c
    {
        J *req = NoteNewRequest("hub.set");
        if (req) {
            JAddStringToObject(req, "product", PRODUCT_UID);
            JAddStringToObject(req, "mode", "continuous");
            JAddStringToObject(req, "sn", "zephyr-blink");
            if (!NoteRequest(req)) {
                return;
            }
        } else { return; }
    }

	if (!gpio_is_ready_dt(&led)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
        {
            J *req = NoteNewRequest("hub.log");
            if (req) {
                JAddStringToObject(req, "text", "Hello, World!");
                JAddBoolToObject(req, "sync", true);
                if (!NoteRequest(req)) {
                    return;
                }
            } else { return; }
        }

		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);
	}
}
