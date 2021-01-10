#include "Camera.h"

namespace maze
{
	Camera Camera::s_Instance;

	Camera::Camera()
	{

	}

	Camera& Camera::Get()
	{
		return s_Instance;
	}
	
	Camera::~Camera()
	{

	}



}