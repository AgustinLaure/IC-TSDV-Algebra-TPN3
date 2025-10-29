#include <raylib.h>
#include <raymath.h>
#include <iostream>

const float cameraSpeed = 25.0f;

void cameraMove(Camera3D& camera, float delta);
Vector3 getVectorMult(Vector3 v, float mult);

struct Figure
{
	Model model;
	float scale;
	Vector3 pos;
	Color color;
};

void main()
{
	InitWindow(1280, 720, "Ejemplo");

	Figure cube;
	cube.model = LoadModel("res/figures/cube.obj");
	cube.scale = 1;
	cube.pos = { 0,0,0 };
	cube.color = WHITE;
	

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

	float delta = 0.0f;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		//Update
		delta = GetFrameTime();

		cameraMove(camera, delta);
		//Draw
		BeginDrawing();
		BeginMode3D(camera);
		ClearBackground(BLACK);

		DrawModel(cube.model, cube.pos, cube.scale, cube.color);

		//Draw Axis
		DrawGrid(100,5);
		DrawLine3D(origin, { 10,0,0 }, RED);
		DrawLine3D(origin, { 0,10,0 }, GREEN);
		DrawLine3D(origin, { 0,0,10 }, BLUE);

		EndMode3D();
		EndDrawing();
	}
	
	UnloadModel(cube.model);
	CloseWindow();
}

void cameraMove(Camera3D& camera, float delta)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector3 lookingDir = Vector3Normalize(camera.target - camera.position);

		UpdateCamera(&camera, CAMERA_FREE);
	}

}

Vector3 getVectorMult(Vector3 v, float mult)
{
	return { v.x * mult,v.y * mult,v.z * mult };
}