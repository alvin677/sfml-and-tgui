#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include "ball.h"

int main()
{
	// Inställningarna för spel rutan
	int xWindow = 1080;
	int yWindow = 720;
	int player1Score = 0;
	int player2Score = 0;
	sf::RenderWindow window(sf::VideoMode(xWindow, yWindow), "P1: W A S D | P2: Piltangenter");


	// Här laddas fontsen in för att sedan kunna användas till att skriva text med
	sf::Font font;
	if (!font.loadFromFile("Fonts/edition.ttf"))
		throw("Could not load font.");

	sf::Font font2;
	if (!font2.loadFromFile("Fonts/snowy.ttf"))
		throw("Could not load font.");
	
	// Här skapar man text objekt
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
	sf::Text text4;

	// Här ändrar man hur texten ska vara
	text.setFont(font);
	text.setCharacterSize(48);
	text.setStyle(sf::Text::Bold);
	text.setPosition(310, 0);
	text.setString("Score: 0");

	text2.setFont(font);
	text2.setCharacterSize(48);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(600, 0);
	text2.setString("Score: 0");

	text3.setFont(font2);
	text3.setCharacterSize(32);
	text3.setStyle(sf::Text::Bold);
	text3.setPosition(220, 675);
	text3.setString("Player 1: W and S     Player 2: Up Arrow and Down Arrow");

	text4.setFont(font2);
	text4.setCharacterSize(72);
	text4.setStyle(sf::Text::Bold);
	text4.setPosition(1080/4, 720 / 2);
	text4.setString("Press SPACEBAR to start");



	// Här skapas spelarna och modifieras
	sf::RectangleShape player;
	sf::RectangleShape player2;
	ball pongball;
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(1080, 5));
	line.setPosition(0, 50);
	line.setFillColor(sf::Color::Magenta);
	player.setSize(sf::Vector2f(20, 100));
	player.setFillColor(sf::Color::Cyan);
	player.setPosition(50, yWindow/2 - 50);	

	player2.setSize(sf::Vector2f(20, 100));
	player2.setFillColor(sf::Color::Red);
	player2.setPosition(1080 - 70, yWindow / 2 - 50);

	// Hastigheten på spelarna
	float speed = 0.3;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.move(0, speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.move(0, -speed);
		}

		if	(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			player2.move(0, -speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player2.move(0, speed);
		}

		if (player.getPosition().y > 720-100) {
			player.move(0, -0.3);
		}
		if (player.getPosition().y < 55) {
			player.move(0, 0.3);
		}
		if (player2.getPosition().y >720-100) {
			player2.move(0, -0.3);
		}
		if (player2.getPosition().y < 55) {
			player2.move(0, 0.3);
		}

		// Kollar collision med spelare 1 och bollen
		if (player.getPosition().x+20 < pongball.getX() + 30 &&
			player.getPosition().x + 20 > pongball.getX() &&
			player.getPosition().y < pongball.getY() + 30 &&
			100 + player.getPosition().y > pongball.getY()) {

			pongball.setBallspeedX((pongball.getBallspeedX() - 0.02) * -1);
		}

		// Kollar collision med spelare 2 och bollen
		if (player2.getPosition().x+20 < pongball.getX() + 30 &&
			player2.getPosition().x + 20 > pongball.getX() &&
			player2.getPosition().y < pongball.getY() + 30 &&
			100 + player2.getPosition().y > pongball.getY()) {
			
			pongball.setBallspeedX((pongball.getBallspeedX() + 0.02)* -1);
		}

		// Väntar på att spelet ska starta genom att trycka på Space tangenten
		if (pongball.getBallspeedX() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			pongball.setBallspeedX(0.3);
			pongball.setBallspeedY(0.3);
		}

		if (pongball.getX() < 15) {
			// Player 2 scores
			sf::SoundBuffer buffer;
			if (!buffer.loadFromFile("Sound/sound.wav")) {
				throw("Game broke :/");
			}
			sf::Sound sound;
			sound.setBuffer(buffer);
			sound.play();
			pongball.set_Position(1080 / 2, 720 / 2);
			player.setPosition(50, yWindow / 2 - 50);
			player2.setPosition(1080 - 70, yWindow / 2 - 50);
			player2Score += 1;
			text2.setString("Score: " + std::to_string(player2Score));

			// Här ställer den in bollens värde till 0 på X och Y så den står stilla, ovanför ligger koden
			// där spelet väntar på att man ska trycka på Space om X hastigheten är 0.
			pongball.setBallspeedX(0);
			pongball.setBallspeedY(0);

		}
		if (pongball.getX() > 1065) {
			// Player 1 scores
			sf::SoundBuffer buffer;
			if (!buffer.loadFromFile("Sound/sound.wav")) {
				throw("Game broke :/");
			}
			sf::Sound sound;
			sound.setBuffer(buffer);
			sound.play();
			pongball.set_Position(1080 / 2, 720 / 2);
			player.setPosition(50, yWindow / 2 - 50);
			player2.setPosition(1080 - 70, yWindow / 2 - 50);
			player1Score += 1;
			text.setString("Score: " + std::to_string(player1Score)); // Lägger till en på Score

			// Samma sak här, se ovan.
			pongball.setBallspeedX(0);
			pongball.setBallspeedY(0);
		}

			// Ritar upp allt
			window.clear();
			window.draw(player);
			window.draw(player2);
			window.draw(text);
			window.draw(text2);
			window.draw(line);
			window.draw(text3);
			if (pongball.getBallspeedX() == 0) {
				window.draw(text4);
			}
			pongball.Update();
			pongball.Render(window);
			window.display();

	}

}