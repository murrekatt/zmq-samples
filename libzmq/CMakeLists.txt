set(name sample-libzmq)

set(cxx-sources
  main.cpp
)

add_executable(${name} ${cxx-sources})
target_link_libraries(${name} zmq)
