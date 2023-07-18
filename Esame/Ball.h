#pragma once
#include "GameObject.h"

#ifndef BALL_H // include guard
#define BALL_H
class Ball :
    public GameObject
{
public:
    /*
        @brief
        create the ball
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    Ball(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x = 0, double y = 0);
    /*
        @brief
        create the ball
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param functionToDo the function that retorn the new position (x or y) in case of a edge collision
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    Ball(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x = 0, double y = 0);

    /*
        @brief
        function that change the velocity in x or in y based on the input
        @param bounceX if the velocity in x has to change
        @param bounceY if the velocity in y has to change
    */
    void Bounce(bool bounceX, bool bounceY);

    /*
        @brief
        function that call moveX and moveY with a timeStep
        @param timeStep to change the movement
    */
    void move(double timeStep);
    /*
        @brief
        the movement based on the timeStep in the x axis
        @param timeStep to change the movement
    */
    void moveX(double timeStep);
    /*
        @brief
        the movement based on the timeStep in the y axis
        @param timeStep to change the movement
    */
    void moveY(double timeStep);
};
#endif
