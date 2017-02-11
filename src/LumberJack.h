/*
 * LumberJack.h
 *
 *  Created on: Feb 5, 2017
 *      Author: Pete
 */

#ifndef SRC_LUMBERJACK_H_
#define SRC_LUMBERJACK_H_

#include <iostream>

#include "RobotMap.h"
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
	void iLog(string& msg);
	void dLog(string& msg);
	void eLog(string& msg);
	void wLog(string& msg);
	void fLog(string& msg);
	void tLog(string& msg);
};

#endif /* SRC_LUMBERJACK_H_ */
