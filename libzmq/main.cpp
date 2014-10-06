#include "Persistor.hpp"
#include "Streamer.hpp"
#include "StreamDispatcher.hpp"
#include "StreamBroker.hpp"
#include "ReceiptGenerator.hpp"
#include "Module.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>

using namespace proto;

int main()
{
    std::cout << "Running libzmq sample.\n";

    enum { Generators = 3 };
    enum { Streamers = 3 };

    typedef std::shared_ptr<Module> ModulePtr;
    typedef std::vector<ModulePtr> Modules;

    Modules modules;

    modules.push_back(std::make_shared<StreamBroker>());
    modules.push_back(std::make_shared<StreamDispatcher>());
    modules.push_back(std::make_shared<Persistor>());

    for (int i = 0; i < Streamers; ++i) {
        auto p = std::make_shared<Streamer>(i);
        modules.push_back(p);
    }

    for (int i = 0; i < Generators; ++i) {
        auto p = std::make_shared<ReceiptGenerator>(i);
        modules.push_back(p);
    }

    sleep(1);

    std::cout << "Starting simulation.\n";

    for (auto it : modules) {
        it->start();
    }

    sleep(3);

    std::cout << "Stopping simulation.\n";

    for (auto& it : modules) {
        it->stop();
    }

    std::cout << "Waiting for shutdown.\n";

    for (auto& it : modules) {
        it->join();
    }

    return 0;
}
