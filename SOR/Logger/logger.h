#ifndef __LOG_H__
#define __LOG_H__
#include <windows.h>
#include <iostream>
#include <fstream>
#include <chrono>

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
        Debug,
        Warning,
        Error
    };
    class Logger {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> time;
        Logger()
        {
            time = std::chrono::high_resolution_clock::now();
            std::ofstream logFile("Logfile.txt", std::ios::app);
            time_t currentTime;
            struct tm * timeInfo;
            char buffer[30];
            std::time (&currentTime);
            timeInfo = localtime (&currentTime);
            strftime (buffer, 30,"%d.%m.%Y %H:%M:%S: ",timeInfo);
            for (int i = 0; i < 60; i++)
                logFile << "_";
            logFile << "\n\n\n" << buffer << "New launch\n";
            logFile.close();
            std::cout << buffer << "New launch\n";
        }
        static Logger* logger_;
    public:
        void operator=(const Logger l) = delete;
        static Logger* GetInstance();

        void DLL_EXPORT WriteLog(LogLevel logLevel, std::string message);
        void DLL_EXPORT ShowLog();
        void ResetTimer() { time = std::chrono::high_resolution_clock::now(); }
        void DLL_EXPORT GetTime(std::string message = "", bool writeToConsole = false, int unit = 0);
        void ClearLogFile()
        {
            std::ofstream logFile("Logfile.txt");
            logFile.close();
        }
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
