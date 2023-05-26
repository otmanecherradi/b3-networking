//
//  protocol.cpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#include "protocol.hpp"

#define TRUE 1


enum Ops { ADD, SUB, DIV, MLP };
std::map<std::string, Ops> ops_map = {
    { "ADD", ADD },
    { "SUB", SUB },
    { "DIV", DIV },
    { "MLP", MLP },
};

Protocol::Protocol(std::string name) {
    this->name = name;
};

std::string Protocol::get_name() {
    return name;
};

void Protocol::run(Client* client) {
    this->client = client;
    
    std::cout << "running " << name << std::endl;
    
    client->initiate_connection();
    
    this->run_protocol();
    
    client->disconnect();
};

void Protocol::run_protocol() {
    while (TRUE) {
        std::string cmd = client->receive(3);
        
        if (cmd == "END")
            break;
        
        // 3 for the operation + 1 space + first_number + 1 space + second_number
        std::string statement = client->receive(3 + 1 + MESSAGE_LENGTH + 1 + MESSAGE_LENGTH);
        
        char* token = std::strtok(statement.data(), " ");
        std::string op = std::string(token);
        
        token = std::strtok(NULL, " ");
        std::string first_number_str = std::string(token);
        
        token = std::strtok(NULL, " ");
        std::string second_number_str = std::string(token);
        
        std::cout << "op " << op << std::endl;
        std::cout << "first_number_str " << first_number_str << std::endl;
        std::cout << "second_number_str " << second_number_str << std::endl;
        
        double first_number = std::stod(first_number_str);
        double second_number = std::stod(second_number_str);
        
        std::cout << "first_number " << first_number << std::endl;
        std::cout << "second_number " << second_number << std::endl;
        
        double result = 0;
        
        switch (ops_map[op]) {
            case ADD:
                result = first_number + second_number;
                break;
            case SUB:
                result = first_number - second_number;
                break;
            case MLP:
                result = first_number * second_number;
                break;
            case DIV:
                if(second_number != 0)
                    result = first_number / second_number;
                else
                    client->send("ERR INVALID_NUMBER");
                break;
            default:
                std::cout << "Undefined operation" << std::endl;
                break;
        }
        
        std::string result_str = std::to_string(result);
        result_str.insert(result_str.begin(), MESSAGE_LENGTH - result_str.size(), '0');
        client->send("RES " + result_str);
    }
};
