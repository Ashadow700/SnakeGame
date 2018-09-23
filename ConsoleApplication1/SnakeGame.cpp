#include "pch.h"
#include "SnakeGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <deque>

using namespace sf;
using std::cout;
using std::endl;
using std::pair;


SnakeGame::SnakeGame(Grid& grid) : grid(grid) {
	cout << "SnakeGame constructor running" << endl;
	initMatrix();
	reset();
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::initMatrix() {
	for (int i = 0; i < grid.getRows(); ++i) {
		std::vector<int> row;
		for (int k = 0; k < grid.getCols(); ++k) {
			row.push_back(0);
		}
		newMatrix.push_back(row);
	}
}

void SnakeGame::tick() {	
	pair<int, int> posChange = findNextPosChange();
	pair<int, int> nextPos{currentPos.first+posChange.first, currentPos.second + posChange.second};
	if (checkOutOfBounds(nextPos)) {
		reset();
		return;
	} else if (checkCollision(nextPos)) {
		reset();
		return;
	}
	
	currentPos = nextPos;
	snake.push_front(currentPos);
	if (currentPos == target) {
		placeTarget();
	} else {
		snake.pop_back();
	}
	
	fillMatrix();
	grid.setValues(newMatrix);
}

bool SnakeGame::checkOutOfBounds(pair<int, int>& nextPos) {
	return (nextPos.second < 0 || nextPos.second >= grid.getRows() || nextPos.first < 0 || nextPos.first >= grid.getCols());
}

bool SnakeGame::checkCollision(pair<int, int>& nextPos) {
	for (auto it = snake.begin(); it != snake.end(); ++it) {
		if (nextPos == *it) {
			cout << "Collision detected at pos <first, second> " << nextPos.first << ", " << nextPos.second  << ">" << endl;
			return true;
		}
	}
	return false;
}

void SnakeGame::reset() {
	cout << "Resetting..." << endl;
	snake.clear();
	currentPos.first = grid.getCols() / 2;
	currentPos.second = grid.getRows() / 2;

	pair<int, int> pos2(currentPos.first - 1, currentPos.second);
	pair<int, int> pos3(currentPos.first - 2, currentPos.second);
	snake.insert(snake.end(), { currentPos, pos2, pos3 });

	direction = sf::Keyboard::Key::Right;

	placeTarget();
	resetMatrix();
	cout << "Finished resetting..." << endl;
}

std::pair<int, int> SnakeGame::findNextPosChange() {
	direction = findNewDirection();

	if (direction == Keyboard::Up) {
		return pair<int, int> {0, -1};
	}
	else if (direction == Keyboard::Down) {
		return pair<int, int> {0, 1};
	}
	else if (direction == Keyboard::Right) {
		return pair<int, int> {1, 0};
	}
	else if (direction == Keyboard::Left) {
		return pair<int, int> {-1, 0};
	}
	else {
		throw std::invalid_argument("Direction have the invalid value :" + direction);
	}
}

sf::Keyboard::Key SnakeGame::findNewDirection() {
	if (Keyboard::isKeyPressed(Keyboard::Up) && direction != Keyboard::Down) {
		cout << "Returning Keyboard::Up" << endl;
		return Keyboard::Up;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && direction != Keyboard::Up) {
		cout << "Returning Keyboard::Down" << endl;
		return Keyboard::Down;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && direction != Keyboard::Left) {
		cout << "Returning Keyboard::Right" << endl;
		return Keyboard::Right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && direction != Keyboard::Right) {
		cout << "Returning Keyboard::Left" << endl;
		return Keyboard::Left;
	}
	else {
		cout << "Returning direction" << endl;
		return direction;
	}
}

void SnakeGame::placeTarget() {
	cout << "Placing new target..." << endl;
	std::vector<pair<int, int>> validTargets = findValidTargets();
	placeTarget(validTargets);
}


void SnakeGame::placeTarget(std::vector<pair<int, int>>& validTargets) {
	int selected = rand() % validTargets.size();
	cout << "selected target <"<< validTargets[selected].first << ", " << validTargets[selected].second << ">" << endl;
	target = validTargets[selected];
	cout << "target selected" << endl;
}

std::vector<pair<int, int>> SnakeGame::findValidTargets() {
	std::vector<pair<int, int>> validTargets;
	for (int row = 0; row < grid.getRows(); ++row) {
		for (int col = 0; col < grid.getCols(); ++col) {
			
			pair<int, int> target = { col, row };
			if (checkTargetValid(target)) {
				validTargets.push_back(target);
			}
		}
	}
	return validTargets;
}

bool SnakeGame::checkTargetValid(pair<int, int>& pos) {
	for (auto it = snake.begin(); it != snake.end(); ++it) {
		if (pos == *it) {
			cout << "pos <row, col> <" << pos.first << ", " << pos.second << "> is not valid" << endl;
			return false;
		}
	}
	return true;
}


void SnakeGame::fillMatrix() {
	resetMatrix();

	for (auto it = snake.begin(); it != snake.end(); ++it) {
		pair<int, int> pos = *it;
		newMatrix[pos.second][pos.first] = 1;
	}
	cout << "Placed snake on newMatrix" << endl;

	newMatrix[target.second][target.first] = 2;
	cout << "Placed target on newMatrix" << endl;
}

void SnakeGame::resetMatrix() {
	cout << "Reseting matrix..." << endl;
	for (int i = 0; i < grid.getRows(); ++i) {
		for (int k = 0; k < grid.getCols(); ++k) {
			newMatrix[i][k] = 0;
		}
	}
	cout << "Finished reseting matrix..." << endl;
}
