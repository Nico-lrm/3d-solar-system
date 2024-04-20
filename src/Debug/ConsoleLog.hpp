#ifndef CONSOLELOG_HPP
#define CONSOLELOG_HPP
#pragma once

#include "Log.hpp"

namespace SPN 
{
    /*!
     * @brief Implémentation de la classe Log.
     * Offre un affichage textuel coloré dans la console pour le débug.
     * @author Nicolas LORMIER
     * @date 13/01/2023
    */
    class ConsoleLog final : public Log
    {
        public:
            ConsoleLog();
            void writeInfo(const char* data) override;
            void writeError(const char* data) override;
            void writeWarning(const char* data) override;
            void writeSuccess(const char* data) override;
            void writeDebug(const char* data) override;
        private:
            void writeDate();
    };
}

#endif