#ifndef SRC_LUMBERJACK_H_
#define SRC_LUMBERJACK_H_

#include <iostream>

#include "WPILib.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include <LiveWindow/LiveWindowSendable.h>
#include "easylogging++.h"


using namespace std;

/*
 * Logging with printf is great and all, but when something
 * goes wrong and we're not debugging or having the console available
 * this gives flexibility to ship the log somewhere for
 * review or alternate means of visibility.
 */
class LumberJack {
private:
	el::Configurations defaultConf;

	bool
		isInfoLoggingEnabled = RobotMap::isInfoLoggingEnabled,
		isDebugLoggingEnabled = RobotMap::isDebugLoggingEnabled,
		isErrorLoggingEnabled = RobotMap::isErrorLoggingEnabled,
		isWarningLoggingEnabled = RobotMap::isWarningLoggingEnabled,
		isFatalLoggingEnabled = RobotMap::isFatalLoggingEnabled,
		isTraceLoggingEnabled = RobotMap::isTraceLoggingEnabled;

	//This is the severity level that will be represented
	el::Level severityLevelChosen;

	el::Logger* defaultLogger;

public:
	LumberJack();
	virtual ~LumberJack();

	// The logging levels to choose from.
	el::Level
		levelInfo = el::Level::Info,
		levelDebug = el::Level::Debug,
		levelError = el::Level::Error,
		levelWarning = el::Level::Warning,
		levelFatal = el::Level::Fatal,
		levelTrace = el::Level::Trace;

	void SetLoggingLevel(el::Level argSeverityLevel);
	void SetConfig();
	void iLog(char* msg);
	void dLog(char* msg);
	void eLog(char* msg);
	void wLog(char* msg);
	void fLog(char* msg);
	void tLog(char* msg);
	void iLog(const string& msg);
	void dLog(const string& msg);
	void eLog(const string& msg);
	void wLog(const string& msg);
	void fLog(const string& msg);
	void tLog(const string& msg);
	void dashLogData(llvm::StringRef key, Sendable* data);
	void dashLogNumber(llvm::StringRef key, double value);
	void dashLogString(llvm::StringRef key, llvm::StringRef message);
};

#endif /* SRC_LUMBERJACK_H_ */
