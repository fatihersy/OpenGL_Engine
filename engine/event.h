#pragma once

#ifndef EVENT_H
#define EVENT_H

typedef b8(*PFN_on_event) (u16 code, void* sender, void* listener_inst);

KAPI b8 event_register(u16 code, void* listener, PFN_on_event on_event);

KAPI b8 event_fire(u16 code, void* sender);

#endif // !EVENT_H


