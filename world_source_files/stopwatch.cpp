#include "stopwatch.h"
using namespace std::chrono;
float world::stopwatch::timeTic() {
    auto curTime = std::chrono::steady_clock::now();
    duration<float> elapsedTime = duration_cast<duration<float>>(curTime - start_tic);
    start_tic = curTime;
    // std::cout << elapsedTime.count() << std::endl;
    // return 0.01; // for debugging
    return elapsedTime.count(); // for real stuff
}
