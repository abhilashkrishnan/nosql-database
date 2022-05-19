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

    return 0;
}
