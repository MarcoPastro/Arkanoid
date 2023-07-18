#include "CollisionManager.h"
#include "Ball.h"
#include "Block.h"
/*
@brief
check if two doubles are equals based on a precision.
@param f1 the first float.
@param f2 the second float.
@param precisions the precision of the operation set by default 0.001f.
@return True if the f1 and the f2 are equals with some precision.
*/
bool isNearlyEquals(double f1, double f2, double precisions = 0.001f)
{
	double fr = f2 - f1;
	if (fr < 0) {
		fr = -fr;
	}
	return (fr <= precisions);
}

//function that check if point xp and yp if is inside the sqaure x1,y1,x2,y2 true else false(<)(default x1=0,y1=0,x2=0,y3=0)(use the function isNearlyEquals
/*
@brief
check if the point is inside or on the edge of the rectangle and the default is the rectangle x1=0,y1=0,x2=1,y2=1.
@param xp the x of the point.
@param yp the y of the point.
@param x1 left side of the rectangle and the default is 0.
@param x2 right side of the rectangle.
@param y1 bottom side of the rectangle.
@param y2 top side of the rectangle.
@return True if is inside on the edge of the rectangle considerating the perimeter of the rectangle.
*/
int isPointInsideASquare(double xp, double yp, double x1, double x2, double y1, double y2, double offsetYDetection)
{
	if (!(   (((yp > y1) && (yp < y2)) 
			 || isNearlyEquals(yp, y1) 
		     || isNearlyEquals(yp, y2)) && (((xp > x1) && (xp < x2)) 
											|| isNearlyEquals(xp, x1) 
											|| isNearlyEquals(xp, x2)) )) {
		return 0;
	}
	if (yp - y1 < offsetYDetection || y2 - yp < offsetYDetection) {
		return -1;
	}
	return 1;
}


CollisionManager::CollisionManager() {
	arrayListOfBlocks = new ArrayList();
	arrayOfBalls = new ArrayList();
}

CollisionManager::~CollisionManager() {
	delete arrayListOfBlocks;
	delete arrayOfBalls;
}

CollisionManager& CollisionManager::operator=(CollisionManager& other)
{
	if (this != &other) {
		delete arrayListOfBlocks;
		delete arrayOfBalls;
		arrayListOfBlocks = other.GetArrayListOfBlocks();
		arrayOfBalls = other.GetArrayOfBalls();
	}
	return *this;
}

ArrayList* CollisionManager::GetArrayListOfBlocks() {
	return arrayListOfBlocks;
}
ArrayList* CollisionManager::GetArrayOfBalls() {
	return arrayOfBalls;
}

void CollisionManager::AddBlock(Block* blockToAdd) {
	arrayListOfBlocks->Add(blockToAdd);
}
void CollisionManager::AddBlocks(Block** blocksToAdd, int dim) {
	for (int i = 0; i < dim; ++i) {
		arrayListOfBlocks->Add(blocksToAdd[i]);
	}
}
void CollisionManager::AddBall(Ball* ballToAdd) {
	arrayOfBalls->Add(ballToAdd);
}
void CollisionManager::AddBalls(Block** ballsToAdd, int dim) {
	for (int i = 0; i < dim; ++i) {
		arrayOfBalls->Add(ballsToAdd[i]);
	}
}
int CollisionManager::CheckCollision(double x1Pos, double y1Pos, double x2Pos, double y2Pos) {
	int sizeArray = arrayListOfBlocks->GetSize();

	for (int i = 0; i < sizeArray; ++i) {
		Block* b = (Block*) arrayListOfBlocks->Get(i);
		if (b->getActive()) {
			double v1x = b->getPosX();
			double v1y = b->getPosY();

			double v2x = b->getPosX() + b->getTextureWidth();
			double v2y = b->getPosY() + b->getTextureHeight();

			int r1 = isPointInsideASquare(x1Pos, y1Pos, v1x, v2x, v1y, v2y, offsetYDetection);
			switch (r1) {
			case -1:
				b->Hit();
				return r1;
				break;
			case 1:
				b->Hit();
				return r1;
				break;
			}
				
			int r2 = isPointInsideASquare(x2Pos, y1Pos, v1x, v2x, v1y, v2y, offsetYDetection);
			switch (r2) {
			case -1:
				b->Hit();
				return r2;
				break;
			case 1:
				b->Hit();
				return r2;
				break;
			}

			int r3 = isPointInsideASquare(x1Pos, y2Pos, v1x, v2x, v1y, v2y, offsetYDetection);
			switch (r3) {
			case -1:
				b->Hit();
				return r3;
				break;
			case 1:
				b->Hit();
				return r3;
				break;
			}

			int r4 = isPointInsideASquare(x2Pos, y2Pos, v1x, v2x, v1y, v2y, offsetYDetection);
			switch (r4) {
			case -1:
				b->Hit();
				return r4;
				break;
			case 1:
				b->Hit();
				return r4;
				break;
			}
		}
	}
	return 0;
}

bool CollisionManager::CheckBallPosition(double x1Pos, double y1Pos, double x2Pos, double y2Pos) {
	int sizeArray = arrayOfBalls->GetSize();

	for (int i = 0; i < sizeArray; ++i) {
		Ball* b = (Ball*) arrayOfBalls->Get(i);
		if (b->getActive()) {
			double v1x = b->getPosX();
			double v1y = b->getPosY();

			double v2x = b->getPosX() + b->getTextureWidth();
			double v2y = b->getPosY() + b->getTextureHeight();

			if (isPointInsideASquare(x1Pos, y1Pos, v1x, v2x, v1y, v2y, offsetYDetection)
				|| isPointInsideASquare(x2Pos, y1Pos, v1x, v2x, v1y, v2y, offsetYDetection)
				|| isPointInsideASquare(x1Pos, y2Pos, v1x, v2x, v1y, v2y, offsetYDetection)
				|| isPointInsideASquare(x2Pos, y2Pos, v1x, v2x, v1y, v2y, offsetYDetection)) return true;

		}
	}
	return false;
}