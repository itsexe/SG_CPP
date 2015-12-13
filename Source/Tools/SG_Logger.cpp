
#include "SG_Logger.h"
#include <stdexcept>
#include <string>

const std::string SG_Logger::kLogLevelDebug = "DEBUG   ";
const std::string SG_Logger::kLogLevelInfo = "INFO    ";
const std::string SG_Logger::kLogLevelError = "ERROR   ";
const std::string SG_Logger::kLogLevelPacket = "PACKET  ";
const std::string SG_Logger::kLogLevelPlayer = "PLAYER  ";
const std::string SG_Logger::kLogLevelDatabase = "DATABASE";
const std::string SG_Logger::kLogLevelAuth = "Auth    ";
const std::string SG_Logger::kLogLevelMMO = "MMO     ";
const std::string SG_Logger::kLogLevelLobby = "Lobby   ";
const std::string SG_Logger::kLogLevelChat = "Chat    ";

const char* const SG_Logger::kLogFileName = "Log.txt";

SG_Logger* SG_Logger::pInstance = nullptr;
std::mutex SG_Logger::sMutex;

SG_Logger& SG_Logger::instance()
{
	static Cleanup cleanup;

	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr)
		pInstance = new SG_Logger();
	return *pInstance;
}

SG_Logger::Cleanup::~Cleanup()
{
	std::lock_guard<std::mutex> guard(SG_Logger::sMutex);
	delete SG_Logger::pInstance;
	SG_Logger::pInstance = nullptr;
}

SG_Logger::~SG_Logger()
{
	mOutputStream.close();
}

SG_Logger::SG_Logger()
{
	mOutputStream.open(kLogFileName, std::ios_base::app);
	if (!mOutputStream.good()) {
		throw std::runtime_error("Unable to initialize the Logger!");
	}
}

void SG_Logger::log(const std::string& inMessage, const std::string& inLogLevel)
{
	std::lock_guard<std::mutex> guard(sMutex);
	logHelper(inMessage, inLogLevel);
}

void SG_Logger::log(const std::vector<std::string>& inMessages, const std::string& inLogLevel)
{
	std::lock_guard<std::mutex> guard(sMutex);
	for (size_t i = 0; i < inMessages.size(); i++) {
		logHelper(inMessages[i], inLogLevel);
	}
}

void SG_Logger::logHelper(const std::string& inMessage, const std::string& inLogLevel)
{
	std::cout << "[" << inLogLevel << "] " << inMessage << std::endl;
	mOutputStream << "[" << inLogLevel << "] " << inMessage << std::endl;
}