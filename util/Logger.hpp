/*
* FILE:   Logger.hpp
* AUTHOR: Jinchao Liu
* DATE: 
* BRIEF:  A logger class which helps trace functions for debugging.
* USAGE:
*        In Logger.hpp:
* 
*            // Enable the following line if logging into file is desired.
*            //#define FILE_LOG_TO_FILE
*
*            // Logging levels
*            //#define FILE_LOG_ERROR
*            //#define FILE_LOG_WARNING
*            //#define FILE_LOG_INFO
*            #define FILE_LOG_DEBUG
*            //#define FILE_LOG_VERBOSE
* 
*        In your files:
*
*            returnValue YourFunc(inputValue)
*	     {
*	         FuncTraceBeginM(LOG_VERBOSE, "");                       
*                // Do something             
*                FuncTraceEndM(LOG_VERBOSE, "");
*            }
*
*        Typical Output:
*            : dd/mm/yy hh:mm:ss DEBUG YourFunc() Begin
*            : dd/mm/yy hh:mm:ss DEBUG YourFunc(), Elapsed time: xx seconds
*            : dd/mm/yy hh:mm:ss DEBUG YourFunc() End
*
*/
#ifndef Util_Logger_Hpp
#define Util_Logger_Hpp

#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <Windows.h>
#include <cstdio>


namespace Util
{
using namespace std;

// Enable the following line if logging into file is desired. 
//#define FILE_LOG_TO_FILE

// Logging levels
//#define FILE_LOG_ERROR
//#define FILE_LOG_WARNING
//#define FILE_LOG_INFO
#define FILE_LOG_DEBUG
//#define FILE_LOG_VERBOSE


/// \brief Log levels. There are five basic levels: ERROR, WARNING, INFO, DEBUG, VERBOSE. 
enum LogLevel 
{
	LOG_ERROR   = 0,  // Errors
	LOG_WARNING = 1,  // Warings
	LOG_INFO    = 2,  // Useful info
	LOG_DEBUG   = 3,  // Debug info
	LOG_VERBOSE = 4   // Everything
};


/// \brief A lightweight timer class.
class Timer
{
public:
	/// \brief Start timer
	inline void Start()
	{
		m_beginTime = GetTickCount();
	}

	/// \brief Stop timer
	inline void Stop()
	{
		DWORD endTime = GetTickCount();
		m_elapsedTime = endTime - m_beginTime;	
	}

	/// \brief Get the elapsed time
	/// \return elapsed time, double.
	inline double GetElapsedTime()
	{
		return m_elapsedTime/1000.0;	
	}

private:
	DWORD m_beginTime;
	DWORD m_elapsedTime;
};


/// \brief Output policy. 
class OutputToFile 
{
public:
    	inline static FILE* GetStream()
    	{		
		return m_pStream;
    	}

    	inline static void SetStream(FILE* pStream)
    	{
		m_pStream = pStream;
    	}

	    /// \brief Output a message string to the stream
	    /// \param[in] message. std::string&.
	    inline static void Output(const std::string& msg)
	    {
		if(!m_pStream)
		{ 
			m_pStream = stdout; 
		}
		fprintf(m_pStream, "%s", msg.c_str());
	        fflush(m_pStream);
	    }
private:
    	static FILE* m_pStream;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// Logger
///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief A class for logging and debugging.
template<typename OutputPolicy>
class Logger
{
public:
    	/// \brief Constructor 
	Logger();

    	/// \brief Destructor 
    	virtual ~Logger();

    	/// \brief Return a std::ostringstream
    	/// \param[in] Desired log level
    	/// \return std::ostringstream
    	std::ostringstream& Get(LogLevel level = LOG_INFO);	

    	/// \brief Report the current level.
    	/// \return The current level
    	inline static LogLevel& ReportingLevel(){ return m_reportingLevel; }
	
    	/// \brief Get the timer
    	/// \return Timer
    	inline static Timer& GetTimer(){ return m_timer; }

protected:
    	std::ostringstream os;

private:
    	Logger(const Logger&){}
    	Logger& operator =(const Logger&){}
    	static const string GetCurrentTime();

private:
    	static Timer    m_timer;
    	static LogLevel m_reportingLevel;
    	static string   m_logLevelName[]; 
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename OutputPolicy>
std::string Logger<OutputPolicy>::m_logLevelName[] = {
	"ERROR  ", "WARNING", "INFO   ", "DEBUG  ", "VERBOSE"
};

#ifdef FILE_LOG_ERROR
template<typename OutputPolicy>
LogLevel Logger<OutputPolicy>::m_reportingLevel = LogLevel::LOG_ERROR;
#endif

#ifdef FILE_LOG_WARNING
template<typename OutputPolicy>
LogLevel Logger<OutputPolicy>::m_reportingLevel = LogLevel::LOG_WARNING;
#endif

#ifdef FILE_LOG_INFO
template<typename OutputPolicy>
LogLevel Logger<OutputPolicy>::m_reportingLevel = LogLevel::LOG_INFO;
#endif

#ifdef FILE_LOG_DEBUG
template<typename OutputPolicy>
LogLevel Logger<OutputPolicy>::m_reportingLevel = LogLevel::LOG_DEBUG;
#endif

#ifdef FILE_LOG_VERBOSE
template<typename OutputPolicy>
LogLevel Logger<OutputPolicy>::m_reportingLevel = LogLevel::LOG_VERBOSE;
#endif

template<typename OutputPolicy>
Timer Logger<OutputPolicy>::m_timer = Timer();

template<typename OutputPolicy>
Logger<OutputPolicy>::Logger(){ }

template<typename OutputPolicy>
Logger<OutputPolicy>::~Logger()
{
    OutputPolicy::Output(os.str());
}

/// WARNING!!! Not thread-safe. 
template<typename OutputPolicy>
const std::string Logger<OutputPolicy>::GetCurrentTime()
{
    time_t now = time(0);
    struct tm  ts;
    char buf[80];
    ts = *localtime(&now);    
    strftime(buf, sizeof(buf), "%d/%m/%y %X", &ts);
    return buf;
}

template<typename OutputPolicy>
std::ostringstream& Logger<OutputPolicy>::Get(LogLevel level)
{
    os << ""  << GetCurrentTime();
    os << " " << m_logLevelName[level] << " ";
    //os << std::string(level > eLogDEBUG ? 0 : level - eLogDEBUG);
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Macros and Definitions for logging.
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef Logger<OutputToFile> FileLogger;

#define FILE_LOG(level) \
if (level > FileLogger::ReportingLevel() || !OutputToFile::GetStream()) ; \
else FileLogger().Get(level)

#define FILE_LOG_START_TIMER(level) \
if (level > FileLogger::ReportingLevel() || !OutputToFile::GetStream()) ; \
else FileLogger().GetTimer().Start()

#define FILE_LOG_STOP_TIMER(level) \
if (level > FileLogger::ReportingLevel() || !OutputToFile::GetStream()) ; \
else FileLogger().GetTimer().Stop()

#define FILE_LOG_ELAPSED_TIME \
FileLogger().GetTimer().GetElapsedTime()

/// \brief Macro for logging function info, begin
#ifndef NDEBUG

#ifdef WIN32 
#define FuncName __FUNCTION__
#else 
#define FuncName 
#endif 

#define FuncTraceBeginM(LogLevel, Msg) \
FILE_LOG(LogLevel) << FuncName << "(), Begin" << std::endl; \
if(strcmp(Msg, "")!=0){FILE_LOG(LogLevel) << FuncName << "(), " << Msg << std::endl;}\
FILE_LOG_START_TIMER(LogLevel); 

#else  // NDEBUG
#define FuncTraceBeginM(Msg) 
#endif 

#ifndef NDEBUG

#define FuncTraceEndM(LogLevel, Msg) \
FILE_LOG_STOP_TIMER(LogLevel); \
if(strcmp(Msg, "")!=0){FILE_LOG(LogLevel) << FuncName << "(), " << Msg << std::endl;}\
FILE_LOG(LogLevel) << FuncName << "(), Elapsed time : " << FILE_LOG_ELAPSED_TIME << " s" << std::endl; \
FILE_LOG(LogLevel) << FuncName << "(), End" << std::endl; \

#else  // NDEBUG
#define FuncTraceEndM(Msg) 
#endif 


#ifndef NDEBUG
#define LogInfoM(LogLevel, Msg) \
FILE_LOG(LogLevel) << FuncName << "(), Begin" << std::endl; \
if(strcmp(Msg, "")!=0){FILE_LOG(LogLevel) << FuncName << "(), " << Msg << std::endl;}
#else  // NDEBUG
#define LogInfoM(LogLevel, Msg) 
#endif 


#ifndef Macro_ThrowMessageBox
#define Macro_ThrowMessageBox
#define Throw_MessageBox(msg, title) \
	MessageBox(NULL, msg, title, MB_OK | MB_ICONWARNING | MB_HELP); 
#endif
}
#endif

