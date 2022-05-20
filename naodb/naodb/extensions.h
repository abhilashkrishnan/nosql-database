#pragma once

#include "database.h"
#include <memory>
#include <string>

using namespace std;

namespace NaoDB {
    class  __declspec(dllexport) NaoDatabase : public Database
    {
    public:
        NaoDatabase(std::string dbname, std::string fullpath);
        virtual ~NaoDatabase() = 0;

        static const std::unique_ptr<Database> CreateEmptyDB(std::string dbname);
        static const std::unique_ptr<Database> LoadDB(std::string dbname);
        static void DeleteDB(std::string dbname);

        virtual std::string GetDBDirectory() override;
        virtual void Destroy() override;

        virtual void SetKeyValue(std::string key, std::string value) override;
        virtual std::string GetKeyValue(std::string key) override;

        class Impl;
    private:
        unique_ptr<Impl> m_Impl;

    };
}