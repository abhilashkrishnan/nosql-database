#pragma once

#include <string>

using namespace std;

namespace NaoDB {
    class  __declspec(dllexport) Database
    {
    public:
        Database(string dbname, string fullPath);

        static Database CreateEmptyDB(string dbname);
        static Database LoadDB(string dbname);
        static void DeleteDB(string dbname);

        string GetDBDirectory() const;
        void Destroy();

        void SetKeyValue(string key, string value);
        string GetKeyValue(string key) const;

    protected:
        string m_dbname;
        string m_fullpath;
    };

}
