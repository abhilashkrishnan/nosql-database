#include "database.h"

#include <filesystem>
#include <fstream>

using namespace std;

namespace NaoDB {
    Database::Database(string dbname, string fullPath)
        : m_dbname(dbname), m_fullpath(fullPath)
    {

    }

    Database Database::CreateEmptyDB(string dbname)
    {
        string basedir("./naodb");

        if (!filesystem::exists(basedir))
        {
            filesystem::create_directory(basedir);
        }

        string dbfolder(basedir + "/" + dbname);
        if (!filesystem::exists(dbfolder))
        {
            filesystem::create_directory(dbfolder);
        }

        return Database(dbname, dbfolder);
    }

    Database Database::LoadDB(string dbname)
    {
        string basedir("./naodb");
        string dbfolder(basedir + "/" + dbname);
        return Database(dbname, dbfolder);
    }

    void Database::DeleteDB(string dbname)
    {
        string basedir("./naodb");
        string dbfolder(basedir + "/" + dbname);

        if (filesystem::exists(dbfolder))
        {
            filesystem::remove_all(dbfolder);
        }
    }

    string Database::GetDBDirectory() const
    {
        return m_fullpath;
    }

    void Database::Destroy()
    {
        if (filesystem::exists(m_fullpath))
        {
            filesystem::remove_all(m_fullpath);
        }
    }

    void Database::SetKeyValue(string key, string value)
    {
        ofstream os;
        os.open(m_fullpath + "/" + key + "_string.kv", ios::out | ios::trunc);
        os << value;
        os.close();
    }

    string Database::GetKeyValue(string key) const
    {
        ifstream is(m_fullpath + "/" + key + "_string.kv");

        string value;

        is.seekg(0, ios::end);
        value.reserve(is.tellg());
        is.seekg(0, ios::beg);

        value.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());

        return value;
    }


}
