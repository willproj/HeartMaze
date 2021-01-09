#pragma once
#include "Common.h"
#include "renderer/shader.h"

namespace maze
{
	class Player
	{
	private:
		std::shared_ptr<renderer::Shader> m_PlayerShader;
		static int32_t m_PosX, m_PosY;

		static glm::mat4 m_ModelMatrix;
	public:
		Player();
		~Player();

		void DrawPlayer(const glm::mat4& view, const glm::mat4& projection, std::function<void()> func);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	private:
		static void TranslateModel(int& key);

	};
}