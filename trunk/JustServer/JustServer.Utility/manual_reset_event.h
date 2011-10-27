#ifndef MANUAL_RESET_EVENT_H
#define MANUAL_RESET_EVENT_H

#include <boost/thread.hpp>

//TODO: truth be told, I don't know what's happening here... :-)

class manual_reset_event
{
public:
    manual_reset_event(bool signaled = false);
    void set();
    void unset();
    void wait();
private:
    boost::mutex m_;
    boost::condition_variable cv_;
    bool signaled_;
};

#endif