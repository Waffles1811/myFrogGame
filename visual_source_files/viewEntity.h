#ifndef LITTLEGAME_VIEWENTITY_H
#define LITTLEGAME_VIEWENTITY_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "../json.hpp"
using json = nlohmann::json;
#include "animationLibrary.h"
namespace repr {
    class animationHandler;
    class viewEntity : public std::enable_shared_from_this<viewEntity> {
    protected:
        std::unique_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::unique_ptr<repr::animationHandler> animationHandling;
        sf::IntRect spriteRect;
        std::string type;
        std::string folder;
        float scale;
        int leftXOffset; // sometime animations need us to add an offset since the left top corner might change
        int rightXOffset;
        int yOffset;
        bool curDirection; // true = left
        float x;
        float y;
    public:
        viewEntity(std::string& _type, std::string& folder, float _scale);
        void initialiseAnimations(std::shared_ptr<animationLibrary> _library);
        virtual sf::Sprite getSprite(float xDimension, float yDimension, float time);
        void setTextureBox(int newX, int newY);
        void setTexture(std::string& _texture, float newLength, float newHeight);
        void setOffsets(int leftXOffset, int rightXOffset, int yOffset);
        void updatePosition(float newX, float NewY);
        void changeOrientation();
        void startAnimation(std::string anim);
        void setNewDefaultAnim(std::string newDefaultAnim);
        void calcLocation();
        };

    class animationHandler{
    private:
        std::string type;
        std::shared_ptr<animationLibrary> library;
        json animation_data;
        std::weak_ptr<viewEntity> sprite;
        std::vector<float> frameDurations; // in milliseconds
        std::string curAnimation;
        float timeSinceLastFrame;
        int curFrame;
        int curX; // where in the sprite sheet we are now
        int curY;
        int xOffset; // how many pixels we have to move for next sprite
        bool repeatingAnimation;
        bool wallAnimations;
        std::string defaultAnim;
    public:
        animationHandler(std::string& _type, const std::shared_ptr<viewEntity>, std::shared_ptr<animationLibrary> _library);
        void updateAnimation(float time);
        void startAnimation(std::string type);
        void continueAnimation(float time);
        void stopAnimation();
        void setNewDefault(std::string newDefaultAnim);
        void defaultTexture();

    };
} // repr

#endif //LITTLEGAME_VIEWENTITY_H
