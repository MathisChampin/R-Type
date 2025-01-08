#pragma once

#include <chrono>

namespace NmpServer
{
    class ClockManager {
    public:
        ClockManager() : _isRunning(false), _elapsedTime(0) {}

        void start()
        {
            _startTime = std::chrono::steady_clock::now();
            _isRunning = true;
            _elapsedTime = 0;
        }

        void pause()
        {
            if (_isRunning) {
                auto now = std::chrono::steady_clock::now();
                _elapsedTime += std::chrono::duration_cast<std::chrono::seconds>(now - _startTime).count();
                _isRunning = false;
            }
        }

        void resume()
        {
            if (!_isRunning) {
                _startTime = std::chrono::steady_clock::now();
                _isRunning = true;
            }
        }

        void reset()
        {
            _isRunning = false;
            _elapsedTime = 0;
        }

        double elapsedSeconds() const
        {
            if (_isRunning) {
                auto now = std::chrono::steady_clock::now();
                return _elapsedTime + std::chrono::duration_cast<std::chrono::seconds>(now - _startTime).count();
            }
            return _elapsedTime;
        }

    private:
        std::chrono::steady_clock::time_point _startTime;
        bool _isRunning;
        double _elapsedTime;
    };
}