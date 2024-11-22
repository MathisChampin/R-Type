#include "Server.hpp"

int main()
{
    NmpServer::Server s;

    s.run();
    s.get_data();
    return 0;
}