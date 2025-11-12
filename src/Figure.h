#pragma once

#include <iostream>

#include "raylib.h"

namespace figure
{
	class Figure
	{
	private:
		Model model;
		float scale;
		Vector3 pos;
		Color color;

	public:
		Figure(std::string modelRef, float scale, Vector3 pos, Color color);
		~Figure();

		void draw();
	};
}

