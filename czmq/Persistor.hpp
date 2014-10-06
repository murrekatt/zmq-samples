#ifndef PROTO_PERSISTOR_HPP
#define PROTO_PERSISTOR_HPP

#include "Module.hpp"
#include <czmq.h>
#include <string>
#include <cassert>

namespace proto
{

struct Persistor : public Module
{
    Persistor()
        : Module()
        , socket_(nullptr)
        , id_("Persistor")
    {
        socket_ = zsocket_new(ctx_, ZMQ_DEALER);
        assert(socket_);
        //zsock_set_identity((zsock_t*)socket_, id_.c_str());

        int rc = zsocket_bind(socket_, "tcp://127.0.0.1:5563");
        assert(rc);
    }

    virtual ~Persistor()
    {
    }

    virtual void run()
    {
        char* msg = zstr_recv(socket_);
        std::cout << id_ << ": Persisting data from member TODO." << std::endl;
    }

    void* socket_;
    std::string id_;
};

} // namespace proto

#endif // PROTO_PERSISTOR_HPP
