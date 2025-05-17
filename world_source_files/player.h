//
// Created by Littlefinger on 11/05/2025.
//

#ifndef LITTLEGAME_PLAYER_H
#define LITTLEGAME_PLAYER_H
#include "entity.h"
namespace world {
    class player : public entity {
    private:
        float xSpeed;
        float ySpeed;

        bool grounded;

        bool goingLeft;
        bool goingRight;
        bool facingUp;
        bool facingDown;

        bool canDash;
        bool inDash;
        float dashTime;
        double dashDirection; // right (->) is 0 then goes clockwise +1,

        bool touchingWall;
        bool wallClinging;
        float wallClingTime;

    public:
        player();
        void timeUp(float time) override;
        void die(); // should make player respawn

        // vv movement related functions
        void goLeft();
        void goRight();
        void stopLeft();
        void stopRight();
        void hitWall(float length, bool left);
        void noWall();
        void clingToWall();
        void releaseWall();

        void faceUp();
        void faceDown();
        void stopUp();
        void stopDown();

        void jump();
        void land(float height);
        void fall();

        void dash();
        void endDash();
        };
}

#endif //LITTLEGAME_PLAYER_H
