//
//  protocol.hpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#ifndef protocol_hpp
#define protocol_hpp

#include <iostream>
#include <string>

#include "client.hpp"

#define MESSAGE_LENGTH 128
#define MAX_ATTEMTPS 8


class Protocol {
private:
    std::string name;
    Client* client;
    
public:
    Protocol(std::string name);
    
    std::string get_name();
    
    void run(Client* client);
    
    void run_protocol();
};

#endif /* protocol_hpp */
