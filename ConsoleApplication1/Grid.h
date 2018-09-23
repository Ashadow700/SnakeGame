#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Grid
{

public:
	Grid(int squareSize, RenderWindow& w);
	~Grid();

	int getSquareSize();
	void drawSquare(int row, int col, sf::Color color) const;
	void drawGrid();
	void setValue(int row, int col, int value);
	void setValueAtMousePos(int posX, int posY, int value);
	void setValues(std::vector< std::vector<int>>& newMatrix);
	void setValue(std::vector<pair<int, int>>& vector);
	int getValue(int row, int col) const;
	void flipValue(int row, int col);
	int getRows() const;
	int getCols() const;

private:
	int squareSize;
	int rows;
	int cols;
	std::vector< std::vector<int> > matrix;
	RenderWindow& w;
};

