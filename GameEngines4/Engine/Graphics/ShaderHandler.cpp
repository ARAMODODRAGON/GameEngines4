#include "ShaderHandler.h"
#include "../Core/Debug.h"

std::unique_ptr<ShaderHandler> ShaderHandler::Singleton = nullptr;

std::string ShaderHandler::ReadShader(const std::string& filename) {
	std::string shadercode = "";
	std::ifstream filestream;
	filestream.exceptions(std::ifstream::badbit);

	try {
		filestream.open(filename);
		std::stringstream tmpstream;
		tmpstream << filestream.rdbuf();
		filestream.close();
		shadercode = tmpstream.str();
		return shadercode;
	} catch (std::ifstream::failure e) {
		DEBUG_ERROR("Could not read the shader: " + filename);
		return "";
	}

}

GLuint ShaderHandler::CreateShader(GLenum shaderType, const std::string& source) {
	GLint compileresult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shadercodeptr = source.c_str();
	const int shadercodesize = source.size();

	glShaderSource(shader, 1, &shadercodeptr, &shadercodesize);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileresult);

	if (!compileresult) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::vector<char> log(infoLogLength);

		glGetShaderInfoLog(shader, infoLogLength, nullptr, &log[0]);

		std::string shaderstring(log.begin(), log.end());

		DEBUG_ERROR("Shader compilation error: " + shaderstring);

	}

	return shader;
}

ShaderHandler::ShaderHandler() {

}

ShaderHandler::~ShaderHandler() {

}

ShaderHandler* ShaderHandler::GetSingleton() {
	// check if instance exists
	if (Singleton.get() == nullptr) {
		Singleton.reset(new ShaderHandler());
	}

	// return singleton
	return Singleton.get();
}

void ShaderHandler::CreateProgram(const std::string& shadername, const std::string& vertfilename, const std::string& fragfilename) {
	if (programs.find(shadername) != programs.end()) return;

	std::string vertshadercode = ReadShader(vertfilename);
	std::string fragshadercode = ReadShader(fragfilename);

	if (vertshadercode == "" || fragshadercode == "") return;

	GLuint vertshader = CreateShader(GL_VERTEX_SHADER, vertshadercode);
	GLuint fragshader = CreateShader(GL_FRAGMENT_SHADER, fragshadercode);

	if (vertshader == 0 || fragshader == 0) {
		glDeleteShader(vertshader);
		glDeleteShader(fragshader);
		return;
	}

	GLint linkresult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertshader);
	glAttachShader(program, fragshader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkresult);

	if (!linkresult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::vector<char> log(infoLogLength);

		glGetShaderInfoLog(program, infoLogLength, nullptr, &log[0]);

		std::string programstring(log.begin(), log.end());

		DEBUG_ERROR("Failed to link shader: " + programstring);

		glDeleteShader(vertshader);
		glDeleteShader(fragshader);
		glDeleteProgram(program);
		return;
	}

	programs[shadername] = program;
	glDeleteShader(vertshader);
	glDeleteShader(fragshader);
}

GLuint ShaderHandler::GetShader(const std::string& shadername) {
	// find and return shader
	if (programs.find(shadername) != programs.end())
		return programs[shadername];
	// otherwise return 0
	return 0;
}

void ShaderHandler::OnDestroy() {
	if (programs.size() > 0) {

		auto iter = programs.begin();

		while (iter != programs.end()) {
			glDeleteProgram(iter->second);
			++iter;
		}

		programs.clear();
	}
}


