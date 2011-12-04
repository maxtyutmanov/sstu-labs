#ifndef I_LOGGER_H
#define I_LOGGER_H

#include <string>
#include "EventType.h"
    
namespace JustServer {
namespace Logging {

    class ILogger {
    public:
        virtual void LogMessage(const EventType::Enum eventType, const std::string& message) const = 0;
        virtual void LogMessage(const EventType::Enum eventType, const std::wstring& message) const = 0;
    };

}
}

#endif