#ifndef NULL_LOGGER_H
#define NULL_LOGGER_H

#include <ILogger.h>

namespace JustServer {
namespace ServiceLocation {

    class NullLogger : public JustServer::Logging::ILogger {
    public:
        virtual void LogMessage(const JustServer::Logging::EventType::Enum eventType, const std::string& message) const {};
        virtual void LogMessage(const JustServer::Logging::EventType::Enum eventType, const std::wstring& message) const {};
    };

}
}

#endif