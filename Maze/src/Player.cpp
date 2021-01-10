#include "Player.h"
#include "Camera.h"

namespace maze
{
	int32_t Player::m_PosX = -22;
	int32_t Player::m_PosY = 7;

	glm::mat4 Player::m_ModelMatrix = glm::mat4(1.0f);

	std::shared_ptr<Maze> Player::m_Maze;

	Player::Player()
	{
		m_PlayerShader = std::shared_ptr<renderer::Shader>(new renderer::Shader("shader/vertexShader.vert", "shader/fragmentShader.frag"));
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(m_PosX, m_PosY, 0.0f));
	}

	Player::~Player()
	{

	}

	void Player::GetMazeInfo(std::shared_ptr<Maze> maze)
	{
		m_Maze = maze;
	}


	void Player::DrawPlayer(const glm::mat4& view, const glm::mat4& projection,std::function<void()> func)
	{
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
		auto& wallCoords = m_Maze->GetWallCoordMapRef();
		auto& cam = Camera::Get();

		if (key == GLFW_KEY_W)
		{
			auto wall = wallCoords.find({ m_PosX,m_PosY + 1 });
			if (wall == wallCoords.end() || (wall != wallCoords.end() && wall->second == NOT_WALL))
			{
				Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(0.0f, 1.0f, 0.0f));
				Player::m_PosY++;
				cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(0.0f, -1.0f, 0.0f));
				std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;
						
			}
			
		}
		if (key == GLFW_KEY_S)
		{
			auto wall = wallCoords.find({ m_PosX,m_PosY - 1 });
			if (wall == wallCoords.end() || (wall != wallCoords.end() && wall->second == NOT_WALL))
			{
				m_PosY--;
				Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
				cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(0.0f, 1.0f, 0.0f));
				std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;
			}
		}
		if (key == GLFW_KEY_A)
		{
			auto wall = wallCoords.find({ m_PosX-1,m_PosY });
			if (wall == wallCoords.end() || (wall != wallCoords.end() && wall->second == NOT_WALL))
			{ 
				
				m_PosX--;
				Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(-1.0f, 0.0f, 0.0f));
				cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(1.0f, 0.0f, 0.0f));
				std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;
				
				
			}
		}
		if (key == GLFW_KEY_D)
		{
			auto wall = wallCoords.find({ m_PosX + 1,m_PosY });
			if (wall == wallCoords.end() || (wall != wallCoords.end() && wall->second == NOT_WALL))
			{
				m_PosX++;
				Player::m_ModelMatrix = glm::translate(Player::m_ModelMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
				cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(-1.0f, 0.0f, 0.0f));
				std::cout << "pos:" << Player::m_PosX << " " << Player::m_PosY << std::endl;
				
			}
		}

		if (key == GLFW_KEY_UP)
		{
			cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(0, 0, 1));
		}
		else if (key == GLFW_KEY_DOWN)
		{
			cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(0, 0, -1));

		}
	}

}