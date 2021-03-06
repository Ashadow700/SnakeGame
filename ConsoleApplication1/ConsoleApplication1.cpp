#include "pch.h"
#include "Grid.h"
#include "SnakeGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;
using std::pair;

using namespace sf;


void getGridPos(sf::RenderWindow& w, Grid& grid) {
	int posX = sf::Mouse::getPosition(w).x;
	int posY = sf::Mouse::getPosition(w).y;
	cout << "Mouse position = [" << posX << "," << posY << "]" << endl;

	int modX = posX % grid.getSquareSize();
	int modY = posY % grid.getSquareSize();
	
	posX -= modX;
	posY -= modY;
	cout << "Mouse position = [" << posX << "," << posY << "]" << endl;
	
	int row = posY / grid.getSquareSize();
	int col = posX / grid.getSquareSize();
	cout << "Grid position = [" << row << "," << col << "]" << endl;

	grid.setValue(row, col, 1);
}

int main() {

	unsigned int width = 300;
	unsigned int height = 200;

	unsigned int lineWidth = 5;

	sf::RenderWindow w(sf::VideoMode(width, height), "Snake Game");
	w.setFramerateLimit(60);

	sf::Clock clock;
	double timer = 0;
	double delay = 0.25;

	cout << "before constructor" << endl;
	Grid grid(25, w);
	SnakeGame snakeGame(grid);
	
	while (w.isOpen()) {

		Event event;
		while (w.pollEvent(event)) {
			if (event.type == Event::Closed) {
				w.close();
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				grid.setValueAtMousePos(sf::Mouse::getPosition(w).x, sf::Mouse::getPosition(w).y, 1);
				
			}
		}


		timer = clock.getElapsedTime().asSeconds();
		if (timer > delay) {
			clock.restart();
			snakeGame.tick();
		}

		grid.drawGrid();
		w.display();
	}

	return 0;
}





/*
if (Keyboard::isKeyPressed(Keyboard::Up)) {
	grid.setValue(10, 10, 1);
}
else if (Keyboard::isKeyPressed(Keyboard::Down)) {
	grid.setValue(10, 11, 1);
}
else {
	grid.setValue(10, 10, 0);
}

*/

/*
	std::pair <int, int> pos1(0, 0);
	std::pair <int, int> pos2(0, 1);
	pair <int, int> pos3(1, 1);
	pair <int, int> pos4(2, 1);
	pair <int, int> pos5(3, 1);
	std::vector<pair<int, int>> testVector{ pos1, pos2, pos3, pos4, pos5 };
	//testVector.push_back(pos1);
	//testVector.push_back(pos2);

	pos3 = testVector[0];
	cout << "pair first = " << pos3.first << " pair second = " << pos3.second << endl;

	pos3 = testVector[1];
	cout << "pair first = " << pos3.first << " pair second = " << pos3.second << endl;
	grid.setValue(testVector);

	sf::Keyboard::Key key = Keyboard::Up;
*/

/*
	std::pair <int, int> pos(2, 3);
	cout << "pair first = " << pos.first << "pair second = " << pos.second << endl;
	pos.first = 4;
	cout << "pair first = " << pos.first << "pair second = " << pos.second << endl;

*/


//grid.flipValue(11, 10);

//sf::RenderWindow& w








/*

		for (int col = 0; col < grid.getCols(); col += 2) {
			grid.drawSquare(4, col);
		}
		grid.drawSquare(0, 0);
		grid.drawSquare(5, 1);
*/


/*
if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	Vector2i pos = sf::Mouse::getPosition(w);

	cout << "Mouse position = [" << pos.x << "," << pos.y << "]" << endl;
}
*/




/*
		RectangleShape rectangle(Vector2f(3, 200));
		rectangle.setPosition(400, 0);

		w.draw(rectangle);*/