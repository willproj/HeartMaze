#include "Application.h"


namespace maze
{

	Application::Application()
		:m_Win(Window::Get())
	{
		m_WallShader = std::shared_ptr<renderer::Shader>(new renderer::Shader("shader/vertexShader.vert", "shader/fragmentShader.frag"));
		m_Maze = std::shared_ptr<Maze>(new Maze());
		m_Win.SetPlayerKeyCallback(Player::KeyCallback);
		
	}

	void Application::Run()
	{

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, -3.0f, -50.0f));

		while (m_Win.Closed())
		{
			m_Win.Clear();
			m_WallShader->BindShaderProgram();

			projection = glm::perspective(glm::radians(45.0f), m_Win.GetAspect(), 0.1f, 100.0f);
			m_WallShader->SetMat4("u_projection", projection);
			m_WallShader->SetMat4("u_view", view);
			
			
			auto wall=m_Maze->GetWallCoordMap();
			for (auto it = wall.begin(); it != wall.end(); it++)
			{
				if (it->second == WALL)
				{
					model = glm::mat4(1.0f);
					model = glm::translate(model, glm::vec3(it->first.first, it->first.second, 0.0f));
					m_WallShader->SetMat4("u_model", model);
					m_Quad.Draw();
			
				}
			}


			//player
			player.DrawPlayer(view, projection, [=]() {m_Quad.Draw(); });
			




			m_Win.Update();
		}
	}

}