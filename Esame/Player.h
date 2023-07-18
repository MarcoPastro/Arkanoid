#pragma once
#include "Block.h"

#ifndef PLAYER_H // include guard
#define PLAYER_H
class Player :
    public Block
{
public:
    /*
        @brief
        create the Player
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    Player(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x = 0, double y = 0);
    /*
        @brief
        create the Player
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    Player(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x = 0, double y = 0);
    /*
        @brief
        function that call moveX and moveY with a timeStep
        @param timeStep to change the movement
    */
    void move(double timeStep);
    /*
        @brief
        Takes key presses and adjusts the texture's velocity 
        @param sdlEvent the input
    */
    void handleEvent(SDL_Event& sdlEvent);
    /*
        @brief
        Change the direction
        @param direction the direction
    */
    void ChangeDirection(Direction direction);
};
#endif
