project(tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(transmit transmit.cpp)
target_compile_features(transmit PRIVATE cxx_std_17)
target_link_libraries(transmit
  PRIVATE
    SocketCan
    pthread
)

add_executable(receive receive.cpp)
target_compile_features(receive PRIVATE cxx_std_17)
target_link_libraries(receive
  PRIVATE
    SocketCan
    pthread
)

enable_testing()

add_executable(test_socketcan test_socketcan.cpp)
target_link_libraries(test_socketcan PRIVATE
  SocketCan
  gtest_main
)
target_compile_definitions(test_socketcan PRIVATE TESTS_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(test_socketcan PRIVATE cxx_std_17)
add_test(NAME test_socketcan COMMAND test_socketcan)
