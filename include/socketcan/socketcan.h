#pragma once

#include <errno.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr const char* can_interface = "vcan0"; 

namespace transport {
class SocketCan {
public:
SocketCan() = default;
SocketCan(const SocketCan&) = delete;
SocketCan(SocketCan&&) = delete;
~SocketCan() = default;
bool run();
/**
 * @brief Open Socket channel
 * 
 * @return true 
 * @return false 
 */
bool open_socket();
/**
 * @brief Close Socket channel
 * 
 * @return true 
 * @return false 
 */
bool close_socket() const;
/**
 * @brief Initialize Socket channel
 * 
 * @return true 
 * @return false 
 */
bool initialize_socket() const;
// read msg
bool read();
// write msg
bool write(const can_frame& frame) const;
private:
int socket_descriptor_;
};
} // namespace transport