#ifndef LITTLEGAME_VIEWENTITY_H
#define LITTLEGAME_VIEWENTITY_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "concreteCamera.h"
namespace repr {
    class viewEntity {
        std::unique_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Sprite> sprite;
        std::shared_ptr<concreteCamera> camera;
        std::string type;
    public:
        viewEntity(std::string& _type, std::shared_ptr<concreteCamera> _camera, float scale);
        sf::Sprite getSprite(float xDimension, float Ydimension);
    };

} // repr

#endif //LITTLEGAME_VIEWENTITY_H
