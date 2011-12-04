#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

namespace JustServer {
namespace Logging {

    struct EventType {
        enum Enum {
            Error = 1,
            ConnectionEstablished = 2,
            RequestAcceptedByHttpCore = 3,
            RequestHandled = 4
        };
    };

}
}

#endif