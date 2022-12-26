#pragma once

#ifndef EVENT_H
#define EVENT_H

typedef struct event_context {
    // 128 bytes
    union {
        /** @brief An array of 2 64-bit signed integers. */
        i64 i64[2];
        /** @brief An array of 2 64-bit unsigned integers. */
        u64 u64[2];

        /** @brief An array of 2 64-bit floating-point numbers. */
        f64 f64[2];

        /** @brief An array of 4 32-bit signed integers. */
        i32 i32[4];
        /** @brief An array of 4 32-bit unsigned integers. */
        u32 u32[4];
        /** @brief An array of 4 32-bit floating-point numbers. */
        f32 f32[4];

        /** @brief An array of 8 16-bit signed integers. */
        i16 i16[8];

        /** @brief An array of 8 16-bit unsigned integers. */
        u16 u16[8];

        /** @brief An array of 16 8-bit signed integers. */
        i8 i8[16];
        /** @brief An array of 16 8-bit unsigned integers. */
        u8 u8[16];

        /** @brief An array of 16 characters. */
        char c[16];
    } data;
} event_context;

typedef b8(*PFN_on_event) (u16 code, void* sender, void* listener_inst, event_context context);

KAPI void initialize_event_system();
KAPI void shutdown_event_system();

KAPI b8 event_register(u16 code, void* listener, PFN_on_event on_event);

KAPI b8 event_fire(u16 code, void* sender, event_context context);

#endif // !EVENT_H


