#pragma once
#include "database.h"
#include<memory>
#include <string>

using namespace std;

namespace NaoDB {
    class  __declspec(dllexport) NaoDB
    {
    public:
        NaoDB();
        ~NaoDB() {};
        static const std::unique_ptr<Database> CreateEmptyDB(std::string dbname);
        static const std::unique_ptr<Database> LoadDB(std::string dbname);
        //static void DeleteDB(std::string dbname);
    };
}

