#pragma once
#ifndef DIRECTION_H // include guard
#define DIRECTION_H
class Direction
{
public:
	Direction(int x = 0, int y = 0);
	/*
		@brief
		get the direction on the x axis (-1 left, 0 not moving, 1 right)
		@return the GameObject or null
	*/
	int	GetX();
	/*
		@brief
		get the direction on the x axis (-1 up, 0 not moving, 1 down)
		@return the GameObject or null
	*/
	int	GetY();
	/*
		@brief
		set the direction on the x axis (-1 up, 0 not moving, 1 down)
		@param newx the new value
	*/
	void SetX(int newx);
	/*
		@brief
		set the direction on the x axis (-1 up, 0 not moving, 1 down)
		@param newy the new value
	*/
	void SetY(int newy);
private:
	int x;
	int y;
};
#endif
