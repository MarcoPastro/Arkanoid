#include "GameObject.h"

GameObject::GameObject(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int velocity, double x, double y)
    : textureGiver(textureGiver)
    , collisionManager(collisionManager)
    , _posX(x)
    , _posY(y)
    , nameTexture(nameTexture)
    , _velocity(velocity)
    , active(true) {
    _velX = _velocity;
    _velY = _velocity;
    functionToDoOnEdge = [](int edge) {
        return edge;
    };
    _texture = textureGiver->getTheTexture(nameTexture);
    if (_texture == nullptr) {
        printf("Failed to load the texture!\n");
    }
    else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}

GameObject::GameObject(TextureManagement* textureGiver, std::string nameTexture, CollisionManager* collisionManager, int (*functionToDo)(int), int velocity, double x, double y)
    : textureGiver(textureGiver)
    , collisionManager(collisionManager)
    , _posX(x)
    , _posY(y)
    , functionToDoOnEdge(functionToDoOnEdge)
    , nameTexture(nameTexture)
    , _velocity(velocity)
    , active(true) {
    _velX = _velocity;
    _velY = _velocity;
    _texture = textureGiver->getTheTexture(nameTexture);
    if (_texture == nullptr) {
        printf("Failed to load the texture!\n");
    }
    else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}


void GameObject::moveX(double timeStep) {
    // Move the texture left or right
    _posX += _velX * timeStep;

    // If the texture went too far to the left or right
    if (_posX < 0) {
        _posX = functionToDoOnEdge(0);
    }
    else if (_posX > SCREEN_WIDTH - _textureWidth) {
        _posX = functionToDoOnEdge(SCREEN_WIDTH - _textureWidth);
    }
}

void GameObject::moveY(double timeStep) {
    
    // Move the texture up or down
    _posY += _velY * timeStep;
    
    // If the texture went too far up or down
    if (_posY < 0) {
        _posY = functionToDoOnEdge(0);
    }
    else if (_posY > SCREEN_HEIGHT - _textureHeight) {
        _posY = functionToDoOnEdge(SCREEN_HEIGHT - _textureHeight);
    }
}


void GameObject::move(double timeStep) {
    double newX1 = _posX + _velX * timeStep;
    double newY1 = _posY + _velY * timeStep;
    double newX2 = newX1 + _textureWidth;
    double newY2 = newY1 + _textureHeight;
    if (collisionManager->CheckCollision(newX1, newY1, newX2, newY2)>0) return;
    moveY(timeStep);
    moveX(timeStep);
}
void GameObject::render() {
    // Show the texture
    if (active) {
        _texture->render((int)_posX, (int)_posY);
    }
}

// Sets the position of this texture (0,0 is the top left)
void GameObject::setPosX(double posX) {
    _posX = posX;
}
void GameObject::setPosY(double posY) {
    _posY = posY;
}

// Gets the position of this texture (0,0 is the top left)
const double GameObject::getPosX() {
    return _posX;
}
const double GameObject::getPosY() {
    return _posY;
}

// Sets the general velocity of this texture with a multiplier
void GameObject::setVelocity(int velocity) {
    _velocity = velocity;
    _velX = velocity;
    _velY = velocity;
}

int GameObject::getVelocity() {
    return _velocity;
}

// Sets the current velocity of this texture
void GameObject::setVelX(double velX) {
    _velX = velX;
}
void GameObject::setVelY(double velY) {
    _velY = velY;
}

// Gets the current velocity of this texture
const double GameObject::getVelX() {
    return _velX;
}
const double GameObject::getVelY() {
    return _velY;
}

// Gets the current velocity of this texture
const int GameObject::getTextureWidth() {
    return _textureWidth;
}
const int GameObject::getTextureHeight() {
    return _textureHeight;
}

void GameObject::ChangeTexture(std::string nameTexture) {
    if (nameTexture != "Empty") {
        MGDTexture* check = textureGiver->getTheTexture(nameTexture);
        if (check == nullptr) return;
        _texture = check;
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
    else {
        setActive(false);
    }
}

void GameObject::setActive(bool value) {
    active = value;
    if (active) {// Reset the values of the textureWidth and Height
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
        return;
    }
}
bool GameObject::getActive() {
    return active;
}

TextureManagement* GameObject::GetTextureManagement()
{
    return textureGiver;
}

MGDTexture* GameObject::GetTexture()
{
    return _texture;
}
