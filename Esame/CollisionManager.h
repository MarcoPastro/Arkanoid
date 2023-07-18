#pragma once
#include "ArrayList.h" 

class Block;
class Ball;

#ifndef COLLISIONMANAGER_H // include guard
#define COLLISIONMANAGER_H
class CollisionManager {
public:
    /*
        @brief
        create the Collision Manager empty
    */
    CollisionManager();
    /*
        @brief
        call the deconstractor of both arraylist
    */
    ~CollisionManager();
    /*
        @brief
        delete the old arraylist and take a pointer to the new ones
        @param other the other collision manager
    */
    CollisionManager& operator=(CollisionManager& other);
    /*
        @brief
        add the block to the specific arraylist
        @param blockToAdd block to add
    */
    void AddBlock(Block* blockToAdd);
    /*
        @brief
        add the blocks to the specific arraylist
        @param blocksToAdd blocks to add
        @param dim dimension of the array to add
    */
    void AddBlocks(Block** blocksToAdd, int dim);
    /*
        @brief
        add the ball to the specific arraylist
        @param ballToAdd ball to add
    */
    void AddBall(Ball* ballToAdd);
    /*
        @brief
        add the balls to the specific arraylist
        @param ballsToAdd balls to add
        @param dim dimension of the array to add
    */
    void AddBalls(Block** ballsToAdd, int dim);
    /*
        @brief
        checks the collision with 2 points that forms a rectangle
        @param x1Pos x of the up left point
        @param y1Pos y of the up left point
        @param x2Pos x of the down right point
        @param y2Pos y of the down right point
        @return 
    */
    int CheckCollision(double x1Pos, double y1Pos, double x2Pos, double y2Pos);
    /*
        @brief
        checks the collision with 2 points that forms a rectangle
        @param x1Pos x of the up left point
        @param y1Pos y of the up left point
        @param x2Pos x of the down right point
        @param y2Pos y of the down right point
    */
    bool CheckBallPosition(double x1Pos, double y1Pos, double x2Pos, double y2Pos);
    /*
        @brief
        get the arraylist of blocks
    */
    ArrayList* GetArrayListOfBlocks();
    /*
        @brief
        get the arraylist of balls
    */
    ArrayList* GetArrayOfBalls();
private:
    class ArrayList* arrayListOfBlocks;
    class ArrayList* arrayOfBalls;
    double offsetYDetection = 0.2;
};
#endif
