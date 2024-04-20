#include "ConsoleLog.hpp"

namespace SPN
{
    ConsoleLog::ConsoleLog()
    {}

    void ConsoleLog::writeInfo(const char* data) {
        std::scoped_lock<std::mutex> lock(_mutex);
        printf("\033[94m");
        this->writeDate();
        std::cout << " INFO : ";
        std::cout << data << std::endl;
        printf("\033[0m"); 
    }

    void ConsoleLog::writeError(const char* data)
    {
        std::scoped_lock<std::mutex> lock(_mutex);
        printf("\033[91m");
        this->writeDate();
        std::cout << " ERREUR : ";
        std::cout << data << std::endl;
        printf("\033[0m"); 
    }

    void ConsoleLog::writeWarning(const char* data)
    {

        std::scoped_lock<std::mutex> lock(_mutex);
        printf("\033[93m");
        this->writeDate();
        std::cout << " ATTENTION : ";
        std::cout << data << std::endl;
        printf("\033[0m"); 
    }

    void ConsoleLog::writeSuccess(const char* data)
    {
        std::scoped_lock<std::mutex> lock(_mutex);
        printf("\033[92m");
        this->writeDate();
        std::cout << " INIT : ";
        std::cout << data << std::endl;
        printf("\033[0m"); 
    }

    void ConsoleLog::writeDebug(const char* data)
    {
        std::scoped_lock<std::mutex> lock(_mutex);
        printf("\033[95m");
        this->writeDate();
        std::cout << " DEBUG : ";
        std::cout << data << std::endl;
        printf("\033[0m"); 
    }

    void ConsoleLog::writeDate()
    {
        tm local_time;
        time_t ttime{ time(&ttime) };
        localtime_s(&local_time, &ttime);
        std::cout << "[" << local_time.tm_hour << ":" << local_time.tm_min << ":" << local_time.tm_sec << "]";
    }
}