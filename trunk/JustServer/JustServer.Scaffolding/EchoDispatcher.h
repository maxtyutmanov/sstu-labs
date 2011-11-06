#ifndef ECHODISPATCHER_H
#define ECHODISPATCHER_H

#include <IRequestDispatcher.h>

class EchoDispatcher : public JustServer::Net::IRequestDispatcher {
    virtual void DispatchRequest(shared_ptr<tcp::socket> pSocket);
};

#endif