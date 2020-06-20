#pragma once

namespace Engine
{
	class ENGINE_API ImGUI
	{
	public:
		static void Begin(const char* name, bool* p_open = false); 
		static void ColorEdit3(const char* label, float col[3]); 
		static void End(); 
	};
}