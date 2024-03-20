#pragma once

#define APP_WIDTH 1920
#define APP_HEIGHT 1080

#define GAME_RESOLUTION_WIDTH 1920
#define GAME_RESOLUTION_HEIGHT 1080

#define NORMALS_SIZE 0.5f

#define GIZMO_ICON_SIZE 0.1f

namespace Layer
{
	enum class Entity_Layer
	{
		DEFAULT = 0,
		RAYCAST = 1,
	};

	static const char* LayerStrings[2] = { "Default" , "Raycast" };
	static const int LayerCount = 2;
}
