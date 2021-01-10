#include "Window.h"

namespace maze
{
	int32_t Window::s_WindowWidth = 1600;
	int32_t Window::s_WindowHeight = 900;
	Window Window::s_Instance;

	Window::Window()
		:m_Window(nullptr)
	{
		if (!InitWindow())
		{
			std::cout << "failed to create window" << std::endl;
		}
	}

	Window::~Window()
	{

	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	}

	bool Window::Closed()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	Window& Window::Get()
	{
		return s_Instance;
	}

	void Window::SetPlayerKeyCallback(void (*f)(GLFWwindow* window,int key,int scancode,int action,int mods))
	{
		glfwSetKeyCallback(m_Window, f);
	}

	bool Window::InitWindow()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(s_WindowWidth, s_WindowHeight, "maze", nullptr, nullptr);
		if (!m_Window)
		{
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			glViewport(0, 0, width, height);
		});
	

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		return true;
	}

}