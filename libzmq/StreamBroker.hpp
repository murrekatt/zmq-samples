#ifndef PROTO_AUDITSTREAMBROKER_HPP
#define PROTO_AUDITSTREAMBROKER_HPP

#include "Module.hpp"
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
        publicSocket_ = zmq_socket(ctx_, ZMQ_ROUTER);
        assert(publicSocket_);
        setLinger(publicSocket_);
        int rc = zmq_bind(publicSocket_, "tcp://127.0.0.1:5560");
        assert(rc == 0);

        privateSocket_ = zmq_socket(ctx_, ZMQ_PAIR);
        assert(privateSocket_);
        setLinger(privateSocket_);
        rc = zmq_bind(privateSocket_, "tcp://127.0.0.1:5561");
        assert(privateSocket_);
    }

    virtual ~StreamBroker()
    {
        int rc = zmq_close(publicSocket_);
        assert(rc == 0);
        rc = zmq_close(privateSocket_);
        assert(rc == 0);
    }

    virtual void run()
    {
        char buffer[32];
        int rc = zmq_recv(publicSocket_, buffer, 32, ZMQ_DONTWAIT);
        assert(rc != -1);
        if (rc > 0) {
            rc = zmq_recv(publicSocket_, buffer, 32, ZMQ_DONTWAIT);
            assert(rc != -1);
            rc = zmq_recv(publicSocket_, buffer, 32, ZMQ_DONTWAIT);
            assert(rc == 32);
            if (rc > 0) {
                std::cout << id_ << ": Forwarding data." << std::endl;
                zmq_send(privateSocket_, buffer, 32, 0);
            }
        }
    }

    void* publicSocket_;
    void* privateSocket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_AUDITSTREAMBROKER_HPP
