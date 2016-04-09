cmake_minimum_required(VERSION 2.8)
project(uvplus)

set(UVPLUS_SRC
   src/async.cpp
   src/check.cpp
   src/handle.cpp
   src/idle.cpp
   src/loop.cpp
   src/poll.cpp
   src/prepare.cpp
   src/stream.cpp
   src/tcp.cpp
   src/timer.cpp
   src/udp.cpp)

include_directories(include)
add_library(uvplus STATIC ${UVPLUS_SRC})

set_property(TARGET uvplus PROPERTY CXX_STANDARD 11)
set_property(TARGET uvplus PROPERTY CXX_STANDARD_REQUIRED ON)
