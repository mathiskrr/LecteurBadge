#ifndef CBDD_H
#define CBDD_H

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

class CBDD {

  private:

    sql::mysql::MySQL_Driver * pDriver;
    sql::Connection * pConnector;
    sql::Statement * pStatement;
    sql::ResultSet * pResult;

    string HostName;
    string UserID;
    string Password;

    void OuvrirBDD();
    void FermerBDD();

  public:

    CBDD( string IP, string Login, string MDP );
    ~CBDD();
    bool VerifierBadge( string IndiceEPC, string Salle );

};

#endif // CBDD_H