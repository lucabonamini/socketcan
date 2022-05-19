#include "socketcan/socketcan.h"

#include <iostream>
#include <cstring>
#include <thread>

int main() {
    transport::SocketCan s_can;
    can_frame frame;
    s_can.open_socket();
    s_can.initialize_socket();
    while(true) {
        frame.can_id = 0x555;
        frame.can_dlc = 5;
        memcpy(frame.data, "Hello", frame.can_dlc);
        s_can.write(frame);
        memset(frame.data, 0, sizeof(frame.data));
        memset(frame.data, 0, frame.can_dlc);
    }
    return 0;
}
