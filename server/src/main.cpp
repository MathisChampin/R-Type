#include "Server.hpp"

#include <thread>

int main()
{
    try
    {
        NmpServer::Server server;

        std::thread server_thread([&server]() {
            server.run();
        });

        while (true) {
            {
                std::cout << "can send ecs entity" << std::endl;
                auto client = server.getClient();
                if (client.size() >= 1) {
                    std::cout << "has client" << std::endl;
                    NmpServer::Packet res(42, NmpServer::EVENT::JOIN);
                    server.broadcast(res);
                    std::cout << "end" << std::endl;
                }else 
                    std::cout << "no client" << std::endl;

            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        server_thread.join();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}


