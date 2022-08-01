#include "..\..\Header\GUI\Inspector.h"
#include "..\..\Header\GUI\GUIManager.h"
#include "..\..\Header\GameFramework\Component\Component.h"

void GE::GUI::Inspector::SetCurrentSelectGameObject(GameObject* gameObject)
{
	currentSelectGameObject = gameObject;
}

void GE::GUI::Inspector::OnGui()
{
	ImGui::Begin("Inspector");

	if (currentSelectGameObject)
	{
		bool isEnabled = currentSelectGameObject->IsEnabled();
		if (ImGui::Checkbox("enabled", &isEnabled))
		{
			currentSelectGameObject->SetEnabled(isEnabled);
		}

		ImGui::Text("name : %s", currentSelectGameObject->GetName().c_str());
		ImGui::Text("tag : %s", currentSelectGameObject->GetTag().c_str());
		ImGui::Separator();

		ImGui::SetNextItemOpen(true, ImGuiCond_::ImGuiCond_Once);
		if (ImGui::TreeNode("Transform"))
		{
			float dragSpeed = 1;
			float dragMinValue = -100000;
			float drawMaxValue = 100000;

			ImGui::DragFloat3("Position", currentSelectGameObject->GetTransform()->position.value, dragSpeed, dragMinValue, drawMaxValue);
			ImGui::DragFloat3("Rotation", currentSelectGameObject->GetTransform()->rotation.value, dragSpeed, dragMinValue, drawMaxValue);
			ImGui::DragFloat3("Scale   ", currentSelectGameObject->GetTransform()->scale.value   , dragSpeed, dragMinValue, drawMaxValue);
			ImGui::TreePop();
		}

		auto components = currentSelectGameObject->GetComponents();
		for (auto& component : *components)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_::ImGuiCond_Once);
			if (component->IsOpenTreeNodeGui())
			{
				component->OnGui();
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}
