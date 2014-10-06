#ifndef PROTO_STREAMDISPATCHER_HPP
#define PROTO_STREAMDISPATCHER_HPP

#include "Module.hpp"
#include <czmq++/socket.hpp>
#include <czmq++/message.hpp>
#include <string>
#include <cassert>

namespace proto
{

struct StreamDispatcher : public Module
{
    StreamDispatcher()
        : socket_(ctx_, ZMQ_PAIR)
        , backendSocket_(ctx_, ZMQ_DEALER)
        , id_("StreamDispatcher")
    {
        int rc = socket_.connect("tcp://127.0.0.1:5561");
        assert(rc == 0);

        backendSocket_.set_identity(id_);
        rc = backendSocket_.bind("tcp://127.0.0.1:5562");
        assert(rc == 0);
    }

    virtual ~StreamDispatcher()
    {
    }

    virtual void run()
    {
        czmqpp::message message;
        message.receive(socket_);

        std::cout << id_ << ": Dispatching data." << std::endl;
        message.send(backendSocket_);
    }

    czmqpp::socket socket_;
    czmqpp::socket backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMDISPATCHER_HPP
