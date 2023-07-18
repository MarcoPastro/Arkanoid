#pragma once
#include "Block.h"

#ifndef ENEMIESBLOCK_H // include guard
#define ENEMIESBLOCK_H
class EnemiesBlock :
    public Block
{
public:
    /*
        @brief
        create the enemy block
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    EnemiesBlock(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int lifeOfTheBlock = 1, double x = 0, double y = 0);
    /*
        @brief
        create the Block
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param functionToDo the function that retorn the new position (x or y) in case of a edge collision
        @param lifeOfTheBlock the initial life of the block
        @param x the x starting position
        @param y the y starting position
    */
    EnemiesBlock(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int lifeOfTheBlock = 1, double x = 0, double y = 0);
    /*
        @brief
        function that activate the logic of the block when been hit (in this case only increment the value)
    */
    void Hit();
    /*
        @brief
        reset the life with the start value
    */
    void ResetLife();
private:
    int life;
    int startLife;
};
#endif
