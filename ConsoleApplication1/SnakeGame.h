#pragma once
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <deque>

using namespace sf;
using std::pair;

class SnakeGame
{
public:
	SnakeGame(Grid& grid);
	~SnakeGame();

	void reset();
	void tick();

private:
	Grid& grid;
	std::deque<pair<int, int>> snake;
	std::vector<std::vector<int>> newMatrix;
	std::pair<int, int> currentPos;
	std::pair<int, int> target;
	sf::Keyboard::Key direction;

	void resetMatrix();
	void fillMatrix();
	void initMatrix();
	std::vector<pair<int, int>> findValidTargets();
	bool checkTargetValid(pair<int, int>& pos);
	void placeTarget(std::vector<pair<int, int>>& validTargets);
	void placeTarget();
	bool checkOutOfBounds(pair<int, int>& nextPos);
	bool checkCollision(pair<int, int>& nextPos);
	std::pair<int, int> findNextPosChange();
	sf::Keyboard::Key findNewDirection();
};



