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

}


CVerifBDD::~CVerifBDD() {

    delete pBadge;

}


void CVerifBDD::ConnexionBDD() {

    // Connexion a la Base de données
    pDriver = sql::mysql::get_mysql_driver_instance();
    pConnector = pDriver -> connect( "tcp://192.168.0.28:3306", "mathis_carrere", "sbRQi87R7" );
    pStatement = pConnector -> createStatement();

}

void CVerifBDD::FermetureBDD() {

    delete pDriver;
    delete pResult;
    delete pStatement;
    delete pConnector;

}

string CVerifBDD::VerificationBadge( string NumeroEPC ) {
    
    ConnexionBDD();

    pResult = pStatement->executeQuery( "SELECT badge_number FROM BEnOcean.TUsers" );
    
    int NumEPC = atoi(NumeroEPC);
    
    if( NumEPC == pResult->getString( "badge_number" ) ){

    //while ( pResult->next() ){

        cout << "Badge inscrit dans la BDD : " << NumeroEPC << endl;

        //}
    }
    else{

        cout << "Ce badge n'est aps inscrit dans la base de donnees !" << endl;

    }

    FermetureBDD();

}