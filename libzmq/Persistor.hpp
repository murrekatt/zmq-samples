#ifndef PROTO_PERSISTOR_HPP
#define PROTO_PERSISTOR_HPP

#include "Module.hpp"
#include <zmq.h>
#include <string>
#include <cassert>

namespace proto
{

struct Persistor : public Module
{
    Persistor()
        : Module()
        , socket_(nullptr)
        , id_("Persistor")
    {
        socket_ = zmq_socket(ctx_, ZMQ_DEALER);
        assert(socket_);
        setLinger(socket_);
        setIdentity(socket_, id_);

        int rc = zmq_bind(socket_, "tcp://127.0.0.1:5563");
        assert(rc);
    }

    virtual ~Persistor()
    {
        int rc = zmq_close(socket_);
        assert(rc);
    }

    virtual void run()
    {
        zmq_msg_t msg;
        int rc = zmq_msg_init(&msg);
        assert(rc == 0);
        rc = zmq_msg_recv(&msg, socket_, ZMQ_DONTWAIT);
        assert(rc != -1);
        if (rc > 0) {
            std::cout << id_ << ": Persisting data from member TODO." << std::endl;
        }
    }

    void* socket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_PERSISTOR_HPP
