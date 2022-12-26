#include "pch.h"
#include "event.h"

#include <map>
#include <vector>

#define MAX_MESSAGE_CODES 16384

typedef struct registered_event
{
    void* listener;
    PFN_on_event callback;
} registered_event;

typedef struct event_code_entry 
{
    std::vector<registered_event> events;
}event_code_entry;

typedef struct event_system_state 
{
    event_code_entry registered[MAX_MESSAGE_CODES];
}event_system_state;

static event_system_state* state_ptr;

void initialize_event_system() 
{
    state_ptr = new event_system_state;


}

void shutdown_event_system()
{
    state_ptr->registered->events.clear();

    delete state_ptr;
}

b8 event_register(u16 code, void* listener, PFN_on_event on_event)
{
    registered_event reg;
    reg.listener = listener;
    reg.callback = on_event;

    state_ptr->registered[code].events.push_back(reg);

    return true;
}

b8 event_fire(u16 code, void* sender, event_context context)
{
    if(state_ptr->registered[code].events.size() == 0) return false;

    for (auto j : state_ptr->registered[code].events)
    {
        j.callback(code, sender, j.listener, context);
    }


    return false;
}
