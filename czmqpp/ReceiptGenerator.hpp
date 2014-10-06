#ifndef PROTO_RECEIPTGENERATOR_HPP
#define PROTO_RECEIPTGENERATOR_HPP

#include "Module.hpp"
#include <czmq++/socket.hpp>
#include <czmq++/message.hpp>
#include <string>
#include <cassert>
#include <unistd.h>

namespace proto
{

struct ReceiptGenerator : public Module
{
    explicit ReceiptGenerator(int i)
        : Module()
        , socket_(ctx_, ZMQ_DEALER)
        , id_("ReceiptGenerator" + std::to_string(i))
        , interval_(i+1)
    {
        socket_.set_identity(id_);

        int rc = socket_.connect("tcp://127.0.0.1:5560");
        assert(rc == 0);
    }

    virtual ~ReceiptGenerator()
    {
    }

    virtual void run()
    {
        czmqpp::data_chunk data { 0,1,2,3,4,5,6,7,8,9,0 };
        czmqpp::message message;
        message.append(data);

        message.send(socket_);

        std::cout << id_ << ": Sending data." << std::endl;

        sleep(interval_);
    }

    czmqpp::socket socket_;
    std::string id_;
    int interval_;
};

} // namespace proto

#endif // PROTO_RECEIPTGENERATOR_HPP
