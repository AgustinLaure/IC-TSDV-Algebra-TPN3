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

		boundingBox::BoundingBox boundingBox;

		std::vector<Vector3> vertices;

	public:
		Figure(std::string modelRef, Vector3 scale, Vector3 pos, Color color, Vector3 rotationAxis, float rotationAngle, float speed, float expandSpeed);
		~Figure();

		void initPositions();
		void initVertices();
		void updatePositions();
		void updateVertices();
		void updateBoundingBox();
		void select();
		void deselect();
		bool getIsSelected();

		void draw();
		void rotate(float delta);
	};
}

