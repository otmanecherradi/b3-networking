//
//  client.hpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#ifndef client_hpp
#define client_hpp

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <map>
#include <chrono>
#include <thread>


class Client {
private:
    int socket;
    sockaddr_in addr;
    
public:
    Client(int socket, sockaddr_in &adr);
    
    void initiate_connection();
    
    void send(std::string message);
    std::string receive(int length);
    
    bool is_closed();
    
    void disconnect();
};

#endif /* client_hpp */
