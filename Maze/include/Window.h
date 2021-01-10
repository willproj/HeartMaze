#pragma once
#include "Common.h"


namespace maze
{
	class Window
	{
	public:
		static Window& Get();
		~Window();

		void Clear() const;
		bool Closed(); 

		void Update();

		const int32_t GetWindowWidth() const { return s_WindowWidth; }
		const int32_t GetWindowHeight() const { return s_WindowHeight; }

		const float GetAspect() const { return static_cast<float>(s_WindowWidth) / static_cast<float>(s_WindowHeight); }
		GLFWwindow* GetWinPtr() { return m_Window; }

		void SetPlayerKeyCallback(void (*f)(GLFWwindow* window, int key, int scancode, int action, int mods));

	private:
		Window();
		static Window s_Instance;
		static int32_t s_WindowWidth, s_WindowHeight;
		GLFWwindow* m_Window;
		bool InitWindow();
	};
}