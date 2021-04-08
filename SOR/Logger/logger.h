#ifndef __LOG_H__
#define __LOG_H__
#include <windows.h>
#include <fstream>
/*  To use this exported function of dll, include this header
 *  in your project.
 */
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

namespace LOGGER
{
    void DLL_EXPORT dll_load();
    enum class LogLevel
    {
        Info,
        Warning,
        Error
        // DEBUG
    };
    class Logger {
    protected:
        Logger()
        {
            std::ofstream logFile("Logfile.txt");
            logFile.close();
        }

        static Logger* logger_;
    public:
        void operator=(const Logger l) = delete;
        static Logger* GetInstance();
        void DLL_EXPORT WriteLog(LogLevel logLevel, std::string message);
        void DLL_EXPORT ShowLog();
    };
    Logger* Logger::logger_ = nullptr;
    Logger* Logger::GetInstance()
    {
        if (logger_ == nullptr)
            logger_ = new Logger();
        return logger_;
    }
}

#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __LOG_H__
