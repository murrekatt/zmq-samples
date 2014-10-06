#ifndef PROTO_STREAMER_HPP
#define PROTO_STREAMER_HPP

#include "Module.hpp"
#include <zmq.h>
#include <string>
#include <cassert>

namespace proto
{

struct Streamer : public Module
{
    explicit Streamer(int i)
        : socket_(nullptr)
        , backendSocket_(nullptr)
        , id_("Streamer" + std::to_string(i))
    {
        socket_ = zmq_socket(ctx_, ZMQ_DEALER);
        assert(socket_);
        setLinger(socket_);
        setIdentity(socket_, id_);
        int rc = zmq_connect(socket_, "tcp://127.0.0.1:5562");
        assert(rc);

        backendSocket_ = zmq_socket(ctx_, ZMQ_DEALER);
        assert(backendSocket_);
        setLinger(backendSocket_);
        setIdentity(backendSocket_, id_);
        rc = zmq_connect(backendSocket_, "tcp://127.0.0.1:5563");
        assert(rc);
    }

    virtual ~Streamer()
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
            std::cout << id_ << ": Streaming data for member TODO." << std::endl;
            zmq_send(backendSocket_, &msg, 32, 0);
        }
    }

    void* socket_;
    void* backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMER_HPP
