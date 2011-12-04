#ifndef LOCATOR_H
#define LOCATOR_H

#include <ILogger.h>
#include "NullLogger.h"

namespace JustServer {
namespace ServiceLocation {

    class Locator {
    public:
        static void Register(JustServer::Logging::ILogger* pLogger);
        static JustServer::Logging::ILogger* GetLogger();

    private:
        static JustServer::Logging::ILogger* pLogger;
        static NullLogger nullLogger;
    };

}
}

#endif