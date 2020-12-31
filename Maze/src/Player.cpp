#include "Player.h"

namespace maze
{
	Player::Player()
	{
		m_PlayerShader = std::shared_ptr<renderer::Shader>(new renderer::Shader("shader/vertexShader.vert", "shader/player.frag"));
	}

	Player::~Player()
	{

	}


	void Player::DrawPlayer(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection,std::function<void()> func)
	{
		m_PlayerShader->BindShaderProgram();
		m_PlayerShader->BindShaderProgram();
		m_PlayerShader->SetMat4("u_projection", projection);
		m_PlayerShader->SetMat4("u_view", view);
		m_PlayerShader->SetMat4("u_model", model);
		func();
		m_PlayerShader->UnbindShaderProgram();
	}

	void Player::processInput(glm::mat4& model,GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));

			std::cout << "up" << std::endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));

			std::cout << "down" << std::endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));

			std::cout << "left" << std::endl;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
			std::cout << "right" << std::endl;
		}
	}

}