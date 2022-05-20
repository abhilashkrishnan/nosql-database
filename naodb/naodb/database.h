#pragma once

#include <string>
#include <memory>

using namespace std;

namespace NaoDB {

    class  __declspec(dllexport) Database
    {
    public:
        Database() = default;
        virtual ~Database() = default;

        static const std::unique_ptr<Database> CreateEmptyDB(std::string dbname);
        static const std::unique_ptr<Database> LoadDB(std::string dbname);
        static void DeleteDB(std::string dbname);

        virtual std::string GetDBDirectory() = 0;
        virtual void Destroy() = 0;

        virtual void SetKeyValue(std::string key, std::string value) = 0;
        virtual std::string GetKeyValue(std::string key) = 0;
      
    };

}
