#pragma once
#include "Window.h"
#include "renderer/Texture.h"
#include "renderer/RenderQuad.h"
#include "Maze.h"
#include "Player.h"
#include "Camera.h"


namespace maze
{

	class Application
	{
	public:
		Application();
		void Run();
		
	private:
		std::shared_ptr<Maze> m_Maze;
		Player player;
		Window& m_Win;

		GLuint m_TexWall;
		GLuint m_TexLand;
		GLuint m_TexPlayer;
		GLuint m_TexRock;

	

		renderer::Quad m_Quad;

		std::shared_ptr<renderer::Shader> m_Shader;
	};
}