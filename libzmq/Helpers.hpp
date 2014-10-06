#ifndef PROTO_HELPERS_HPP
#define PROTO_HELPERS_HPP

#include <zmq.h>
#include <iostream>
#include <string>
#include <cassert>

namespace proto
{

inline void setLinger(void* socket)
{
    int linger = 1000;
    int rc = zmq_setsockopt(socket, ZMQ_LINGER, &linger, sizeof(linger));
    assert(rc == 0 || errno == ETERM);
}

inline void setIdentity(void* socket, const std::string& id)
{
    int rc = zmq_setsockopt(socket, ZMQ_IDENTITY, id.c_str(), id.size());
    assert(rc == 0);
}

} // namespace proto

#endif // PROTO_HELPERS_HPP
