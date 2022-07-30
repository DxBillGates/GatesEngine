#include "..\..\Header\GUI\Hierarchy.h"
#include "..\..\Header\GUI\GUIManager.h"

bool GE::GUI::Hierarchy::OnGui(GameObject* gameObject)
{
	bool isInputButton = false;
	ImGui::Begin("Hierarchy");
	isInputButton = ImGui::Button(gameObject->GetName().c_str());
	ImGui::End();

	return isInputButton;
}
