#include "Figure.h"
#include "raymath.h"

const float cameraSpeed = 25.0f;

void cameraMove(Camera3D& camera, bool& isCursorOn, float delta);

void main()
{
	InitWindow(1280, 720, "TP_03");

	figure::Figure cube = figure::Figure("res/figures/cube.obj", 1, { 0,0,0 }, WHITE);

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

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update
		delta = GetFrameTime();

		cameraMove(camera, isCursorOn, delta);
		//Drawz
		BeginDrawing();
		BeginMode3D(camera);
		ClearBackground(BLACK);

		cube.draw();

		//Draw Axis
		DrawGrid(100, 5);
		DrawLine3D(origin, { 10,0,0 }, RED);
		DrawLine3D(origin, { 0,10,0 }, GREEN);
		DrawLine3D(origin, { 0,0,10 }, BLUE);

		EndMode3D();
		EndDrawing();
	}

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