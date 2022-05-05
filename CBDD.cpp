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

#include "CLecteurRFID.h"
#include "CBDD.h"
#include "LSAByte.h"

using namespace std;


CBDD::CBDD( string IP, string Login, string MDP ) {

    this -> HostName = IP;
    this -> UserID = Login;
    this -> Password = MDP;

}


CBDD::~CBDD() {
    
}


void CBDD::OuvrirBDD() {

    // Connexion a la Base de données

    pDriver = sql::mysql::get_mysql_driver_instance();
    pConnector = pDriver -> connect( HostName, UserID, Password );
    pStatement = pConnector -> createStatement();

}

void CBDD::FermerBDD() {

    delete pStatement;
    delete pConnector;
}

bool CBDD::VerifierBadge( string NumeroEPC, string Salle ) {
    
    string Badge;
    
    string Requete = "SELECT CASE WHEN `badge_number` = " + NumeroEPC + " AND `room_id` = " + Salle + " THEN 'true' ELSE 'false' END AS Autorisation FROM BEnOcean.TUsers ORDER BY Autorisation DESC LIMIT 1;";

    OuvrirBDD();


    pResult = pStatement->executeQuery( Requete );

    pResult->next();

    Badge = pResult->getString( "Autorisation" );

    delete pResult;

    FermerBDD();

    if( Badge == "false" ){

        cout << "Ce badge n'est pas inscrit dans la base de donnees !" << endl;

        return false;

    }
    else{

        cout << "Ce Badge est inscrit dans la base de donnees !" << endl;

        return true;

    }

}