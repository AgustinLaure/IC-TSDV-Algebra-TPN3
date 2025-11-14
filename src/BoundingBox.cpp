#include "BoundingBox.h"

namespace boundingBox
{
	const Color linesColor = YELLOW;

	BoundingBox::BoundingBox() : color(linesColor) {}
	BoundingBox::BoundingBox(Vector3 min, Vector3 max) : min(min), max(max) {}
	BoundingBox::~BoundingBox() {}

	void BoundingBox::draw()
	{
		Vector3 edges[8];

		edges[0] = min;
		edges[1] = min + Vector3{ 0.0f,0.0f,max.z - min.z };
		edges[2] = max - Vector3{ 0.0f,max.y - min.y,0.0f };
		edges[3] = min + Vector3{ max.x - min.x,0.0f,0.0f };
		edges[4] = min + Vector3{ 0.0f,max.y - min.y,0.0f };
		edges[5] = max - Vector3{ max.x - min.x,0.0f,0.0f };
		edges[6] = max;
		edges[7] = max - Vector3{ 0.0f,0.0f, max.z - min.z };

		DrawLine3D(edges[0], edges[1], color);
		DrawLine3D(edges[1], edges[2], color);
		DrawLine3D(edges[2], edges[3], color);
		DrawLine3D(edges[3], edges[0], color);
		DrawLine3D(edges[4], edges[5], color);
		DrawLine3D(edges[5], edges[6], color);
		DrawLine3D(edges[6], edges[7], color);
		DrawLine3D(edges[7], edges[4], color);
		DrawLine3D(edges[4], edges[0], color);
		DrawLine3D(edges[5], edges[1], color);
		DrawLine3D(edges[6], edges[2], color);
		DrawLine3D(edges[7], edges[3], color);

		//DrawPoint3D(edges[0], ORANGE);
		//DrawPoint3D(edges[1], ORANGE);
		//DrawPoint3D(edges[2], ORANGE);
		//DrawPoint3D(edges[3], ORANGE);
		//DrawPoint3D(edges[4], ORANGE);
		//DrawPoint3D(edges[5], ORANGE);
		//DrawPoint3D(edges[6], ORANGE);
		//DrawPoint3D(edges[7], ORANGE);
	}
}

