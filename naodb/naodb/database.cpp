#include "naodb.h"
#include "database.h"
#include "extensions.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>



using namespace std;

namespace NaoDB {

   

    class  NaoDatabase::Impl : public Database
    {
    public:
        Impl(std::string dbname, std::string fullpath);
        ~Impl();

        static const std::unique_ptr<Database> CreateEmptyDB(std::string dbname);
        static const std::unique_ptr<Database> LoadDB(std::string dbname);
        static void DeleteDB(std::string dbname);

        virtual std::string GetDBDirectory() override;
        virtual void Destroy() override;

        virtual void SetKeyValue(std::string key, std::string value) override;
        virtual std::string GetKeyValue(std::string key) override;
    private:
        std::string m_dbname;
        std::string m_fullpath;
        std::unordered_map<std::string, std::string> m_KeyValueStore;
    };

    NaoDatabase::Impl::Impl(std::string dbname, std::string fullpath) :
        m_dbname(dbname), m_fullpath(fullpath)
    {
        for (auto& p : filesystem::directory_iterator(GetDBDirectory()))
        {
            if (p.exists() && p.is_regular_file())
            {
                string keyWithString = p.path().filename().string();
                string key = keyWithString.substr(0, keyWithString.length() - 10);

                if (".kv" == p.path().extension())
                {
                    ifstream is(p.path());

                    string value;

                    is.seekg(0, ios::end);
                    value.reserve(is.tellg());
                    is.seekg(0, ios::beg);
                    value.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());

                    m_KeyValueStore.insert({ key, value });
                }
            }
        }
    }

    NaoDatabase::Impl::~Impl()
    {

    }
         
    const std::unique_ptr<Database> NaoDatabase::Impl::CreateEmptyDB(string dbname)
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

        return std::make_unique<NaoDatabase::Impl>(dbname, dbfolder);
    }

    const std::unique_ptr<Database> NaoDatabase::Impl::LoadDB(std::string dbname)
    {
        string basedir("./naodb");
        string dbfolder(basedir + "/" + dbname);
        return std::make_unique<NaoDatabase::Impl>(dbname, dbfolder);
    }

    /*void NaoDB::DeleteDB(std::string dbname)
    {
    }*/

    void NaoDatabase::Impl::DeleteDB(string dbname)
    {
        string basedir("./naodb");
        string dbfolder(basedir + "/" + dbname);

        if (filesystem::exists(dbfolder))
        {
            filesystem::remove_all(dbfolder);
        }
    }

    string NaoDatabase::Impl::GetDBDirectory() 
    {
        return m_fullpath;
    }

    void NaoDatabase::Impl::Destroy()
    {
        if (filesystem::exists(m_fullpath))
        {
            filesystem::remove_all(m_fullpath);
        }

        m_KeyValueStore.clear();
    }

    void NaoDatabase::Impl::SetKeyValue(string key, string value)
    {
        ofstream os;
        os.open(m_fullpath + "/" + key + "_string.kv", ios::out | ios::trunc);
        os << value;
        os.close();

        m_KeyValueStore.insert({ key, value });
    }

    string NaoDatabase::Impl::GetKeyValue(string key) 
    {
        /*string keydb(m_fullpath + "/" + key + "_string.kv");
        string value("");

        if (filesystem::exists(keydb))
        {
            ifstream is(m_fullpath + "/" + key + "_string.kv");


            string value;

            is.seekg(0, ios::end);

            value.reserve(is.tellg());

            is.seekg(0, ios::beg);

            value.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());

            return value;
        }
        else
        {
            cout << "No value exists for the key: " << key << endl;
            return value;
        }*/

        const auto& v = m_KeyValueStore.find(key);

        if (v == m_KeyValueStore.end())
        {
            return "";
        }

        return v->second;
    }

    NaoDatabase::NaoDatabase(std::string dbname, std::string fullpath)
        : m_Impl(std::make_unique<NaoDatabase::Impl>(dbname, fullpath))
    {
       
    }

    NaoDatabase::~NaoDatabase()
    {

    }

    const std::unique_ptr<Database> NaoDatabase::CreateEmptyDB(string dbname)
    {
        return NaoDatabase::Impl::CreateEmptyDB(dbname);
    }

    const std::unique_ptr<Database> NaoDatabase::LoadDB(string dbname)
    {
        return NaoDatabase::Impl::LoadDB(dbname);
    }

    void NaoDatabase::DeleteDB(string dbname)
    {
        return NaoDatabase::Impl::DeleteDB(dbname);
    }

    string NaoDatabase::GetDBDirectory()
    {
        return m_Impl->GetDBDirectory();
    }

    void NaoDatabase::Destroy()
    {
        return m_Impl->Destroy();
    }

    void NaoDatabase::SetKeyValue(string key, string value)
    {
        return m_Impl->SetKeyValue(key, value);
    }

    string NaoDatabase::GetKeyValue(string key)
    {
        return m_Impl->GetKeyValue(key);
    }
   
    /*const std::unique_ptr<Database> Database::CreateEmptyDB(std::string dbname)
    {
        return NaoDatabase::CreateEmptyDB(dbname);
    }*/
    const std::unique_ptr<Database> Database::LoadDB(std::string dbname)
    {
        return NaoDatabase::Impl::LoadDB(dbname);
    }
    void Database::DeleteDB(std::string dbname)
    {
        NaoDatabase::Impl::DeleteDB(dbname);
    }
}
