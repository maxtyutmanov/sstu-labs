#include "manual_reset_event.h"

manual_reset_event::manual_reset_event(bool signaled)
    : signaled_(signaled) {}

void manual_reset_event::set() {
    {
        boost::lock_guard<boost::mutex> lock(m_);
        signaled_ = true;
    }

    // Notify all because until the event is manually
    // reset, all waiters should be able to see event signalling
    cv_.notify_all();
}

void manual_reset_event::unset() {
    boost::lock_guard<boost::mutex> lock(m_);
    signaled_ = false;
}

void manual_reset_event::wait() {
    boost::unique_lock<boost::mutex> lock(m_);
    while (!signaled_) {
        cv_.wait(lock);
    }
}