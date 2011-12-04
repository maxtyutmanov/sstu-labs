#ifndef SQL_SERVER_LOGGER_H
#define SQL_SERVER_LOGGER_H

#include "ILogger.h"

namespace JustServer {
namespace Logging {

    class SqlServerLogger : public ILogger {
    public:
        SqlServerLogger(const std::wstring& connectionString);

        virtual void LogMessage(const EventType::Enum eventType, const std::string& message) const;
        virtual void LogMessage(const EventType::Enum eventType, const std::wstring& message) const;

    private:
        std::wstring connectionString;
    };

}
}

#endif