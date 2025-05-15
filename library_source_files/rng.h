#ifndef LITTLEGAME_RNG_H
#define LITTLEGAME_RNG_H
#include <cstdlib>

namespace world {
    class rng {
    public:
        /*
         *
         * return: a random number between min and max-1
         *
         */
        int generateRandomint(int min, int max);

        rng() = default;
    };
} // namespace dj


#endif //LITTLEGAME_RNG_H
