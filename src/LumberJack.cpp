#include <LumberJack.h>
INITIALIZE_EASYLOGGINGPP

LumberJack::LumberJack() {
	defaultConf.setToDefault();
}

LumberJack::~LumberJack() {
}

void LumberJack::SetLoggingLevel(el::Level argSeverityLevel)
{
	severityLevelChosen = argSeverityLevel;
}

void LumberJack::SetConfig()
{
	// Values are always std::string
	defaultConf.set(severityLevelChosen, el::ConfigurationType::Format, "%datetime %level %msg");
	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);
}

void LumberJack::iLog(char* msg)
{
	LOG_IF(isInfoLoggingEnabled, INFO) << msg;
}

void LumberJack::dLog(char* msg)
{
	LOG_IF(isDebugLoggingEnabled, DEBUG) << msg;
}

void LumberJack::eLog(char* msg)
{
	LOG_IF(isErrorLoggingEnabled, ERROR) << msg;
}

void LumberJack::wLog(char* msg)
{
	LOG_IF(isWarningLoggingEnabled, WARNING) << msg;
}

void LumberJack::fLog(char* msg)
{
	LOG_IF(isFatalLoggingEnabled, FATAL) << msg;
}

void LumberJack::tLog(char* msg)
{
	LOG_IF(isTraceLoggingEnabled, TRACE) << msg;
}

void LumberJack::iLog(const string& msg)
{
	LOG_IF(isInfoLoggingEnabled, INFO) << msg;
}

void LumberJack::dLog(const string& msg)
{
	LOG_IF(isDebugLoggingEnabled, DEBUG) << msg;
}

void LumberJack::eLog(const string& msg)
{
	LOG_IF(isErrorLoggingEnabled, ERROR) << msg;
}

void LumberJack::wLog(const string& msg)
{
	LOG_IF(isWarningLoggingEnabled, WARNING) << msg;
}

void LumberJack::fLog(const string& msg)
{
	LOG_IF(isFatalLoggingEnabled, FATAL) << msg;
}

void LumberJack::tLog(const string& msg)
{
	LOG_IF(isTraceLoggingEnabled, TRACE) << msg;
}
