#include "Common.h"



namespace maze::renderer
{
	static const std::string ReadFile(const std::string& filepath)
	{
		std::ifstream infile(filepath);
		if (infile)
		{
			std::stringstream strstream;
			strstream << infile.rdbuf();
			std::string result = strstream.str();
			return result;
		}
		return "";
	}


	class Shader
	{
	private:
		std::tuple<std::string, std::string> m_Source;
		GLuint m_ShaderProgram;
		std::string m_VFilePath;
		std::string m_FFilePath;
	public:
		Shader(const std::string& vfile, const std::string& ffile);
		~Shader();


		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec2(const std::string& name, const glm::vec2& value) const;
		void SetVec2(const std::string& name, float x, float y) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
		void SetVec4(const std::string& name, const glm::vec4& value) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;
		void SetMat2(const std::string& name, const glm::mat2& mat) const;
		void SetMat3(const std::string& name, const glm::mat3& mat) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;


		void BindShaderProgram() const;
		void UnbindShaderProgram()const;
	private:
		std::tuple<std::string, std::string> GetShaderSource();

		GLuint CreateShader(const std::string& file, int type);
		GLuint& CreateShaderProgram(const std::string& vertexshader, const std::string& fragmentshader);
		void CheckShaderError(const std::string& name, GLuint shader);
	};
}