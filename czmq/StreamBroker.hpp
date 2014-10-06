#ifndef PROTO_STREAMBROKER_HPP
#define PROTO_STREAMBROKER_HPP

#include "Module.hpp"
#include <czmq.h>
#include <string>
#include <cassert>

namespace proto
{

struct StreamBroker : public Module
{
    StreamBroker()
        : publicSocket_(nullptr)
        , privateSocket_(nullptr)
        , id_("StreamBroker")
    {
        publicSocket_ = zsocket_new(ctx_, ZMQ_ROUTER);
        assert(publicSocket_);
        int rc = zsocket_bind(publicSocket_, "tcp://127.0.0.1:5560");
        assert(rc == 0);

        privateSocket_ = zsocket_new(ctx_, ZMQ_PAIR);
        assert(privateSocket_);
        rc = zsocket_bind(privateSocket_, "tcp://127.0.0.1:5561");
        assert(privateSocket_);
    }

    virtual ~StreamBroker()
    {
    }

    virtual void run()
    {
        char* msg = zstr_recv(publicSocket_);
        std::cout << id_ << ": Forwarding data." << std::endl;
        zstr_send(privateSocket_, msg);
        free(msg);
    }

    void* publicSocket_;
    void* privateSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMBROKER_HPP
