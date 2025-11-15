#pragma once

#include <iostream>
#include <vector>

#include "raylib.h"

#include "BoundingBox.h"

namespace figure
{
	class Figure
	{
	private:
		float speed;
		float expandSpeed;
		Model model;
		float rotationAngle;
		Color color;
		bool isSelected;

		Vector3 scale;
		Vector3 pos;

		Matrix translateM;
		Matrix rotationM;
		Matrix scaleM;

		bool isRotating;
		bool isTranslating;
		bool isScaling;

		std::vector<Vector3> vertices;
		int maxVertices;

	public:
		std::string name;

		bool isCollidingFigure;

		boundingBox::BoundingBox boundingBox;
		bool isCollidingBoundingBox;

		std::vector<plane::Plane> planes;
		int maxPlanes;

		Figure(std::string name, std::string modelRef, Vector3 scale, Vector3 pos, Color color, Vector3 rotationAxis, float rotationAngle, float speed, float expandSpeed);
		~Figure();

		void initPositions();
		void initVertices();
		void setPlanes();
		void updatePositions();
		void updateVertices();
		void updatePlanes();
		bool isPointCol(Vector3 point);
		void select();
		void deselect();
		bool getIsSelected();

		void draw();
		void modifyTrsValues(float delta);
	};
}

