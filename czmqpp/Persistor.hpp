#ifndef PROTO_PERSISTOR_HPP
#define PROTO_PERSISTOR_HPP

#include "Module.hpp"
#include <czmq++/socket.hpp>
#include <czmq++/message.hpp>
#include <string>
#include <cassert>

namespace proto
{

struct Persistor : public Module
{
    Persistor()
        : Module()
        , socket_(ctx_, ZMQ_DEALER)
        , id_("Persistor")
    {
        socket_.set_identity(id_);

        int rc = socket_.bind("tcp://127.0.0.1:5563");
        assert(rc);
    }

    virtual ~Persistor()
    {
    }

    virtual void run()
    {
        czmqpp::message message;
        message.receive(socket_);

        std::cout << id_ << ": Persisting data from member TODO." << std::endl;
    }

    czmqpp::socket socket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_PERSISTOR_HPP
