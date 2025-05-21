#ifndef LITTLEGAME_VIEWENTITY_H
#define LITTLEGAME_VIEWENTITY_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "concreteCamera.h"
#include "../json.hpp"
using json = nlohmann::json;
namespace repr {
    class animationHandler;
    class viewEntity : public std::enable_shared_from_this<viewEntity> {
        std::unique_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::shared_ptr<concreteCamera> camera;
        std::unique_ptr<repr::animationHandler> animationHandling;
        sf::IntRect spriteRect;
        std::string type;
        float scale;
        int xOffset; // sometime animations need us to add an offset since the left top corner might change
        int yOffset;
    public:
        viewEntity(std::string& _type, std::shared_ptr<concreteCamera> _camera, float _scale);
        sf::Sprite getSprite(float xDimension, float yDimension, float time);
        void initialize(std::shared_ptr<concreteAnimationObserver> _obs);
        void setTextureBox(int newX, int newY);
        void setTexture(std::string& _texture, float newLength, float newHeight);
        void defaultTexture();
        };

    class animationHandler{
    private:
        json animation_data;
        std::shared_ptr<concreteAnimationObserver> animationObserver;
        std::weak_ptr<viewEntity> sprite;
        std::vector<float> frameDurations; // in milliseconds
        std::vector<int> xOffsets;
        std::vector<int> yOffsets;
        float timeSinceLastFrame;
        int curFrame;
        int curX; // where in the sprite sheet we are now
        int curY;
        int xOffset; // how many pixels we have to move for next sprite
        bool inAnimation;

    public:
        animationHandler(std::string& _type, std::shared_ptr<concreteAnimationObserver>, const std::shared_ptr<viewEntity>&);
        void updateAnimation(float time);
        void startAnimation(animation type);
        void continueAnimation(float time);
        void stopAnimation();
    };
} // repr

#endif //LITTLEGAME_VIEWENTITY_H
