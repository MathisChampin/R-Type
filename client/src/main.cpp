#include "Client.hpp"

int main()
{
    NmpClient::Client c;
    c.send_input();
    c.get_data(); 
    return 0;
}