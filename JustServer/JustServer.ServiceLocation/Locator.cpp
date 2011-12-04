#include "Locator.h"


namespace JustServer {
namespace ServiceLocation {

    NullLogger Locator::nullLogger;
    JustServer::Logging::ILogger* Locator::pLogger = &nullLogger;

    void Locator::Register(JustServer::Logging::ILogger* pLogger) {
        if (pLogger != NULL) {
            Locator::pLogger = pLogger;
        }
    }

    JustServer::Logging::ILogger* Locator::GetLogger() {
        return pLogger;
    }


}
}