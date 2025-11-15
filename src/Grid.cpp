#include "Grid.h"

namespace grid
{
	const float distX = 0.1f;
	const float distY = 0.1f;
	const float distZ = 0.1f;

	const float startX = (-distX * maxX) / 2;
	const float startY = (-distY * maxY) / 2;
	const float startZ = (-distZ * maxZ) / 2;

	const Color pointColor = WHITE;

	Grid::Grid()
	{
		points = new Point * *[maxX];

		for (int i = 0; i < maxX; i++)
		{
			points[i] = new Point * [maxY];

			for (int j = 0; j < maxZ; j++)
			{
				points[i][j] = new Point[maxZ];

				for (int k = 0; k < maxZ; k++)
				{
					points[i][j][k].boundingBoxesIn = 0;
					points[i][j][k].figuresIn = 0;

					for (int l = 0; l < maxFigures; l++)
					{
						points[i][j][k].figures[l] = nullptr;
						points[i][j][k].boundingBoxes[l] = nullptr;
					}

					points[i][j][k].pos = { startX + i * distX, startY + j * distY , startZ + k * distZ};
				}
			}
		}
	}
	Grid::~Grid()
	{
		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				delete[] points[i][j];
				points[i][j] = nullptr;
			}
			delete[] points[i];
			points[i] = nullptr;
		}

		delete[] points;
		points = nullptr;
	}

	void Grid::update(std::vector<figure::Figure*> figures, int maxFigures)
	{
		for (int fig = 0; fig < maxFigures; fig++)
		{
			figures[fig]->isCollidingBoundingBox = false;
			figures[fig]->isCollidingFigure = false;
		}

		for (int x = 0; x < maxX; x++)
		{
			for (int y = 0; y < maxY; y++)
			{
				for (int z = 0; z < maxZ; z++)
				{
					points[x][y][z].boundingBoxesIn = 0;
					points[x][y][z].figuresIn = 0;
					points[x][y][z].color = pointColor;
				}
			}
		}

		for (int fig = 0; fig < maxFigures; fig++)
		{
			for (int x = 0; x < maxX; x++)
			{
				for (int y = 0; y < maxY; y++)
				{
					for (int z = 0; z < maxZ; z++)
					{
						if (figures[fig]->boundingBox.isPointCol(points[x][y][z].pos))
						{
							points[x][y][z].boundingBoxes[points[x][y][z].boundingBoxesIn] = figures[fig];
							points[x][y][z].color = GREEN;
							points[x][y][z].boundingBoxesIn++;

							if (figures[fig]->isPointCol(points[x][y][z].pos))
							{
								points[x][y][z].figures[points[x][y][z].figuresIn] = figures[fig];
								points[x][y][z].figuresIn++;
							}
						}
					}
				}
			}
		}

		for (int x = 0; x < maxX; x++)
		{
			for (int y = 0; y < maxY; y++)
			{
				for (int z = 0; z < maxZ; z++)
				{
					if (points[x][y][z].boundingBoxesIn > 1)
					{
						for (int bbI = 0; bbI < points[x][y][z].boundingBoxesIn; bbI++)
						{
							points[x][y][z].boundingBoxes[bbI]->isCollidingBoundingBox = true;
						}

						if (points[x][y][z].figuresIn > 1)
						{
							for (int fgi = 0; fgi < points[x][y][z].figuresIn; fgi++)
							{
								points[x][y][z].figures[fgi]->isCollidingFigure = true;
							}
						}
					}
				}
			}
		}
	}

	void Grid::draw()
	{
		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				for (int k = 0; k < maxZ; k++)
				{
					DrawPoint3D(points[i][j][k].pos, points[i][j][k].color);
				}
			}
		}
	}
}