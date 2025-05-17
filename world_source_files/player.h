//
// Created by Littlefinger on 11/05/2025.
//

#ifndef LITTLEGAME_PLAYER_H
#define LITTLEGAME_PLAYER_H
#include "entity.h"

enum class movement{
    moveRight,
    faceDown,
    moveLeft,
    faceUp,
    jump,
    dash,
    wallCling,
    stopRight,
    stopDown,
    stopLeft,
    stopUp,
    stopCling
};

namespace world {
    class playerMovement;
    class inputHandler;
    class collisionHandler;
    class player : public entity, public std::enable_shared_from_this<player>  {
    private:
        std::shared_ptr<playerMovement> movement;
        std::shared_ptr<inputHandler> inputHandling;
        std::shared_ptr<collisionHandler> collisionFixer;
    public:
        player();
        void initialize();
        void timeUp(float time) override;
        void die(); // should make player respawn
        void processInput(enum movement input);
        void handleCollision(int id, const std::shared_ptr<entity>& hitobject);
        };

    class inputHandler{
        std::weak_ptr<playerMovement> movement;
    public:
        inputHandler(std::weak_ptr<playerMovement>);
        void processInput(enum movement input);
    };

    class playerMovement{
    public:
        float xSpeed;
        float ySpeed;
    private:
        std::weak_ptr<player> player_entity;
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
        playerMovement(std::weak_ptr<player>);
        void timeUp(float time);

        void goLeft();
        void goRight();
        void stopLeft();
        void stopRight();
        void boinkHead();
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

    class collisionHandler{
        std::weak_ptr<playerMovement> movement;
        std::weak_ptr<player> player_entity;
    public:
        collisionHandler(std::weak_ptr<playerMovement>, std::weak_ptr<player>);
        void handleCollision(int id, const std::shared_ptr<entity>& hitobject);
    };
}

#endif //LITTLEGAME_PLAYER_H
