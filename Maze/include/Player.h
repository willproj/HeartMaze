#pragma once
#include "Common.h"
#include "renderer/shader.h"
#include "Maze.h"

namespace maze
{
	class Player
	{
	private:
		std::shared_ptr<renderer::Shader> m_PlayerShader;
		static int32_t m_PosX, m_PosY;

		static glm::mat4 m_ModelMatrix;

		static std::shared_ptr<Maze> m_Maze;
	public:
		Player();
		~Player();


		int32_t GetPosX()const { return m_PosX; }
		int32_t GetPosY()const { return m_PosY; }
		void GetMazeInfo(std::shared_ptr<Maze> maze);
		void DrawPlayer(const glm::mat4& view, const glm::mat4& projection, std::function<void()> func);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	private:
		static void TranslateModel(int& key);

	};
}