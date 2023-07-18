#include "Player.h"

Player::Player(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x, double y)
    :Block(textureGiver, nameTexture, collisionManager, velocity,x, y) {
}
Player::Player(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x, double y)
    :Block(textureGiver, nameTexture, collisionManager, functionToDo, velocity,x, y) {
}


void Player::ChangeDirection(Direction direction) {
    _velY = _velocity * direction.GetY(); //_velY + _velocity * direction.GetY();
    _velX = _velocity * direction.GetX(); //_velX + _velocity * direction.GetX();
}

void Player::handleEvent(SDL_Event& sdlEvent) {
    // If a key was pressed
    if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
        // Adjust the velocity
        Direction* mDirection = new Direction();
        
        switch (sdlEvent.key.keysym.sym) {
        /*case SDLK_UP:
        case 'w':
            mDirection->SetY(-1);
            break;
        case SDLK_DOWN:
        case 's':
            mDirection->SetY(1);
            break;*/
        case SDLK_LEFT:
        case 'a':
            mDirection->SetX(-1);
            break;
        case SDLK_RIGHT:
        case 'd':
            mDirection->SetX(1);
            break;
        }

        ChangeDirection(*mDirection);
        delete mDirection;
    }
    // If a key was released
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
        // Adjust the velocity

        Direction* mDirection = new Direction();

        switch (sdlEvent.key.keysym.sym) {
        /*case SDLK_UP:
        case 'w':
            mDirection->SetY(0);
            break;
        case SDLK_DOWN:
        case 's':
            mDirection->SetY(0);
            break;*/
        case SDLK_LEFT:
        case 'a':
            mDirection->SetX(0);
            break;
        case SDLK_RIGHT:
        case 'd':
            mDirection->SetX(0);
            break;
        }

        ChangeDirection(*mDirection);

        delete mDirection;
    }

    
    
}

void Player::move(double timeStep) {
    double newX1 = _posX + _velX * timeStep;
    double newY1 = _posY + _velY * timeStep;
    double newX2 = newX1 + _textureWidth;
    double newY2 = newY1 + _textureHeight;
    if (collisionManager->CheckBallPosition(newX1, newY1, newX2, newY2) > 0) return;
    moveY(timeStep);
    moveX(timeStep);
}