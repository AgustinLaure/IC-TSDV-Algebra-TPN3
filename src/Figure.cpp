#include "Figure.h"

#include "raymath.h"

namespace figure
{
	Figure::Figure(std::string name, std::string modelRef, Vector3 scale, Vector3 pos, Color color, Vector3 rotationAxis, float rotationAngle, float speed, float expandSpeed) : name(name), scale(scale), pos(pos), color(color), rotationAngle(rotationAngle), speed(speed), expandSpeed(speed), isSelected(false)
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
		isCollidingBoundingBox = false;
	}
	Figure::~Figure()
	{
		UnloadModel(model);
	}

	void Figure::initPositions()
	{
		model.transform = MatrixMultiply(MatrixMultiply(scaleM, rotationM), translateM);

		initVertices();
		boundingBox.init(vertices, maxVertices);
		setPlanes();
	}

	void Figure::updatePositions()
	{
		model.transform = MatrixMultiply(MatrixMultiply(scaleM, rotationM), translateM);

		updateVertices();
		boundingBox.updateValues(vertices, maxVertices);
		updatePlanes();
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

	void Figure::setPlanes()
	{
		for (int i = 0; i < model.meshes[0].triangleCount; i++)
		{
			plane::Plane auxPlane = plane::Plane(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);

			//Vector3 center = pos - auxPlane.pos;
			//
			//if (Vector3DotProduct(auxPlane.norm, center) < 0)
			//{
			//	auxPlane.norm *= -1;
			//}

			planes.push_back(auxPlane);
			maxPlanes++;
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

	void Figure::updatePlanes()
	{
		for (int i = 0; i < model.meshes[0].triangleCount; i++)
		{
			plane::Plane auxPlane = plane::Plane(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);

			//Vector3 center = Vector3Transform(pos, translateM) - auxPlane.pos;
			//
			//if (Vector3DotProduct(auxPlane.norm, center) < 0)
			//{
			//	auxPlane.norm *= -1;
			//}

			planes[i] = auxPlane;
		}
	}

	bool Figure::isPointCol(Vector3 point)
	{
		bool isInside = true;

		for (int i = 0; i < maxPlanes; i++)
		{
			isInside = true;

			Vector3 diff = point - planes[i].pos;

			if (Vector3DotProduct(diff, planes[i].norm) < 0)
			{
				isInside = false;
				break;
			}
		}

		return isInside;
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

		boundingBox.draw();

		//DrawTriangle3D(boundingBox.vertices[0], boundingBox.vertices[1], boundingBox.vertices[2], GREEN);
		//
		//DrawLine3D(boundingBox.planes[0].pos, boundingBox.planes[0].pos + Vector3Scale(boundingBox.planes[0].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[1].pos, boundingBox.planes[1].pos + Vector3Scale(boundingBox.planes[1].norm, 1.0f), RED);
		//
		//DrawLine3D(boundingBox.planes[2].pos, boundingBox.planes[2].pos + Vector3Scale(boundingBox.planes[2].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[3].pos, boundingBox.planes[3].pos + Vector3Scale(boundingBox.planes[3].norm, 1.0f), RED);
		//
		//DrawLine3D(boundingBox.planes[4].pos, boundingBox.planes[4].pos + Vector3Scale(boundingBox.planes[4].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[5].pos, boundingBox.planes[5].pos + Vector3Scale(boundingBox.planes[5].norm, 1.0f), RED);
		//
		//DrawLine3D(boundingBox.planes[6].pos, boundingBox.planes[6].pos + Vector3Scale(boundingBox.planes[6].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[7].pos, boundingBox.planes[7].pos + Vector3Scale(boundingBox.planes[7].norm, 1.0f), RED);
		//
		//DrawLine3D(boundingBox.planes[8].pos, boundingBox.planes[8].pos + Vector3Scale(boundingBox.planes[8].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[9].pos, boundingBox.planes[9].pos + Vector3Scale(boundingBox.planes[9].norm, 1.0f), RED);
		//
		//DrawLine3D(boundingBox.planes[10].pos, boundingBox.planes[10].pos + Vector3Scale(boundingBox.planes[10].norm, 1.0f), RED);
		//DrawLine3D(boundingBox.planes[11].pos, boundingBox.planes[11].pos + Vector3Scale(boundingBox.planes[11].norm, 1.0f), RED);

		for (int i = 0; i < maxPlanes; i++)
		{
			DrawLine3D(planes[i].pos, planes[i].pos + Vector3Scale(planes[i].norm, 1.0f), RED);
		}


		for (int i = 0; i < boundingBox.planes.size(); i++)
		{
			//DrawLine3D(boundingBox.planes[i].pos, boundingBox.planes[i].pos + Vector3Scale(boundingBox.planes[i].norm, 1.0f), RED);
		}

		DrawLine3D(pos, { 0.0f,0.0f,0.0f }, BROWN);
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
