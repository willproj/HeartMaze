#pragma once
#include "Common.h"

namespace maze
{
	class Camera
	{
	private:
		Camera();
		glm::mat4 m_ModelMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectMatrix;

		static Camera s_Instance;
	public:
		static Camera& Get();
		~Camera();

		glm::mat4& GetModelMatrixRef() { return m_ModelMatrix; }
		glm::mat4& GetViewMatrixRef() { return m_ViewMatrix; }
		glm::mat4& GetProjectMatrixRef() { return m_ProjectMatrix; }
				 

	};
}