#pragma once

#include "../PhysicsApplication.h"
#include <Graphics/Scene/BaseScene.h>

using namespace Scene;

class SceneOne : public BaseScene
{
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

