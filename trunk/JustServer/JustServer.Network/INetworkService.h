#ifndef INETWORKSERVICE_H
#define INETWORKSERVICE_H

/*The main purpose of this service is listening for incoming TCP connections on
the specific port. Once request arrives this service passes it to specific dispatcher
in the form of TCP socket. So, this service doesn't contain application specific details, 
just supporting the requests accepting in asynchronous manner*/
class INetworkService {
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
};

#endif