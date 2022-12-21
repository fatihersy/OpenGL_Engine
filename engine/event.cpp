#include "pch.h"
#include "event.h"

#include <map>

typedef struct registered_event
{
    void* listener;
    PFN_on_event callback;
} registered_event;

typedef struct event_code_entry
{
} event_code_entry;

//#define MAX_MESSAGE_CODES 16384
//
//typedef struct event_system_state 
//{
//    event_code_entry registered[MAX_MESSAGE_CODES];
//} event_system_state;

//static event_system_state* state_ptr;

std::multimap<u16, registered_event> events = {};

b8 event_register(u16 code, void* listener, PFN_on_event on_event)
{
    for (auto itr = events.begin(); itr != events.end(); ++itr)
    {
        if ((*itr).first == code) return false;
    }

    registered_event reg;
    reg.listener = listener;
    reg.callback = on_event;

    events.insert(std::pair(code, reg));

    return true;
}

b8 event_fire(u16 code, void* sender)
{
    if (events.size() == 0) return false;

    for (auto itr = events.begin(); itr != events.end(); ++itr)
    {
        if ((*itr).first == code)
        {
            (*itr).second.callback(code, sender, (*itr).second.listener);

            return true;
        }
    }

    return false;
}
