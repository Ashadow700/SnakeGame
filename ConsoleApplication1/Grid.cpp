#include "pch.h"
#include "Grid.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Grid::Grid(int squareSize, RenderWindow& w) : squareSize(squareSize), w(w) {
	cout << "Grid constructor running, Square = " << squareSize << endl;
	cout << "x size = " << w.getSize().x << endl;
	cout << "y size = " << w.getSize().y << endl;

	rows = (w.getSize().y / squareSize);
	cols = (w.getSize().x / squareSize);
	
	matrix.resize(rows);
	for (int index = 0; index < rows; ++index) {
		matrix[index].resize(cols);
	}
}

Grid::~Grid() {
}

void Grid::setValue(int row, int col, int value) {
	matrix[row][col] = value;
}

void Grid::setValueAtMousePos(int posX, int posY, int value) {
	int modX = posX % squareSize;
	int modY = posY % squareSize;

	posX -= modX;
	posY -= modY;
	cout << "Mouse position = [" << posX << "," << posY << "]" << endl;

	int row = posY / squareSize;
	int col = posX / squareSize;
	cout << "Grid position = [" << row << "," << col << "]" << endl;

	setValue(row, col, 1);
}

void Grid::setValues(std::vector< std::vector<int>>& newMatrix) {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			matrix[row][col] = newMatrix[row][col];
		}
	}
}

void Grid::setValue(std::vector<pair<int, int>>& vector) {
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		pair<int, int> pos = *it;
		setValue(pos.second, pos.first, 1);
	}
}

int Grid::getValue(int row, int col) const {
	return(matrix[row][col]);
}

void Grid::flipValue(int row, int col)  {
	if (matrix[row][col] == 0) {
		matrix[row][col] = 1;
	} else if (matrix[row][col] == 1) {
		matrix[row][col] = 0;
	}
}

int Grid::getRows() const {
	return rows;
}

int Grid::getCols() const {
	return cols;
}

int Grid::getSquareSize() {
	return squareSize;
}

void Grid::drawGrid() {
	w.clear();
	for (int row = 0; row < rows; ++row ) {
		for (int col = 0; col < cols; ++col) {
			if (matrix[row][col] == 1) {
				drawSquare(row, col, sf::Color::White);
			} else if (matrix[row][col] == 2) {
				drawSquare(row, col, sf::Color::Red);
			}

		}
	}
}

void Grid::drawSquare(int row, int col, sf::Color color) const {
	RectangleShape rectangle(Vector2f(squareSize, squareSize));
	rectangle.setPosition(col*squareSize, row*squareSize);
	rectangle.setFillColor(color);
	w.draw(rectangle);
}