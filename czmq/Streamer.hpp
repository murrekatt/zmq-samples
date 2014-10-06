#ifndef PROTO_STREAMER_HPP
#define PROTO_STREAMER_HPP

#include "Module.hpp"
#include <czmq.h>
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
        socket_ = zsocket_new(ctx_, ZMQ_DEALER);
        assert(socket_);
        //zsock_set_identity((zsock_t*)socket_, id_.c_str());
        int rc = zsocket_connect(socket_, "tcp://127.0.0.1:5562");
        assert(rc);

        backendSocket_ = zsocket_new(ctx_, ZMQ_DEALER);
        assert(backendSocket_);
        //zsock_set_identity((zsock_t*)backendSocket_, id_.c_str());
        rc = zsocket_connect(backendSocket_, "tcp://127.0.0.1:5563");
        assert(rc);
    }

    virtual ~Streamer()
    {
    }

    virtual void run()
    {
        char* msg = zstr_recv(socket_);
        std::cout << id_ << ": Streaming data for member TODO." << std::endl;
        zstr_send(backendSocket_, msg);
        free(msg);
    }

    void* socket_;
    void* backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMER_HPP
