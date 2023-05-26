//
//  server.hpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#ifndef server_hpp
#define server_hpp

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <thread>

#include "client.hpp"
#include "protocol.hpp"


class Server {
private:
    struct sockaddr_in addr{};
    std::map<int, Client*> clients;
    
    Protocol* protocol;
    
public:
    void attach_protocol(Protocol* p);
    
    int listen(unsigned int port);
    
    void stop();
};

#endif /* server_hpp */
