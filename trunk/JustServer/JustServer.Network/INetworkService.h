#ifndef INETWORKSERVICE_H
#define INETWORKSERVICE_H

//Listening for incoming TCP connections and dispatches received requests to the 
//protocol specific subsystem in the form of sockets. Also could maintain connection pool.
class INetworkService {
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
};

#endif