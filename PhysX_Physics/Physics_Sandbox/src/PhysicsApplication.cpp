#include "PhysicsApplication.h"

#include <Graphics/Scene/SceneManager.h>
#include <Graphics/Panels/EditorLayout.h>

#include "Scenes/SceneOne.h"

using namespace Scene;

void PhysicsApplication::SetUp()
{
	PhysX_Engine::GetInstance().Initialize();

	viewportCamera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 100.0f, 45.0f);
	viewportCamera->transform.SetPosition(glm::vec3(-16, 10, 16));
	viewportCamera->transform.SetRotation(glm::vec3(-20, -47, 0));
	viewportCamera->applyPostProcessing = true;

	EditorLayout::GetInstance().SetMaximizeState(false);


	BaseScene* sceneOne = new SceneOne();

	SceneManager::GetInstance().AddScene("SceneOne", sceneOne);

	SceneManager::GetInstance().ChangeScene("SceneOne");

}

void PhysicsApplication::Update()
{
	if (applicationPlay)
	{
		PhysX_Engine::GetInstance().Update();
	}
}

void PhysicsApplication::Render()
{
}

void PhysicsApplication::Shutdown()
{
	PhysX_Engine::GetInstance().Cleanup();
}

void PhysicsApplication::OnPlayStateChanged(bool state)
{
	if (state)
	{
		PhysX_Engine::GetInstance().OnApplicationStart();
	}
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
