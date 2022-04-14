#define _DEBUG

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/serial.h>
#include <errno.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iomanip>

#include "LecteurRFID.h"
#include "VerifBDD.h"
#include "LSAByte.h"

using namespace std;


CVerifBDD::CVerifBDD() {

    this -> pBadge = new CLecteurRFID;

    this -> pDriver = new sql::mysql::MySQL_Driver;
    this -> pConnector = new sql::Connection;
    this -> pStatement = new sql::Statement;
    this -> pResult = new sql::ResultSet;

}


CVerifBDD::~CVerifBDD() {

    delete pBadge;
    
    delete pDriver;
    delete pResult;
    delete pStatement;
    delete pConnector;

}


void CVerifBDD::ConnexionBDD( string AdresseBDD, string Identifiant, string Mdp ) {

    pDriver = sql::mysql::get_mysql_driver_instance();
    pConnector = pDriver -> connect( AdresseBDD, Identifiant, Mdp ); // "tcp://192.168.0.28:3306", "mathis_carrere", "sbRQi87R7"
    pStatement = pConnector -> createStatement();
    cout << "Connexion" << endl;

}