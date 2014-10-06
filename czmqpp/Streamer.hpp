#ifndef PROTO_STREAMER_HPP
#define PROTO_STREAMER_HPP

#include "Module.hpp"
#include <czmq++/socket.hpp>
#include <czmq++/message.hpp>
#include <string>
#include <cassert>

namespace proto
{

struct Streamer : public Module
{
    explicit Streamer(int i)
        : socket_(ctx_, ZMQ_DEALER)
        , backendSocket_(ctx_, ZMQ_DEALER)
        , id_("Streamer" + std::to_string(i))
    {
        socket_.set_identity(id_);
        int rc = socket_.connect("tcp://127.0.0.1:5562");
        assert(rc == 0);

        backendSocket_.set_identity(id_);
        rc = backendSocket_.connect("tcp://127.0.0.1:5563");
        assert(rc == 0);
    }

    virtual ~Streamer()
    {
    }

    virtual void run()
    {
        czmqpp::message message;
        message.receive(socket_);

        std::cout << id_ << ": Streaming data for member TODO." << std::endl;
        message.send(backendSocket_);
    }

    czmqpp::socket socket_;
    czmqpp::socket backendSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_STREAMER_HPP
