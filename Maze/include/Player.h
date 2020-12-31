#pragma once
#include "Common.h"
#include "renderer/shader.h"

namespace maze
{
	class Player
	{
	private:
		std::shared_ptr<renderer::Shader> m_PlayerShader;

	public:
		Player();
		~Player();

		void DrawPlayer(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, std::function<void()> func);

		void processInput(glm::mat4& model, GLFWwindow* window);
	};
}