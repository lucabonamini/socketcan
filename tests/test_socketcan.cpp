#include "socketcan/socketcan.h"

#include <gtest/gtest.h>

TEST(SocketCan, OpenSocket) {
  transport::SocketCan s_can;
  EXPECT_TRUE(s_can.open_socket());
}

TEST(SocketCan, CloseSocket) {
  transport::SocketCan s_can;
  EXPECT_TRUE(s_can.close_socket());
}

TEST(SocketCan, InitializeSocket) {
  transport::SocketCan s_can;
  EXPECT_TRUE(s_can.initialize_socket());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}