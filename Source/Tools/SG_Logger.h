#ifndef SG_LOG
#define SG_LOG
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
class SG_Logger
{
public:
	static const std::string kLogLevelDebug;
	static const std::string kLogLevelInfo;
	static const std::string kLogLevelError;
	static const std::string kLogLevelPacket;
	static const std::string kLogLevelPlayer;
	static const std::string kLogLevelDatabase;
	static const std::string kLogLevelAuth;
	static const std::string kLogLevelMMO;
	static const std::string kLogLevelLobby;


	// Returns a reference to the singleton Logger object
	static SG_Logger& instance();

	// Logs a single message at the given log level
	void log(const std::string& inMessage,
		const std::string& inLogLevel);

	// Logs a vector of messages at the given log level
	void log(const std::vector<std::string>& inMessages,
		const std::string& inLogLevel);

protected:
	// Static variable for the one-and-only instance  
	static SG_Logger* pInstance;

	// Constant for the filename
	static const char* const kLogFileName;

	// Data member for the output stream
	std::ofstream mOutputStream;

	// Embedded class to make sure the single Logger
	// instance gets deleted on program shutdown.
	friend class Cleanup;
	class Cleanup
	{
	public:
		~Cleanup();
	};

	// Logs message. The thread should own a lock on sMutex
	// before calling this function.
	void logHelper(const std::string& inMessage,
		const std::string& inLogLevel);

private:
	SG_Logger();
	virtual ~SG_Logger();
	SG_Logger(const SG_Logger&);
	SG_Logger& operator=(const SG_Logger&);
	static std::mutex sMutex;
};

#endif