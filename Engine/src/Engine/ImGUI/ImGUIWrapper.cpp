#include "ENPH.h"
#include "ImGUIWrapper.h"
#include "imgui.h"

namespace Engine
{
	void ImGUI::Begin(const char* name, bool* p_open)
	{
		ImGui::Begin(name, p_open);
	}

	void ImGUI::ColorEdit3(const char* label, float col[3])
	{
		ImGui::ColorEdit3(label, col);
	}

	void ImGUI::End()
	{
		ImGui::End();
	}
}