#include "Application.h"

namespace maze
{

	Application::Application()
		:m_Win(Window::Get())
	{
		m_Shader = std::shared_ptr<renderer::Shader>(new renderer::Shader("shader/vertexShader.vert", "shader/fragmentShader.frag"));
		m_Maze = std::shared_ptr<Maze>(new Maze());
		m_Win.SetPlayerKeyCallback(Player::KeyCallback);
		player.GetMazeInfo(m_Maze);


		m_TexWall = renderer::Texture::CreateTexture("resources/rose1.png");
		m_TexLand = renderer::Texture::CreateTexture("resources/grass.jpg");
		m_TexPlayer = renderer::Texture::CreateTexture("resources/player.png");
		m_TexRock = renderer::Texture::CreateTexture("resources/stone.png");

	}

	void Application::Run()
	{
		glm::mat4 model = glm::mat4(1.0f);

		m_Shader->SetInt("u_texture", 0);

		
		auto& cam = Camera::Get();
		cam.GetViewMatrixRef() = glm::translate(cam.GetViewMatrixRef(), glm::vec3(-player.GetPosX(), -player.GetPosY(), -20.0f));
		

		while (m_Win.Closed())
		{
			m_Win.Clear();
			
			//player
			renderer::Texture::BindTexture(0, m_TexPlayer);
			player.DrawPlayer(cam.GetViewMatrixRef(), cam.GetProjectMatrixRef(), [=]() {m_Quad.Draw(); });

			//set up shader
			cam.GetProjectMatrixRef() = glm::perspective(glm::radians(45.0f), m_Win.GetAspect(), 0.1f, 100.0f);
			m_Shader->BindShaderProgram();
			m_Shader->SetMat4("u_projection", cam.GetProjectMatrixRef());
			m_Shader->SetMat4("u_view", cam.GetViewMatrixRef());
		

			//rock wall
			for (int i = -30; i <= 30; i++)
			{
				model = glm::mat4(1.0f);
				renderer::Texture::BindTexture(0, m_TexRock);
				model = glm::translate(model, glm::vec3(i, -17.0f, 0.0f));
				m_Shader->SetMat4("u_model", model);
				m_Quad.Draw();
			}

			for (int i = -30; i <= 30; i++)
			{
				model = glm::mat4(1.0f);
				renderer::Texture::BindTexture(0, m_TexRock);
				model = glm::translate(model, glm::vec3(i, 23.0f, 0.0f));
				m_Shader->SetMat4("u_model", model);
				m_Quad.Draw();
			}

			for (int i = -17; i <= 23; i++)
			{
				model = glm::mat4(1.0f);
				renderer::Texture::BindTexture(0, m_TexRock);
				model = glm::translate(model, glm::vec3(-30, i, 0.0f));
				m_Shader->SetMat4("u_model", model);
				m_Quad.Draw();
			}

			for (int i = -17; i <= 23; i++)
			{
				model = glm::mat4(1.0f);
				renderer::Texture::BindTexture(0, m_TexRock);
				model = glm::translate(model, glm::vec3(30, i, 0.0f));
				m_Shader->SetMat4("u_model", model);
				m_Quad.Draw();
			}



			//render wall
			auto& wall = m_Maze->GetWallCoordMapRef();
			for (auto it = wall.begin(); it != wall.end(); it++)
			{
				if (it->second == WALL)
				{
					renderer::Texture::BindTexture(0, m_TexWall);
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(it->first.first, it->first.second, 0.0f));
					m_Shader->SetMat4("u_model", model);
					m_Quad.Draw();
				}
			}


		

			//render land
			for (int i = -18; i <= 18; i++ )
			{
				for (int j = -18; j <= 18; j++)
				{
					model = glm::mat4(1.0f);
					model = glm::scale(model, glm::vec3(5.0f));
					renderer::Texture::BindTexture(0, m_TexLand);
					model = glm::translate(model, glm::vec3(i, j, 0.0f));
					m_Shader->SetMat4("u_model", model);
					m_Quad.Draw();

				}
				
			}
			

			m_Win.Update();
		}
	}

}