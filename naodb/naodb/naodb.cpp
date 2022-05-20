#include "naodb.h"
#include "extensions.h"

namespace NaoDB {
    NaoDB::NaoDB()
    {
    }

    const std::unique_ptr<Database> NaoDB::CreateEmptyDB(std::string dbname)
    {
        return NaoDatabase::CreateEmptyDB(dbname);
    }

    
    const std::unique_ptr<Database> NaoDB::LoadDB(std::string dbname)
    {
        return NaoDatabase::LoadDB(dbname);
    }

    /*void DeleteDB(std::string dbname)
    {

    }*/
    
}

