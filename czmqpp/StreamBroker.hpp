#ifndef PROTO_STREAMBROKER_HPP
#define PROTO_STREAMBROKER_HPP

#include "Module.hpp"
#include <czmq++/socket.hpp>
#include <czmq++/message.hpp>
#include <string>
#include <cassert>

namespace proto
{

struct StreamBroker : public Module
{
    StreamBroker()
        : publicSocket_(ctx_, ZMQ_ROUTER)
        , privateSocket_(ctx_, ZMQ_PAIR)
        , id_("StreamBroker")
    {
        int rc = publicSocket_.bind("tcp://127.0.0.1:5560");
        assert(rc == 0);

        rc = privateSocket_.bind("tcp://127.0.0.1:5561");
        assert(rc == 0);
    }

    virtual ~StreamBroker()
    {
    }

    virtual void run()
    {
        czmqpp::message message;
        message.receive(publicSocket_);

        std::cout << id_ << ": Forwarding data." << std::endl;
        message.send(privateSocket_);
    }

    czmqpp::socket publicSocket_;
    czmqpp::socket privateSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMBROKER_HPP
