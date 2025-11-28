#include <events/event-loop.h>

#include <iostream>


int main() {
    using namespace pn::events;
    EventLoop loop;

    loop.add_handler({ 
        EventType::first, 
        []() { 
            std::cout << "Event loop is working!" << std::endl;
        } 
    });

    Event event = { EventType::first };
    loop.trigger_event(event);
}
