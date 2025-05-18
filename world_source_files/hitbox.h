#ifndef LITTLEGAME_HITBOX_H
#define LITTLEGAME_HITBOX_H
namespace world {
    class hitbox {// I might add hitboxes off different shapes later
    protected:
        float x;
        float y;
        float xOffset;
        float yOffset;
    public:
        hitbox(float _xOffset, float _yOffset);
        virtual void setX(float _x); // might be overridden if I add circular shapes or smth
        virtual void setY(float _y);
    };

    class rectHitbox : public hitbox {
    public:
        float length; // how far it stretches to the right from entity.x
        float height; // how far it stretches down from entity.y
        bool killsYou; // owie that hurts :(


        rectHitbox(float, float, float, float, bool);
        int detectCollision(rectHitbox& otherBox, float xDif, float yDif);
        /*codes:
         * 0 = no collision
         * 1 = collision at bottom
         * 2 = placeholder for collision top
         * 3 = collision left
         * 4 = collision right
         * 5 = kill player*/
        float getLeftX();
        float getRightX();
        float getUpY();
        float getDownY();
    };
}

#endif //LITTLEGAME_HITBOX_H
