#pragma once
#include <SFML/Graphics.hpp>
class ball
{
public:
	ball();
	void Update();
	void Render(sf::RenderWindow& win);

	void setBallspeedX(float new_speed);
	void setBallspeedY(float new_speed);
	float getBallspeedX();
	float getBallspeedY();
	float getX();
	float getY();
	void set_Position(float new_x, float new_y);


private:
	void init();
	sf::CircleShape baseShape;
	float ballspeedX;
	float ballspeedY;

};

