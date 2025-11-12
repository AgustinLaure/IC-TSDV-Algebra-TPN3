#include "Figure.h"

namespace figure
{
	Figure::Figure(std::string modelRef, float scale, Vector3 pos, Color color) : scale(scale), pos(pos), color(color)
	{
		model = LoadModel(modelRef.c_str());
	}
	Figure::~Figure()
	{
		UnloadModel(model);
	}

	void Figure::draw()
	{
		DrawModel(model, pos, scale, color);
	}
}
