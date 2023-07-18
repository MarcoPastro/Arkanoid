#include "Ball.h"

Ball::Ball(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x, double y)
    :GameObject(textureGiver, nameTexture, collisionManager, velocity, x, y) {
}
Ball::Ball(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x, double y)
    :GameObject(textureGiver, nameTexture, collisionManager, functionToDo, velocity, x, y) {
}

void Ball::Bounce(bool bounceX, bool bounceY) {
    if (bounceX) {
        _velX = -_velX;
    }
    if (bounceY) {
        _velY = -_velY;
    }
}

void Ball::move(double timeStep) {
    double newX1 = _posX + _velX * timeStep;
    double newX2 = newX1 + _textureWidth;
    double newY1 = _posY + _velY * timeStep;
    double newY2 = newY1 + _textureHeight;
    double collRes = collisionManager->CheckCollision(newX1, newY1, newX2, newY2);
    if (collRes < 0) {
        Bounce(false, true);
    }
    else if (collRes > 0) {
        Bounce(true,false);
    }
    moveY(timeStep);
    moveX(timeStep);
}
void Ball::moveX(double timeStep) {
    // Move the texture left or right
    _posX += _velX * timeStep;

    // If the texture went too far to the left or right
    if (_posX < 0) {
        _posX = functionToDoOnEdge(0);
        Bounce(1, 0);
    }
    else if (_posX > SCREEN_WIDTH - _textureWidth) {
        _posX = functionToDoOnEdge(SCREEN_WIDTH - _textureWidth);
        Bounce(1, 0);
    }
}
void Ball::moveY(double timeStep) {
    // Move the texture up or down
    _posY += _velY * timeStep;

    // If the texture went too far up or down
    if (_posY < 0) {
        _posY = functionToDoOnEdge(0);
        Bounce(0, 1);
    }
    else if (_posY > SCREEN_HEIGHT - _textureHeight) {
        /*_posY = functionToDoOnEdge(SCREEN_HEIGHT - _textureHeight);
        Bounce(false, true);*/
        setActive(false);
    }
}