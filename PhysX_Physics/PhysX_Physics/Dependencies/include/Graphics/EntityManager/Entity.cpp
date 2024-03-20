#include "Entity.h"
#include "EntityManager.h"
#include "../Panels/EditorLayout.h"

#include "../Panels/ImguiDrawUtils.h"

std::function<void(Entity*)> Entity::OnLayerDraw = nullptr;

void Entity::InitializeEntity(Entity* entity)
{
	EntityManager::GetInstance().AddEntity(entity);
}

void Entity::OnSceneDraw()
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	node_flags |= ImGuiTreeNodeFlags_SpanFullWidth;
	node_flags |= ImGuiTreeNodeFlags_Leaf;

	if (isSelected)
	{
		node_flags |= ImGuiTreeNodeFlags_Selected;
	}

	bool node_open = ImGui::TreeNodeEx(name.c_str(), node_flags);

	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
	{
		EditorLayout::GetInstance().SetSelectedObjects({ this });
	}
}

void Entity::OnPropertyDraw()
{
	ImGui::InputText("##ObjectName", &name[0], 516);

	ImGui::InputText("##Tag", &tag[0], 516);
	ImGui::SameLine();

	if (OnLayerDraw == nullptr)
	{
		if (ImGuiUtils::DrawInt("Layer", layer, false))
		{
			OnLayerChanged();
		}
	}
	else
	{
		OnLayerDraw(this);
	}
	//ImGuiUtils::DrawDropDown("Layer", layer, Layer::LayerStrings, Layer::LayerCount, false);

	transform.OnPropertyDraw();
}

void Entity::Destroy()
{
	EntityManager::GetInstance().RemoveEntity(entityId);
}

