#ifndef PROTO_AUDITSTREAMDISPATCHER_HPP
#define PROTO_AUDITSTREAMDISPATCHER_HPP

#include "Module.hpp"
#include <zmq.h>
#include <string>
#include <cassert>

namespace proto
{

struct StreamDispatcher : public Module
{
    StreamDispatcher()
        : socket_(nullptr)
        , backendSocket_(nullptr)
        , id_("StreamDispatcher")
    {
        socket_ = zmq_socket(ctx_, ZMQ_PAIR);
        assert(socket_);
        setLinger(socket_);
        int rc = zmq_connect(socket_, "tcp://127.0.0.1:5561");
        assert(rc == 0);

        backendSocket_ = zmq_socket(ctx_, ZMQ_DEALER);
        assert(backendSocket_);
        setLinger(backendSocket_);
        setIdentity(backendSocket_, id_);
        rc = zmq_bind(backendSocket_, "tcp://127.0.0.1:5562");
        assert(rc == 0);
    }

    virtual ~StreamDispatcher()
    {
        int rc = zmq_close(socket_);
        assert(rc);
        rc = zmq_close(backendSocket_);
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
            std::cout << id_ << ": Dispatching data." << std::endl;
            zmq_send(backendSocket_, &msg, 32, 0);
        }
    }

    void* socket_;
    void* backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_AUDITSTREAMDISPATCHER_HPP
