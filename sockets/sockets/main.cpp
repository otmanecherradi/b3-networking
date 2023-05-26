//
//  main.cpp
//  sockets
//
//  Created by Otmane on 5/24/23.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define TRUE   1
#define PORT 5500

#include "server.hpp"
#include "protocol.hpp"

int main(int argc , char *argv[]) {
    Server s;
    Protocol calc_protocol("CALC");
    
    s.attach_protocol(&calc_protocol);
    
    s.listen(PORT);
    
    return 0;
}
