# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

# Create variables to alias path names
set(NOTE_C ${CMAKE_CURRENT_LIST_DIR}/note-c)
set(SRC ${CMAKE_CURRENT_LIST_DIR}/src)

# Let Zephyr build additional 3rd party libs (e.g. `note-c`) with `app`
target_sources(app
    PRIVATE ${NOTE_C}/n_atof.c
    PRIVATE ${NOTE_C}/n_b64.c
    PRIVATE ${NOTE_C}/n_cjson.c
    PRIVATE ${NOTE_C}/n_cjson_helpers.c
    PRIVATE ${NOTE_C}/n_const.c
    PRIVATE ${NOTE_C}/n_ftoa.c
    PRIVATE ${NOTE_C}/n_helpers.c
    PRIVATE ${NOTE_C}/n_hooks.c
    PRIVATE ${NOTE_C}/n_i2c.c
    PRIVATE ${NOTE_C}/n_md5.c
    PRIVATE ${NOTE_C}/n_printf.c
    PRIVATE ${NOTE_C}/n_request.c
    PRIVATE ${NOTE_C}/n_serial.c
    PRIVATE ${NOTE_C}/n_str.c
    PRIVATE ${NOTE_C}/n_ua.c
)

target_include_directories(app
    PRIVATE ${NOTE_C}
)

target_sources(app
    PRIVATE ${SRC}/main.c
    PRIVATE ${SRC}/notecard.c
)
