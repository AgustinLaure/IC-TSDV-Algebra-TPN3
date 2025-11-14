#include "BoundingBox.h"

namespace boundingBox
{
	const Color linesColor = YELLOW;

	BoundingBox::BoundingBox() : color(linesColor) 
	{
		max = { 0.0f,0.0f,0.0f };
		min = { 0.0f,0.0f,0.0f };
		maxVertices = 0;
	}
	BoundingBox::~BoundingBox() {}

	void BoundingBox::init(std::vector <Vector3>& figureVertices, int figureMaxVert)
	{
		Vector3 minAux = { INT_MAX,INT_MAX,INT_MAX };
		Vector3 maxAux = { INT_MIN,INT_MIN,INT_MIN };

		for (int i = 0; i < figureMaxVert; i++)
		{
			minAux.x = fminf(minAux.x, figureVertices[i].x);
			minAux.y = fminf(minAux.y, figureVertices[i].y);
			minAux.z = fminf(minAux.z, figureVertices[i].z);

			maxAux.x = fmaxf(maxAux.x, figureVertices[i].x);
			maxAux.y = fmaxf(maxAux.y, figureVertices[i].y);
			maxAux.z = fmaxf(maxAux.z, figureVertices[i].z);
		}

		min = minAux;
		max = maxAux;

		maxVertices = 8;

		vertices[0] = min;
		vertices[1] = min + Vector3{ 0.0f,0.0f,max.z - min.z };
		vertices[2] = max - Vector3{ 0.0f,max.y - min.y,0.0f };
		vertices[3] = min + Vector3{ max.x - min.x,0.0f,0.0f };
		vertices[4] = min + Vector3{ 0.0f,max.y - min.y,0.0f };
		vertices[5] = max - Vector3{ max.x - min.x,0.0f,0.0f };
		vertices[6] = max;
		vertices[7] = max - Vector3{ 0.0f,0.0f, max.z - min.z };

		setPlanes();
	}

	void BoundingBox::setPlanes()
	{
		for (int i = 0; i < maxVertices; i++)
		{
			plane::Plane auxPlane = plane::Plane(vertices[i], vertices[i+1], vertices[i+2]);

			planes.push_back(auxPlane);
			maxPlanes++;
		}
	}

	void BoundingBox::updateValues(std::vector <Vector3>& figureVertices, int figureMaxVert)
	{
		Vector3 minAux = { INT_MAX,INT_MAX,INT_MAX };
		Vector3 maxAux = { INT_MIN,INT_MIN,INT_MIN };

		for (int i = 0; i < figureMaxVert; i++)
		{
			minAux.x = fminf(minAux.x, figureVertices[i].x);
			minAux.y = fminf(minAux.y, figureVertices[i].y);
			minAux.z = fminf(minAux.z, figureVertices[i].z);

			maxAux.x = fmaxf(maxAux.x, figureVertices[i].x);
			maxAux.y = fmaxf(maxAux.y, figureVertices[i].y);
			maxAux.z = fmaxf(maxAux.z, figureVertices[i].z);
		}

		min = minAux;
		max = maxAux;

		vertices[0] = min;
		vertices[1] = min + Vector3{ 0.0f,0.0f,max.z - min.z };
		vertices[2] = max - Vector3{ 0.0f,max.y - min.y,0.0f };
		vertices[3] = min + Vector3{ max.x - min.x,0.0f,0.0f };
		vertices[4] = min + Vector3{ 0.0f,max.y - min.y,0.0f };
		vertices[5] = max - Vector3{ max.x - min.x,0.0f,0.0f };
		vertices[6] = max;
		vertices[7] = max - Vector3{ 0.0f,0.0f, max.z - min.z };
	}

	bool BoundingBox::isPointCol(Vector3 point)
	{
		bool isInside = true;

		for (int i = 0; i < maxPlanes; i++)
		{
			Vector3 diff = point - planes[i].pos;

			if (Vector3DotProduct(diff, planes[i].norm) >= 0)
			{
				return false;
			}
		}

		return isInside;
	}

	void BoundingBox::draw()
	{
		DrawLine3D(vertices[0], vertices[1], color);
		DrawLine3D(vertices[1], vertices[2], color);
		DrawLine3D(vertices[2], vertices[3], color);
		DrawLine3D(vertices[3], vertices[0], color);
		DrawLine3D(vertices[4], vertices[5], color);
		DrawLine3D(vertices[5], vertices[6], color);
		DrawLine3D(vertices[6], vertices[7], color);
		DrawLine3D(vertices[7], vertices[4], color);
		DrawLine3D(vertices[4], vertices[0], color);
		DrawLine3D(vertices[5], vertices[1], color);
		DrawLine3D(vertices[6], vertices[2], color);
		DrawLine3D(vertices[7], vertices[3], color);
	}
}

