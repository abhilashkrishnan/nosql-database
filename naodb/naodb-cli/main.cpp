#include <iostream>
#include "database.h"

using namespace std;

int main()
{
    cout << "NaoDB Cli" << endl;

    NaoDB::Database db = NaoDB::Database::CreateEmptyDB("testdb");
    db.LoadDB("testdb");
    string dir = db.GetDBDirectory();

    cout << "Dir: " + dir << endl;

    string key = "Customer";

    db.SetKeyValue(key, "Annis Jackson");
    
    string json = R"(

        "Italy" : {
               "Name" : "Federico",
                "Designation" : "Director",
                "Email" : "fed@milan.it" 
         }
    )";

    key = "CustomerJson";
    db.SetKeyValue(key, json);
    
    cout << "Key: " << key << ", Value: " << db.GetKeyValue(key);

    
    return 0;
}
