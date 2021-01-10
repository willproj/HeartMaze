#pragma once
#include "Common.h"

namespace maze::renderer
{
	class Quad
	{
	public:
		void Draw();
		Quad();
		~Quad() {}

	private:
		
		void Create();
		int32_t vertexShader, fragmentShader;
		size_t VBO, VAO, EBO;

		std::vector<float> m_Vertices = {
			0.6f,  0.6f, 0.0f,  1.0f,1.0f,// top right    
			0.6f, -0.6f, 0.0f,  1.0f,0.0f,// bottom right
			-0.6f, -0.6f, 0.0f,  0.0f,0.0f,// bottom left
			-0.6f,  0.6f, 0.0f,   0.0f,1.0f// top left 
		};

		std::vector<size_t> m_Indices = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
	};
}