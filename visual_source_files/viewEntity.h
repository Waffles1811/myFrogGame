#ifndef LITTLEGAME_VIEWENTITY_H
#define LITTLEGAME_VIEWENTITY_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "concreteCamera.h"
using json = nlohmann::json;
namespace repr {
    class animationHandler;
    class viewEntity : public std::enable_shared_from_this<viewEntity> {
    protected:
        std::unique_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::shared_ptr<concreteCamera> camera;
        std::unique_ptr<repr::animationHandler> animationHandling;
        std::shared_ptr<repr::concreteOrientationObserver> orientationObserver;
        sf::IntRect spriteRect;
        std::string type;
        float scale;
        int leftXOffset; // sometime animations need us to add an offset since the left top corner might change
        int rightXOffset;
        int yOffset;
        bool curDirection;
    public:
        viewEntity(std::string& _type, std::string& folder, std::shared_ptr<concreteCamera> _camera, float _scale);
        virtual sf::Sprite getSprite(float xDimension, float yDimension, float time);
        void initialize(std::shared_ptr<concreteAnimationObserver> _obs,
                        std::shared_ptr<concreteOrientationObserver> orobs);
        void setTextureBox(int newX, int newY);
        void setTexture(std::string& _texture, float newLength, float newHeight);
        void setOffsets(int leftXOffset, int rightXOffset, int yOffset);
        void defaultTexture();
        };

    class animationHandler{
    private:
        json animation_data;
        std::shared_ptr<concreteAnimationObserver> animationObserver;
        std::weak_ptr<viewEntity> sprite;
        std::vector<float> frameDurations; // in milliseconds
        animation curAnimation;
        float timeSinceLastFrame;
        int curFrame;
        int curX; // where in the sprite sheet we are now
        int curY;
        int xOffset; // how many pixels we have to move for next sprite
        bool inAnimation;
        bool repeatingAnimation;

    public:
        animationHandler(std::string& _type, std::shared_ptr<concreteAnimationObserver>,
                const std::shared_ptr<viewEntity>&);
        void updateAnimation(float time);
        void startAnimation(animation type);
        void continueAnimation(float time);
        void stopAnimation();
    };
} // repr

#endif //LITTLEGAME_VIEWENTITY_H
