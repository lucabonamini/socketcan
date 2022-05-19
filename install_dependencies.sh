#!/bin/bash

sudo apt -y update
sudo apt install -y \
    ccache \
    clang-tidy \
    cppcheck \
    iwyu \
    graphviz \
    doxygen
