#include <raylib.h>
#include <raymath.h>

void main()
{
	InitWindow(1280, 720, "Ejemplo");

	Vector3 origin = { 0,0,0 };

	Camera3D camera = { 0 };

	const float cameraDistance = 20.0f;
	const float rotationAngle = 0.05f;

	camera.position = { cameraDistance, cameraDistance, cameraDistance };  // Camera position
	camera.target = origin;      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	while (!WindowShouldClose())
	{
		BeginDrawing();

		BeginMode3D(camera);

		EndMode3D();

		ClearBackground(BLACK);
		EndDrawing();
	}
	CloseWindow();
}