#include <events/events.h>


namespace pn::events {

// ---- Event Handler ---- 

EventHandler::EventHandler(EventType event_type, std::function<void(void)> callback) 
        : _event_type_filter(event_type),
          _on_event(std::move(callback))
    {}


void EventHandler::operator()(const Event& event) {
    std::ignore = event;
    _on_event();
}



// ---- Event Loop ---- 

void EventLoop::add_handler(EventHandler&& handler) {
    _handlers.push_back(std::move(handler));
}


void EventLoop::trigger_event(Event& event) {
    for (auto& handler : _handlers) {
        if (!handler.is_type(event.type)) {
            continue;
        }

        handler(event);
    }
}

} // namespace pn::events
