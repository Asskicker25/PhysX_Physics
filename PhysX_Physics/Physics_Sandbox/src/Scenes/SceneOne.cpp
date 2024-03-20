#include "SceneOne.h"
#include "../AppSettings.h"

#include "../Player.h"

#include <PhysX_Object.h>

#include <Shapes/SphereCollider.h>

void SceneOne::Start()
{
	GameCamera* mainCamera = new GameCamera();
	mainCamera->name = "MainCamera";
	mainCamera->InitializeCamera(PERSPECTIVE, GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT, 0.1f, 100.0f, 45.0f);
	mainCamera->transform.SetPosition(glm::vec3(0, 0, 10));
	mainCamera->applyPostProcessing = true;
	mainCamera->postProcessing->bloom.isEnabled = true;
	mainCamera->postProcessing->chromaticAberration.isEnabled = true;

	Light* dirLight = new Light();
	dirLight->transform.SetScale(glm::vec3(0.1f));
	dirLight->transform.SetRotation(glm::vec3(0, -100, -36));
	dirLight->InitializeLight(Directional);

	PhysX_Object* sphere = new PhysX_Object();
	sphere->LoadModel("res/Models/DefaultSphere.fbx");
	sphere->transform.SetPosition(glm::vec3(0.5f, 10, 0));
	sphere->transform.SetScale(glm::vec3(0.5f));
	sphere->Initialize(RigidBody::DYNAMIC, BaseColliderShape::SPHERE);
	sphere->mRigidBody.SetMass(10);
	sphere->name = "Sphere";
	sphere->mColliderShape->AsSphere()->SetRadius(2);

	PhysX_Object* plane = new PhysX_Object();
	plane->LoadModel("res/Models/DefaultCube.fbx");
	plane->transform.SetPosition(glm::vec3(0.0f, -0.15f, 0));
	plane->transform.SetScale(glm::vec3(20, 0.1f, 20));
	plane->Initialize(RigidBody::STATIC, BaseColliderShape::BOX);
	plane->name = "Plane";

	/*PhysX_Object* sphere2 = new PhysX_Object();
	sphere2->CopyFromModel(*sphere,true);
	sphere2->transform.SetPosition(glm::vec3(0, 1, 0));
	sphere2->transform.SetScale(glm::vec3(1));
	sphere2->Initialize(RigidBody::STATIC, BaseColliderShape::SPHERE);*/

	Player* player = new Player();

}

void SceneOne::Update()
{
}

void SceneOne::Render()
{
	//meshInstance->DrawShaded(meshInstance->shader);
}
