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
    stopJump,
    dash,
    wallCling,
    stopRight,
    stopDown,
    stopLeft,
    stopUp,
    stopCling
};

namespace world {
    // some declarations
    class playerMovement;
    class inputHandler;
    class collisionHandler;
    class animationHandler;
    class player : public entity, public std::enable_shared_from_this<player>  {
    private:
        std::shared_ptr<playerMovement> movement;
        std::shared_ptr<inputHandler> inputHandling;
        std::shared_ptr<collisionHandler> collisionFixer;
        std::shared_ptr<animationHandler> animationHandling;
    public:
        player();
        player(float x, float y);
        void initialize();
        void timeUp(float time) override;
        void processInput(enum movement input);
        void handleCollision(int id, const std::shared_ptr<entity>& hitObject);
        void reset();
        void setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                 std::shared_ptr<world::orientationObserver> _orientobserver);
        const std::shared_ptr<animationHandler> &getAnimationHandling() const;
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
        bool goingLeft;
        bool goingRight;
        bool facingUp;
        bool facingDown;

        bool grounded;
        bool jumping;
        float jumpingTime;

        bool canDash;
        bool inDash;
        float dashTime;
        double dashDirection; // right (->) is 0 then goes clockwise +1,

        bool touchingWall;
        bool wallClinging;
        float wallClingTime;

        float coyoteTime;
        float jumpBufferTime;

    public:
        playerMovement(std::weak_ptr<player>);
        void timeUp(float time);
        void reset();

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
        void stopJump();
        void land(float height);
        void fall();

        void dash();
        void endDash();
    };

    class collisionHandler{
        float xRespawnPoint;
        float yRespawnPoint;
        std::weak_ptr<playerMovement> movement;
        std::weak_ptr<player> player_entity;
    public:
        collisionHandler(std::weak_ptr<playerMovement>, std::weak_ptr<player>,float, float);
        void handleCollision(int id, const std::shared_ptr<entity>& hitObject);
        void respawn();
    };

    class animationHandler{ // maybe change the hitbox in certain scenarios idk
        std::shared_ptr<world::animationObserver> observer;
        std::shared_ptr<world::orientationObserver> orientationObserver;
    public:
        animationHandler();
        ~animationHandler() = default;
        void processAnimation(animation animationID);
        void setAnimationCameras(std::shared_ptr<world::animationObserver> _animobserver,
                                std::shared_ptr<world::orientationObserver> _orientobserver);
        void turn(bool direction);
    };
}

#endif //LITTLEGAME_PLAYER_H
