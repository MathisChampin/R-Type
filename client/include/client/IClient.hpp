#pragma once

#include <iostream>

namespace NmpClient 
{
    class IClient {
        public:
            virtual void send_input() = 0;
            virtual void get_data() = 0;
            virtual ~IClient() = default;
    };
}