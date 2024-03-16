#include "PhysicsApplication.h"

#include <Graphics/Scene/SceneManager.h>

#include "Scenes/SceneOne.h"

using namespace Scene;

void PhysicsApplication::SetUp()
{
	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);
	viewportCamera->transform.SetPosition(glm::vec3(0, 0, 10));
	viewportCamera->applyPostProcessing = true;

	BaseScene* sceneOne = new SceneOne();

	SceneManager::GetInstance().AddScene("SceneOne", sceneOne);

	SceneManager::GetInstance().ChangeScene("SceneOne");

}

void PhysicsApplication::Update()
{
}

void PhysicsApplication::Render()
{
}

void PhysicsApplication::Shutdown()
{
}

void PhysicsApplication::OnPlayStateChanged(bool state)
{
}

void PhysicsApplication::ProcessInput(GLFWwindow* window)
{
}

void PhysicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void PhysicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
