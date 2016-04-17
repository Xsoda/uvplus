cmake_minimum_required(VERSION 2.8)
project(uvplus)

set(UVPLUS_SRC
   src/handle.cpp
   src/stream.cpp
   src/async.cpp
   src/check.cpp
   src/idle.cpp
   src/loop.cpp
   src/poll.cpp
   src/prepare.cpp
   src/tcp.cpp
   src/timer.cpp
   src/udp.cpp
   src/pipe.cpp
   src/process.cpp
   src/signal.cpp
   src/tty.cpp
   src/fs_event.cpp
   src/fs_poll.cpp)

include_directories(../libuv/include)
include_directories(include)
add_library(uvplus STATIC ${UVPLUS_SRC})

set_property(TARGET uvplus PROPERTY CXX_STANDARD 11)
set_property(TARGET uvplus PROPERTY CXX_STANDARD_REQUIRED ON)
