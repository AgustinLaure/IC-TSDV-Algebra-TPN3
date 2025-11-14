#include "Figure.h"

#include <vector>

#include "raymath.h"

const float cameraSpeed = 25.0f;

void cameraMove(Camera3D& camera, bool& isCursorOn, float delta);
void drawWorldLines(Vector3 origin);
void figuresUpdate(std::vector<figure::Figure*> figures, int maxFigures, bool isCursorOn, float delta);
void figuresDraw(std::vector<figure::Figure*> figures);
void deinitFigures(std::vector<figure::Figure*> figures);

void main()
{
	InitWindow(1280, 720, "TP_03");

	std::vector<figure::Figure*> figures;
	int maxFigures = 0;
	
	figure::Figure* cube = new figure::Figure("res/figures/cube.obj", {2,2,2}, {1,0,0}, WHITE, {0,0,0}, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	figures.push_back(cube);
	maxFigures++;

	//figure::Figure* deca = new figure::Figure("res/figures/decahedron.obj", { 2,2,2 }, { 6,0,0 }, WHITE, { 0,0,0 }, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	//figures.push_back(deca);
	//maxFigures++;
	//
	//figure::Figure* dode = new figure::Figure("res/figures/dodecahedron.obj", { 2,2,2 }, { 12,0,0 }, WHITE, { 0,0,0 }, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	//figures.push_back(dode);
	//maxFigures++;
	//
	//figure::Figure* ico = new figure::Figure("res/figures/icosahedron.obj", { 2,2,2 }, {18,0,0 }, WHITE, { 0,0,0 }, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	//figures.push_back(ico);
	//maxFigures++;
	//
	//figure::Figure* octa = new figure::Figure("res/figures/octahedron.obj", { 2,2,2 }, { 24,0,0 }, WHITE, { 0,0,0 }, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	//figures.push_back(octa);
	//maxFigures++;
	//
	//figure::Figure* tetra = new figure::Figure("res/figures/tetrahedron.obj", { 2,2,2 }, { 30,0,0 }, WHITE, { 0,0,0 }, 0.05f * RAD2DEG, 10.0f, 0.0005f);
	//figures.push_back(tetra);
	//maxFigures++;

	Vector3 origin = { 0,0,0 };
	Camera3D camera = { 0 };
	const float cameraDistance = 20.0f;
	const float rotationAngle = 0.05f;
	camera.position = { cameraDistance, cameraDistance, cameraDistance };  // Camera position
	camera.target = origin;						// Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	DisableCursor();
	bool isCursorOn = false;

	float delta = 0.0f;

	while (!WindowShouldClose())
	{
		//Update
		delta = GetFrameTime();
		figuresUpdate(figures, maxFigures, isCursorOn, delta);
		cameraMove(camera, isCursorOn, delta);

		//
		
		//Draw
		BeginDrawing();
		BeginMode3D(camera);
		ClearBackground(BLACK);

		drawWorldLines(origin);
		figuresDraw(figures);
		
		EndMode3D();
		EndDrawing();
	}

	deinitFigures(figures);

	CloseWindow();
}

void cameraMove(Camera3D& camera, bool& isCursorOn, float delta)
{
	if (IsKeyPressed(KEY_TAB))
	{
		isCursorOn = !isCursorOn;

		if (isCursorOn)
		{
			EnableCursor();
		}
		else
		{
			DisableCursor();
		}
	}

	if (!isCursorOn)
	{
		UpdateCamera(&camera, CAMERA_FREE);
	}
}

void drawWorldLines(Vector3 origin)
{
	DrawGrid(100, 5);
	DrawLine3D(origin, { 10,0,0 }, RED);
	DrawLine3D(origin, { 0,10,0 }, GREEN);
	DrawLine3D(origin, { 0,0,10 }, BLUE);
}

void figuresUpdate(std::vector<figure::Figure*> figures, int maxFigures, bool isCursorOn, float delta)
{
	if (IsKeyPressed(KEY_ONE))
	{
		if (!figures[0]->getIsSelected())
		{
			figures[0]->select();
		}
		else
		{
			figures[0]->deselect();
		}
	}

	if (IsKeyPressed(KEY_TWO))
	{
		if (!figures[1]->getIsSelected())
		{
			figures[1]->select();
		}
		else
		{
			figures[1]->deselect();
		}
	}

	if (IsKeyPressed(KEY_THREE))
	{
		if (!figures[2]->getIsSelected())
		{
			figures[2]->select();
		}
		else
		{
			figures[2]->deselect();
		}
	}

	if (IsKeyPressed(KEY_FOUR))
	{
		if (!figures[3]->getIsSelected())
		{
			figures[3]->select();
		}
		else
		{
			figures[3]->deselect();
		}
	}

	if (IsKeyPressed(KEY_FIVE))
	{
		if (!figures[4]->getIsSelected())
		{
			figures[4]->select();
		}
		else
		{
			figures[4]->deselect();
		}
	}

	if (IsKeyPressed(KEY_SIX))
	{
		if (!figures[5]->getIsSelected())
		{
			figures[5]->select();
		}
		else
		{
			figures[5]->deselect();
		}
	}

	for (int i = 0; i < maxFigures; i++)
	{
		figures[i]->modifyTrsValues(delta);
	}

	for (int i = 0; i < maxFigures; i++)
	{
		figures[i]->update(figures, maxFigures);
	}
}

void figuresDraw(std::vector<figure::Figure*> figures)
{
	for (int i = 0; i < figures.size(); i++)
	{
		figures[i]->draw();
	}
}

void deinitFigures(std::vector<figure::Figure*> figures)
{
	int figuresSize = figures.size();

	for (int i = 0; i < figuresSize; i++)
	{
		delete figures[i];
		figures[i] = nullptr;
	}
}