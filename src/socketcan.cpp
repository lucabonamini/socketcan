#include "socketcan/socketcan.h"

#include <glog/logging.h>
#include <iostream>

namespace transport {
bool SocketCan::run() {
    open_socket();
    initialize_socket();
    return true;
}
bool SocketCan::open_socket() {
    socket_descriptor_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socket_descriptor_ < 0) {
        LOG(ERROR) << "Error in create socket.";
        return false;
    }

    return true;
}
bool SocketCan::close_socket() const {
    close(socket_descriptor_);
    return true;
}
bool SocketCan::initialize_socket() const {
    struct sockaddr_can can_address {};
    struct ifreq network_device {};
    strcpy(network_device.ifr_ifrn.ifrn_name, "vcan0");
    ioctl(socket_descriptor_, SIOCGIFINDEX, &network_device);

    can_address.can_family = AF_CAN;
    can_address.can_ifindex = network_device.ifr_ifru.ifru_ivalue;

    if (bind(socket_descriptor_, (struct sockaddr*)&can_address, sizeof(can_address)) < 0) {
        return false;
    }

    return true;
}
bool SocketCan::read() {
    can_frame frame {};
	auto nbytes = ::read(socket_descriptor_, &frame, sizeof(struct can_frame));
 	if (nbytes < 0) {
		perror("Read");
		return false;
	}
	printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);
	for (auto i = 0; i < frame.can_dlc; i++) {
		printf("%02X ",frame.data[i]);
    }
	printf("\r\n");
    return true;
}
bool SocketCan::write(const can_frame& frame) const {
    if (::write(socket_descriptor_, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Write");
        return false;
	}
    return true;
}
} // namespace transport