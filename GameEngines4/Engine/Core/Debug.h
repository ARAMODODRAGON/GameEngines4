#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <string>
using std::string;

enum class Message_Type : unsigned char {
	None = 0,
	Fatal_Error = 1,
	Error = 2,
	Warning = 3,
	Trace = 4,
	Info = 5,
};

class Debug {
private:

public:

	// delete constructors and operators to prevent instancing
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	// static functions
	static void DebugInit();
	static void SetSeverity(Message_Type type);
	static void Info(const string& message, const string& filename, const int& line);
	static void Trace(const string& message, const string& filename, const int& line);
	static void Warning(const string& message, const string& filename, const int& line);
	static void Error(const string& message, const string& filename, const int& line);
	static void FatalError(const string& message, const string& filename, const int& line);

	static string GetFilenameFromPath(const string& path);
private:
	static void Log(const Message_Type type, const std::string& message, const std::string& filename, const int& line);
	static Message_Type currentSeverity;
	static std::string outputName;
};

#define TEXT(value) std::to_string(value)
#define __FILENAME__ Debug::GetFilenameFromPath(__FILE__)
#define DEBUG_INFO(message) Debug::Info(message, __FILENAME__, __LINE__)
#define DEBUG_TRACE(message) Debug::Trace(message, __FILENAME__, __LINE__)
#define DEBUG_WARNING(message) Debug::Warning(message, __FILENAME__, __LINE__)
#define DEBUG_ERROR(message) Debug::Error(message, __FILENAME__, __LINE__)
#define DEBUG_FATALERROR(message) Debug::FatalError(message, __FILENAME__, __LINE__)


#endif // !DEBUG_H