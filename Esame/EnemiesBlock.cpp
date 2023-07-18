#include "EnemiesBlock.h"

EnemiesBlock::EnemiesBlock(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int life, double x, double y)
    :Block(textureGiver, nameTexture, collisionManager, 0, x, y), startLife(life), life(life){
}
EnemiesBlock::EnemiesBlock(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int life, double x, double y)
    :Block(textureGiver, nameTexture, collisionManager, functionToDo, 0, x, y), startLife(life), life(life) {
}

void EnemiesBlock::Hit() {
    ++numBeingHit;
    if (numBeingHit >= life) {
        setActive(false);
    }
    else {
        switch (life - numBeingHit) {
        case 1:
            ChangeTexture("Block1");
            break;
        case 2:
            ChangeTexture("Block2");
            break;
        case 3:
            ChangeTexture("Block3");
            break;
        }
    }
}

void EnemiesBlock::ResetLife()
{
    numBeingHit = 0;
    life = startLife;
    switch (life) {
    case 1:
        ChangeTexture("Block1");
        break;
    case 2:
        ChangeTexture("Block2");
        break;
    case 3:
        ChangeTexture("Block3");
        break;
    }
}