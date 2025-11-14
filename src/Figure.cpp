#include "Figure.h"

#include "raymath.h"

namespace figure
{
	Figure::Figure(std::string modelRef, Vector3 scale, Vector3 pos, Color color, Vector3 rotationAxis, float rotationAngle, float speed, float expandSpeed) : scale(scale), pos(pos), color(color), rotationAngle(rotationAngle), speed(speed), expandSpeed(speed), isSelected(false)
	{
		maxVertices = 0;

		model = LoadModel(modelRef.c_str());

		translateM = MatrixTranslate(pos.x, pos.y, pos.z);
		rotationM = MatrixRotate(rotationAxis, rotationAngle);
		scaleM = MatrixScale(scale.x, scale.y, scale.z);

		initPositions();

		isRotating = false;
		isTranslating = false;
		isScaling = false;
	}
	Figure::~Figure()
	{
		UnloadModel(model);
	}

	void Figure::initPositions()
	{
		model.transform = MatrixMultiply(MatrixMultiply(scaleM, rotationM), translateM);

		initVertices();
		updateBoundingBox();
	}

	void Figure::updatePositions()
	{
		model.transform = MatrixMultiply(MatrixMultiply(scaleM, rotationM), translateM);

		updateVertices();
		updateBoundingBox();
	}

	void Figure::initVertices()
	{
		Vector3 vertex = { 0.0f,0.0f,0.0f };

		Mesh modelMesh = model.meshes[0];

		for (int i = 0; i < modelMesh.vertexCount; i++)
		{
			vertex.x = modelMesh.vertices[i * 3];
			vertex.y = modelMesh.vertices[i * 3 + 1];
			vertex.z = modelMesh.vertices[i * 3 + 2];

			vertex = Vector3Transform(vertex, model.transform);

			vertices.push_back(vertex);
			maxVertices++;
		}
	}

	void Figure::updateVertices()
	{
		Vector3 vertex = { 0.0f,0.0f,0.0f };

		Mesh modelMesh = model.meshes[0];

		for (int i = 0; i < modelMesh.vertexCount; i++)
		{
			vertex.x = modelMesh.vertices[i * 3];
			vertex.y = modelMesh.vertices[i * 3 + 1];
			vertex.z = modelMesh.vertices[i * 3 + 2];

			vertex = Vector3Transform(vertex, model.transform);

			vertices[i] = vertex;
		}
	}

	void Figure::updateBoundingBox()
	{
		Vector3 min = { INT_MAX,INT_MAX,INT_MAX };
		Vector3 max = { INT_MIN,INT_MIN,INT_MIN };

		for (int i = 0; i < maxVertices; i++)
		{
			min.x = fminf(min.x, vertices[i].x);
			min.y = fminf(min.y, vertices[i].y);
			min.z = fminf(min.z, vertices[i].z);

			max.x = fmaxf(max.x, vertices[i].x);
			max.y = fmaxf(max.y, vertices[i].y);
			max.z = fmaxf(max.z, vertices[i].z);
		}

		boundingBox.min = min;
		boundingBox.max = max;
	}

	void Figure::select()
	{
		isSelected = true;
		color = RED;
	}

	void Figure::deselect()
	{
		isSelected = false;
		color = WHITE;
	}

	bool Figure::getIsSelected() { return isSelected; }

	void Figure::draw()
	{
		DrawModel(model, { 0.0f,0.0f,0.f }, 1, color);

		for (int i = 0; i < vertices.size(); i++)
		{
			DrawPoint3D(vertices[i], GREEN);
		}
		boundingBox.draw();
	}

	void Figure::modifyTrsValues(float delta)
	{
		if (isSelected)
		{
			if (IsKeyPressed(KEY_T))
			{
				isTranslating = !isTranslating;

				if (isTranslating)
				{
					color = YELLOW;
				}
				else
				{
					color = WHITE;
				}
			}
			if (IsKeyPressed(KEY_R))
			{
				isRotating = !isRotating;

				if (isRotating)
				{
					color = PURPLE;
				}
				else
				{
					color = WHITE;
				}
			}
			if (IsKeyPressed(KEY_Z))
			{
				isScaling = !isScaling;

				if (isScaling)
				{
					color = BLUE;
				}
				else
				{
					color = WHITE;
				}
			}

			if (isTranslating)
			{
				Vector3 dir = { 0.0f,0.0f,0.0f };

				if (IsKeyDown(KEY_W))
				{
					dir.z = -1;
				}
				if (IsKeyDown(KEY_A))
				{
					dir.x = -1;
				}
				if (IsKeyDown(KEY_S))
				{
					dir.z = 1;
				}
				if (IsKeyDown(KEY_D))
				{
					dir.x = 1;
				}
				if (IsKeyDown(KEY_Q))
				{
					dir.y = 1;
				}
				if (IsKeyDown(KEY_E))
				{
					dir.y = -1;
				}

				dir = Vector3Normalize(dir);

				if (Vector3Length(dir) > 0.0f)
				{
					dir *= speed * delta;

					translateM = MatrixMultiply(translateM, MatrixTranslate(dir.x, dir.y, dir.z));

					updatePositions();
				}
			}
			else if (isRotating)
			{
				Vector3 rotationAxis = { 0.0f, 0.0f, 0.0f };

				if (IsKeyDown(KEY_W))
				{
					rotationAxis.x = -1;
				}
				if (IsKeyDown(KEY_A))
				{
					rotationAxis.y = -1;
				}
				if (IsKeyDown(KEY_S))
				{
					rotationAxis.x = 1;
				}
				if (IsKeyDown(KEY_D))
				{
					rotationAxis.y = 1;
				}
				if (IsKeyDown(KEY_Q))
				{
					rotationAxis.z = 1;
				}
				if (IsKeyDown(KEY_E))
				{
					rotationAxis.z = -1;
				}

				if (Vector3Length(rotationAxis) > 0.0f)
				{
					rotationAxis = Vector3Normalize(rotationAxis);

					rotationM = MatrixMultiply(MatrixRotate(rotationAxis, rotationAngle * delta), rotationM);

					updatePositions();
				}
			}

			else if (isScaling)
			{
				if (IsKeyDown(KEY_W))
				{
					if (scale.z + expandSpeed * delta > 0.0f)
					{
						scale.z += expandSpeed * delta;
					}
				}
				if (IsKeyDown(KEY_A))
				{
					if (scale.x + -expandSpeed * delta > 0.0f)
					{
						scale.x += -expandSpeed * delta;
					}
				}
				if (IsKeyDown(KEY_S))
				{
					if (scale.z + -expandSpeed * delta > 0.0f)
					{
						scale.z += -expandSpeed * delta;
					}
				}
				if (IsKeyDown(KEY_D))
				{
					if (scale.x + expandSpeed * delta > 0.0f)
					{
						scale.x += expandSpeed * delta;
					}
				}
				if (IsKeyDown(KEY_Q))
				{
					if (scale.y + -expandSpeed * delta > 0.0f)
					{
						scale.y += -expandSpeed * delta;
					}
				}
				if (IsKeyDown(KEY_E))
				{
					if (scale.y + expandSpeed * delta > 0.0f)
					{
						scale.y += expandSpeed * delta;
					}
				}

				scaleM = MatrixScale(scale.x, scale.y, scale.z);

				updatePositions();
			}
		}
	}
}
