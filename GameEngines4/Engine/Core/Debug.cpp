#include "Debug.h"

Message_Type Debug::currentSeverity = Message_Type::None;
string Debug::outputName = "";

void Debug::DebugInit() {
	// set the log filename
	outputName = "EngineLog.txt";

	// create/open file
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();

	// set the current severity
	currentSeverity = Message_Type::Fatal_Error;
}

void Debug::SetSeverity(Message_Type type) {
	currentSeverity = type;
}



void Debug::Info(const string& message, const string& filename, const int& line) {
	// call the log function
	Log(Message_Type::Info, "[INFO]: " + message, filename, line);
}

void Debug::Trace(const string& message, const string& filename, const int& line) {
	// call the log function
	Log(Message_Type::Trace, "[TRACE]: " + message, filename, line);
}

void Debug::Warning(const string& message, const string& filename, const int& line) {
	// call the log function
	Log(Message_Type::Warning, "[WARNING]: " + message, filename, line);
}

void Debug::Error(const string& message, const string& filename, const int& line) {
	// call the log function
	Log(Message_Type::Error, "[ERROR]: " + message, filename, line);
}

void Debug::FatalError(const string& message, const string& filename, const int& line) {
	// call the log function
	Log(Message_Type::Fatal_Error, "[FATAL_ERROR]: " + message, filename, line);
}

string Debug::GetFilenameFromPath(const string& path) {

	string filename = "";

	size_t i = path.size() - 1;
	for (; i < path.size(); --i) {
		if (path[i] == *("\\")) {
			++i;
			break;
		}
	}
	if (i > path.size() - 1) i = 0;

	filename = path.substr(i);

	return filename;
}





void Debug::Log(const Message_Type type, const string& message, const string& filename, const int& line) {
	// check type to severity
	if (type <= currentSeverity && currentSeverity > Message_Type::None) {
		// open file
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);

		// print to file and console
		out << message << " in: " << filename << " on line: " << line << std::endl;
		//std::cout << message << std::endl;

		// exit file
		out.flush();
		out.close();
	}
}
