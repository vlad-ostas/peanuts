#pragma once 

#include <unordered_map>
#include <vector>
#include <string>


namespace events {

enum class EventType {
    first,
    second,
    third
};


struct Event {
    std::string name;
    EventType type;
};


class EventHandler;

/// 
class EventLoop {
public:
    /// Adds an entry to _handlers container
    void register_handler(EventHandler& handler);

    /// Checks for pending events in queue.
    /// If any, dispatches all
    void check_pending() const;
    /// Dispatches all pending events.
    /// When an event is dispatched to a handler,
    ///     handler is triggered to process the event
    void dispatch();

private:
    /// Triggers a handler to process an event
    void _handle(EventHandler& handler) const;

private:
    /// Event FIFO container
    std::vector<Event> _event_queue;
    /// A register of known handlers
    std::vector<std::reference_wrapper<EventHandler>> _handlers;
};


class EventHandler {
public:
    EventHandler() = delete;
    EventHandler(EventLoop& loop, std::initializer_list<EventType> event_type_filter_list = {});

    virtual ~EventHandler();

    virtual void handle(const Event& event);

private:
    std::vector<EventType> event_type_filter;
};

} // namespace events
