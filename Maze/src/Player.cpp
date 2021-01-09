#include "Player.h"

namespace maze
{
	int32_t Player::m_PosX = 0;
	int32_t Player::m_PosY = 0;

	glm::mat4 Player::m_ModelMatrix = glm::mat4(1.0f);

	Player::Player()
	{
		m_PlayerShader = std::shared_ptr<renderer::Shader>(new renderer::Shader("shader/vertexShader.vert", "shader/player.frag"));
	}

	Player::~Player()
	{

	}


	void Player::DrawPlayer(const glm::mat4& view, const glm::mat4& projection,std::function<void()> func)
	{
		m_PlayerShader->BindShaderProgram();
		m_PlayerShader->BindShaderProgram();
		m_PlayerShader->SetMat4("u_projection", projection);
		m_PlayerShader->SetMat4("u_view", view);
		m_PlayerShader->SetMat4("u_model", m_ModelMatrix);
		func();
		m_PlayerShader->UnbindShaderProgram();
	}

	void Player::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			TranslateModel(key);
			break;
		case GLFW_RELEASE:
			break;
		case GLFW_REPEAT:
			TranslateModel(key);
			break;
		}
	}

	void Player::TranslateModel(int& key)
	{
		if (key == GLFW_KEY_UP)
		{
			Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(0.0f, 1.0f, 0.0f));
			Player::m_PosY++;
			std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;
		}
		else if (key == GLFW_KEY_DOWN)
		{
			Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
			Player::m_PosY--;
			std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;

		}
		else if (key == GLFW_KEY_LEFT)
		{
			Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(-1.0f, 0.0f, 0.0f));
			Player::m_PosX--;
			std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;

		}
		else if (key == GLFW_KEY_RIGHT)
		{
			Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
			Player::m_PosX++;
			std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;

		}
	}

}