#ifndef PROTO_RECEIPTGENERATOR_HPP
#define PROTO_RECEIPTGENERATOR_HPP

#include "Module.hpp"
#include <zmq.h>
#include <string>
#include <cassert>
#include <unistd.h>

namespace proto
{

struct ReceiptGenerator : public Module
{
    explicit ReceiptGenerator(int i)
        : Module()
        , socket_(nullptr)
        , id_("ReceiptGenerator" + std::to_string(i))
        , interval_(i+1)
    {
        socket_ = zmq_socket(ctx_, ZMQ_DEALER);
        assert(socket_);
        setLinger(socket_);
        setIdentity(socket_, id_);

        int rc = zmq_connect(socket_, "tcp://127.0.0.1:5560");
        assert(rc == 0);
    }

    virtual ~ReceiptGenerator()
    {
        int rc = zmq_close(socket_);
        assert(rc == 0);
    }

    virtual void run()
    {
        const char* content = "12345678ABCDEFGH12345678abcdefgh";

        std::cout << id_ << ": Sending data." << std::endl;
        int rc = zmq_send(socket_, "", 0, ZMQ_SNDMORE);
        assert(rc == id_.size());
        rc = zmq_send(socket_, content, 32, 0);

        sleep(interval_);
    }

    void* socket_;
    std::string id_;
    int interval_;
};

} // namespace proto

#endif // PROTO_RECEIPTGENERATOR_HPP
