#include "Block.h"

Block::Block(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x, double y)
    :GameObject(textureGiver, nameTexture, collisionManager, velocity, x, y), numBeingHit(0){
}
Block::Block(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x, double y)
    :GameObject(textureGiver, nameTexture, collisionManager,functionToDo, velocity, x, y), numBeingHit(0){
}

int Block::getNumBeingHit() {
    return numBeingHit;
}
void Block::Hit() {
    ++numBeingHit;
}

