#include "logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <chrono>
//#undef NDEBUG                  // uncomment to enable asserts in release build

void DLL_EXPORT LOGGER::dll_load()
{
    std::cout<<"LOGGER_LOAD\n";
}

void  DLL_EXPORT LOGGER::Logger::WriteLog(LogLevel logLevel, std::string message)
{
    std::ofstream logFile("Logfile.txt", std::ios::app);
    if (logLevel == LogLevel::Info)
    {
        logFile << message << "\n";
    }
    if (logLevel == LogLevel::Debug)
    {
        logFile << message << "\n";
        std::cout << message << "\n";
    }
    if (logLevel == LogLevel::Warning)
    {
        logFile << "Warning: " << message << "\n";
        std::cout << "Warning: " << message << "\n";
    }
    if (logLevel == LogLevel::Error)
    {
        logFile << "Error: " << message << "\n";
        logFile.close();
        std::cerr << "Error: " << message << "\n";
        assert(0);
    }
    logFile.close();
}
void DLL_EXPORT LOGGER::Logger::ShowLog()
{
    std::ifstream logFile("Logfile.txt");
    if (logFile.is_open())
    {
        std::string tmp;
        while (!logFile.eof())
        {
            std::getline(logFile, tmp);
            std::cout << tmp << std::endl;
        }
        logFile.close();
    }
    else
        std::cout << "Log file doesn't exist\n";
}

 void DLL_EXPORT LOGGER::Logger::GetTime(std::string message, bool writeToConsole, int unit)
        {
            // writeToConsole = 0 - won't write in console, 1 - will write; unit = 1 - seconds, 0 - ms
            auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - time).count();
            ResetTimer();
            if (unit == 1)
                timeDiff = timeDiff / 1000;
            std::string tmp = message + "\n" + std::to_string(timeDiff);
            if (unit == 1)
                tmp += " s passed.\n";
            else
                tmp += " ms passed.\n";
            LogLevel logLevel = LogLevel::Info;
            if (writeToConsole)
                logLevel = LogLevel::Debug;
            WriteLog(logLevel, tmp);
        }


// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
