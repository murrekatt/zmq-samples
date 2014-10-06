#ifndef PROTO_STREAMDISPATCHER_HPP
#define PROTO_STREAMDISPATCHER_HPP

#include "Module.hpp"
#include <czmq.h>
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
        socket_ = zsocket_new(ctx_, ZMQ_PAIR);
        assert(socket_);
        int rc = zsocket_connect(socket_, "tcp://127.0.0.1:5561");
        assert(rc == 0);

        backendSocket_ = zsocket_new(ctx_, ZMQ_DEALER);
        assert(backendSocket_);
        //zsock_set_identity((zsock_t*)backendSocket_, id_.c_str());
        rc = zsocket_bind(backendSocket_, "tcp://127.0.0.1:5562");
        assert(rc == 0);
    }

    virtual ~StreamDispatcher()
    {
    }

    virtual void run()
    {
        char* msg = zstr_recv(socket_);
        std::cout << id_ << ": Dispatching data." << std::endl;
        zstr_send(backendSocket_, msg);
        free(msg);
    }

    void* socket_;
    void* backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMDISPATCHER_HPP
