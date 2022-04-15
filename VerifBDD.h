#ifndef VERIF_BDD_H
#define VERIF_BDD_H

#include <string.h>
#include <string>
#include <termios.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "LSAByte.h"
#include "LecteurRFID.h"

using namespace std;

class CVerifBDD {

  private:

    CLecteurRFID * pBadge;

    sql::mysql::MySQL_Driver * pDriver;
    sql::Connection * pConnector;
    sql::Statement * pStatement;
    sql::ResultSet * pResult;

    void ConnexionBDD();
    void FermetureBDD();

  public:

    CVerifBDD();
    ~CVerifBDD();
    string VerificationBadge( string IndiceEPC );

};

#endif // VERIF_BDD_H