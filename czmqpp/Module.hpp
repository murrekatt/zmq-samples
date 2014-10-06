#ifndef PROTO_MODULE_HPP
#define PROTO_MODULE_HPP

#include <czmq++/context.hpp>
#include <thread>
#include <memory>
#include <atomic>
#include <iostream>
#include <cassert>

namespace proto
{

struct Module
{
    Module()
        : ctx_()
        , t_()
        , running_(false)
    {
    }

    virtual ~Module()
    {
    }

    void start()
    {
        if (running_) return;

        running_ = true;

        t_ = std::make_shared<std::thread>([this](){ while (this->running_) this->run(); });
    }

    void stop()
    {
        running_ = false;
    }

    void join()
    {
        t_->join();
    }

private:
    virtual void run() = 0;

protected:
    czmqpp::context ctx_;

private:
    std::shared_ptr<std::thread> t_;
    std::atomic<bool> running_;
};

} // namespace proto

#endif // PROTO_MODULE_HPP
