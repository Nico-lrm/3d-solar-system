#ifndef LOG_HPP
#define LOG_HPP
#pragma once

#include <iostream>
#include <string>
#include <mutex>
#include <ctime>

namespace SPN 
{
    /*!
     * @brief Interface de la classe Log. Doit être hérité pour pouvoir l'utiliser.
     * @author Nicolas LORMIER
     * @date 13/01/2023
    */
    class Log
    {
        public:
            virtual void writeInfo(const char* data) = 0;
            virtual void writeError(const char* data) = 0;
            virtual void writeWarning(const char* data) = 0;
            virtual void writeSuccess(const char* data) = 0;
            virtual void writeDebug(const char* data) = 0;
        protected:
            std::mutex _mutex;
            virtual void writeDate() = 0;
    };
}

#endif