#pragma once 

#include <vector>
#include <functional>


namespace pn::events {

enum class EventType {
    first,
    second,
    third
};


struct Event {
    EventType type;
};


/// Stores a callback and a needed EventType
class EventHandler {
public:
    EventHandler() = delete;
    EventHandler(EventType event_type, std::function<void(void)> callback);

    void operator()(const Event& event);

    bool is_type(EventType type) { return type == _event_type_filter; }

private:
    EventType _event_type_filter;
    std::function<void(void)> _on_event;
};


/// Stores Handlers and dispatches incoming Events to them
class EventLoop {
public:
    /// Adds a handler (event consumer)
    void add_handler(EventHandler&& handler);

    /// Triggers an event (called from event producer)
    void trigger_event(Event& event);

private:
    /// storage of added handlers
    std::vector<EventHandler> _handlers;
};

} // namespace pn::events
