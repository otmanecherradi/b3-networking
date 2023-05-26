//
//  client.cpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#include "client.hpp"


Client::Client(int socket, sockaddr_in &addr) {
    this->socket = socket;
    this->addr = addr;
    
    std::cout << "New client detected on port: " << ntohs(this->addr.sin_port) << std::endl;
};


void Client::initiate_connection() {
    std::string value = receive(5);
    
    if(value == "HELLO")
        send("WELCOME");
};

void Client::send(std::string message) {
    std::cout << "Sending:: " << message << std::endl;
    
    char const* buffer = message.c_str();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ::send(socket, buffer, strlen(buffer), 0);
};

std::string Client::receive(int length) {
    char buffer[length + 1];
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto i = ::recv(this->socket, buffer, length + 1, 0);
    std::cout << "i:: " << i << std::endl;
    buffer[i] = 0;
    std::string res(buffer, length);
    
    std::cout << "Received:: " << res << std::endl;
    
    return res;
};

bool Client::is_closed() {
    char buffer[1];
    return read(socket, buffer, 1) == 0;
};

void Client::disconnect() {
    close(socket);
    std::cout << "Client disconnected on port: " << ntohs(addr.sin_port) << std::endl;
};
