#pragma once
#include "MGDGlobals.h"
#include "MGDTexture.h"
#include "Direction.h"
#include "TextureManagement.h"
#include "CollisionManager.h"
#include <string>

#ifndef GAMEOBJECT_H // include guard
#define GAMEOBJECT_H

class GameObject {
public:
    /*
        @brief
        create a gameobject
        @param textureGiver where the texture is
        @param nameTexture the name of the texture
        @param collisionManager where the collision can be checked
        @param velocity the initial velocity of the ball
        @param x the x starting position
        @param y the y starting position
    */
    GameObject(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x = 0, double y = 0);

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
    GameObject(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x = 0, double y = 0);

    // Moves the texture
    /*
        @brief
        Moves the texture based on a timeStep
        @param timeStep the time step
    */
    virtual void move(double timeStep);

    // Moves the texture on X axis
    /*
        @brief
        Moves the texture on a x axis based on a timeStep
        @param timeStep the time step
    */
    virtual void moveX(double timeStep);

    // Moves the texture on Y axis
    /*
        @brief
        Moves the texture on a y axis based on a timeStep
        @param timeStep the time step
    */
    virtual void moveY(double timeStep);

    /*
        @brief
        Shows the texture on the screen
    */
    void render();

    // Sets the position of this texture (0,0 is the top left)
    /*
        @brief
        Sets the position on the x axis of this texture (0,0 is the top left)
        @param timeStep the time step
    */
    void setPosX(double posX);
    /*
        @brief
        Sets the position on the y axis of this texture (0,0 is the top left)
        @param timeStep the time step
    */
    void setPosY(double posY);

    // Gets the position of this texture (0,0 is the top left)
    /*
        @brief
        Gets the position on the x axis of this texture (0,0 is the top left)
        @return the x position
    */
    const double getPosX();
    /*
        @brief
        Gets the position on the y axis of this texture (0,0 is the top left)
        @return the x position
    */
    const double getPosY();

    // Sets the general velocity of the texture
    /*
        @brief
        Sets the general velocity of the texture
        @param velocity the new value
    */
    void setVelocity(int velocity);

    /*
        @brief
        Gets the general velocity of the texture
        @return the velocity
    */
    int getVelocity();

    // Sets the current velocity of the x or y of this texture
    /*
        @brief
        Sets the current velocity of the x of this texture
        @param the x position
    */
    void setVelX(double velX);
    /*
        @brief
        Sets the current velocity of the y of this texture
        @param the x position
    */
    void setVelY(double velY);

    // Gets the current velocity of this texture
    /*
        @brief
        Gets the current velocity of the x of this texture
        @return the velocity
    */
    const double getVelX();
    /*
        @brief
        Gets the current velocity of the y of this texture
        @return the velocity
    */
    const double getVelY();

    /*
        @brief
        Gets the width of the texture
        @return the width of the texture
    */
    const int getTextureWidth();
    /*
        @brief
        Gets the height of the texture
        @return the height of the texture
    */
    const int getTextureHeight();

    // Change the texture
    /*
        @brief
        Change the texture
        @param nameTexture the name of the texture
    */
    void ChangeTexture(std::string nameTexture);

    /*
        @brief
        Set the object to active (if not active the render and the collision doesn't work)
        @param value the value
    */
    void setActive(bool value);
    /*
        @brief
        Gets true or false if the object is active
        @return the value of active
    */
    bool getActive();
    /*
        @brief
        Gets the texture manager
        @return the texture manager
    */
    TextureManagement* GetTextureManagement();
    /*
        @brief
        Gets the texture
        @return the texture
    */
    MGDTexture* GetTexture();
protected:
    double _posX, _posY;
    double _velX, _velY;

    // The dimensions of the texture
    int _textureWidth = 20;
    int _textureHeight = 20;

    // Maximum axis velocity of the texture
    int _velocity = 200;

    int (*functionToDoOnEdge)(int);

    class CollisionManager* collisionManager;

private:
    std::string nameTexture;

    bool active;

    class TextureManagement* textureGiver;

    // Scene textures
    class MGDTexture* _texture;

    
};
#endif