//
//  server.cpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#include "server.hpp"

#define TRUE 1


void run_protocol_on_client(Protocol* p, Client* client) {
    p->run(client);
};

void Server::attach_protocol(Protocol *p) {
    this->protocol = p;
};

int Server::listen(unsigned int port) {
    int main_socket = socket(AF_INET, SOCK_STREAM , IPPROTO_IP);
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    int addrlen = sizeof(addr);
    
    bind(main_socket, (struct sockaddr *)&addr, addrlen);
    
    ::listen(main_socket, SOMAXCONN);
    
    std::cout << "Server running on port: " << port << std::endl;
    
    while (TRUE) {
        int client_socket = accept(main_socket, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
        
        Client client(client_socket, addr);
        clients[client_socket] = &client;
        
        std::thread client_thread(run_protocol_on_client, protocol, &client);
        client_thread.detach();
    }
    
    return 0;
};

void Server::stop() {
    
};
