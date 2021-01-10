#include "renderer/Shader.h"

namespace maze::renderer
{
	Shader::~Shader()
	{

	}

	Shader::Shader(const std::string& vfile, const std::string& ffile)
		:m_VFilePath(vfile), m_FFilePath(ffile), m_ShaderProgram(0)
	{
		auto [vertexSource, fragmentSource] = GetShaderSource();
		m_ShaderProgram = CreateShaderProgram(vertexSource, fragmentSource);
	}

	std::tuple<std::string, std::string> Shader::GetShaderSource()
	{
		return {
			ReadFile(m_VFilePath),
			ReadFile(m_FFilePath)
		};
	}


	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderProgram, name.c_str()), (GLint)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderProgram, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ShaderProgram, name.c_str()), value);
	}

	void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_ShaderProgram, name.c_str()), x, y);
	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_ShaderProgram, name.c_str()), x, y, z);
	}

	void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_ShaderProgram, name.c_str()), x, y, z, w);
	}

	void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::BindShaderProgram()const
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::UnbindShaderProgram()const
	{
		glUseProgram(0);
	}

	GLuint Shader::CreateShader(const std::string& file, int type)
	{
		GLuint shader = glCreateShader(type);
		const char* shader_src = file.c_str();
		glShaderSource(shader, 1, &shader_src, NULL);
		glCompileShader(shader);
		CheckShaderError("shader", shader);
		return shader;
	}

	GLuint& Shader::CreateShaderProgram(const std::string& vertexsource, const std::string& fragmentsource)
	{
		GLuint vertexShader = CreateShader(vertexsource, GL_VERTEX_SHADER);
		GLuint fragmentShader = CreateShader(fragmentsource, GL_FRAGMENT_SHADER);
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);
		CheckShaderError("program", m_ShaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return m_ShaderProgram;
	}


	void Shader::CheckShaderError(const std::string& name, GLuint shader)
	{
		if (name == "program")
		{
			int success;
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				char infoLog[1024];
				glGetProgramInfoLog(m_ShaderProgram, 1024, NULL, infoLog);
				std::cout << "Error:" << "program:" << infoLog << std::endl;
			}
			else std::cout << "Shader program created successfully!" << std::endl;
		}
		else
		{
			int success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[1024];
				glGetShaderInfoLog(m_ShaderProgram, 1024, NULL, infoLog);
				std::cout << "Error:" << "program:" << infoLog << std::endl;
			}
			else std::cout << "Shader created successfully!" << std::endl;
		}
	}
}