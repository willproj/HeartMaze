#pragma once
#include "include/Window.h"
#include "include/renderer/RenderQuad.h"
#include "Maze.h"
#include "include/Player.h"


namespace maze
{

	class Application
	{
	public:
		Application();
		void Run();
		std::shared_ptr<Maze> m_Maze;
		Player player;
		
	private:
		Window& m_Win;
		renderer::Quad m_Quad;

		std::shared_ptr<renderer::Shader> m_WallShader;
	};
}