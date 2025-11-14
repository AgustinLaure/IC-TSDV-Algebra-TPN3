#pragma once

#include "raylib.h"
#include "raymath.h"

namespace boundingBox
{
	class BoundingBox
	{
	public:
		Vector3 min;
		Vector3 max;

		Color color;

		BoundingBox();
		BoundingBox(Vector3 min, Vector3 max);
		~BoundingBox();

		void draw();
	};
}

