#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H
#include <glew.h>
#include "../Core/Debug.h"
#include <memory>
#include <sstream>
#include <map>
#include <vector>


class ShaderHandler {
	std::string ReadShader(const std::string& filename);
	GLuint CreateShader(GLenum shaderType, const std::string& source);
	std::map<std::string, GLuint> programs;

	// singleton
	static std::unique_ptr<ShaderHandler> Singleton;
	friend std::default_delete<ShaderHandler>;
	ShaderHandler();
	~ShaderHandler();
public:
	static ShaderHandler* GetSingleton();
	// disable copy & move constructors/operators
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;
	// end singleton

	void CreateProgram(const std::string& shadername, const std::string& vertfilename, const std::string& fragfilename);
	GLuint GetShader(const std::string& shadername);
	void OnDestroy();
};

#endif // !SHADERHANDLER_H