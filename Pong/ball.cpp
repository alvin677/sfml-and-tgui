#include "ball.h"

ball::ball()
{
	init();
}

void ball::Update()
{
	baseShape.move(ballspeedX, ballspeedY);
		
	if (baseShape.getPosition().y > 705 || baseShape.getPosition().y < 65) {
		ballspeedY = ballspeedY * -1;
	}
}

void ball::Render(sf::RenderWindow& win)
{
    win.draw(baseShape);
}

void ball::setBallspeedX(float new_speed)
{
	ballspeedX = new_speed;
}

void ball::setBallspeedY(float new_speed)
{
	ballspeedY = new_speed;
}

float ball::getBallspeedX()
{
	return ballspeedX;
}

float ball::getBallspeedY()
{
	return ballspeedY;
}

float ball::getX()
{
	return baseShape.getPosition().x;
}

float ball::getY()
{
	return baseShape.getPosition().y;
}

void ball::set_Position(float new_x, float new_y)
{
	baseShape.setPosition(new_x, new_y);
}

void ball::init()
{
	srand(time(0));
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	/*ballspeedX = rand() % 2000 - 1000;
	ballspeedY = rand() % 2000-1000;
	ballspeedX = ballspeedX / 2000;
	ballspeedY = ballspeedY / 2000;*/
	ballspeedX = 0;
	ballspeedY = 0;

	baseShape.setFillColor(sf::Color(r, g, b));
	baseShape.setRadius(15.f);
	baseShape.setPosition(1080 / 2, 720 / 2);
	baseShape.setOrigin(15, 15);
}
