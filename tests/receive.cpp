#include "socketcan/socketcan.h"

#include <iostream>
#include <thread>

int main() {
    transport::SocketCan s_can;
    s_can.run();
    while(true) {
        s_can.read();
    }
    return 0;
}
