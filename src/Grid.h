#pragma once

#include "Figure.h"

namespace grid
{
	const int maxX = 30;
	const int maxY = 30;
	const int maxZ = 30;

	const int maxFigures = 6;

	struct Point
	{
		Color color;

		Vector3 pos;
		figure::Figure* boundingBoxes[maxFigures];
		int boundingBoxesIn;

		figure::Figure* figures[maxFigures];
		int figuresIn;
	};

class Grid
{
public:
	Point*** points;
	Grid();
	~Grid();

	void update(std::vector<figure::Figure*>, int maxFigures);
	void draw();
};
}

