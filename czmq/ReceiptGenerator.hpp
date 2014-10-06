#ifndef PROTO_RECEIPTGENERATOR_HPP
#define PROTO_RECEIPTGENERATOR_HPP

#include "Module.hpp"
#include <czmq.h>
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
        socket_ = zsocket_new(ctx_, ZMQ_DEALER);
        assert(socket_);
        //zsock_set_identity((zsock_t*)socket_, id_.c_str());

        int rc = zsocket_connect(socket_, "tcp://127.0.0.1:5560");
        assert(rc == 0);
    }

    virtual ~ReceiptGenerator()
    {
    }

    virtual void run()
    {
        const char* content = "12345678ABCDEFGH12345678abcdefgh";

        std::cout << id_ << ": Sending data." << std::endl;
        zstr_send(socket_, content);

        sleep(interval_);
    }

    void* socket_;
    std::string id_;
    int interval_;
};

} // namespace proto

#endif // PROTO_RECEIPTGENERATOR_HPP
