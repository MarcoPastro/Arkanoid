#include "Direction.h"

Direction::Direction(int x, int y): x(x),y(y) {
}
// -1 left, 0 not moving, 1 right
int	Direction::GetX() {
	return x;
}
// -1 up, 0 not moving, 1 down
int	Direction::GetY() {
	return y;
}
// -1 left, 0 not moving, 1 right
void Direction::SetX(int newx) {
	x = newx;
}
// -1 up, 0 not moving, 1 down
void Direction::SetY(int newy) {
	y = newy;
}