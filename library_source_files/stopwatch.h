#ifndef LITTLEGAME_STOPWATCH_H
#define LITTLEGAME_STOPWATCH_H
#include <chrono>
namespace world {
    class stopwatch {
    protected:
        std::chrono::steady_clock::time_point start_tic;

    public:
        /*
         *
         * measures time since last time this function was called
         *
         * return: time since last tic
         *
         */
        float timeTic();
        stopwatch() = default;
    };
} // namespace dj
#endif // LITTLEGAME_STOPWATCH_H
