// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// permet de conserver l'état du robot et d'effectuer les tâches commune.

#include <Arduino.h>
#include "VOR13.h"
#include "debugSerialPort.h"

VOR13::VOR13(): _aEcrire( "VOLAB" ) {}

void VOR13::begin(){
    _mode = MODE_ECRIT; // mode par defaut
    _etat = ETAT_ATTENTE;
    _recState = NOREC;
}

String VOR13::buildStateTrame(){
    String trame;
    switch (_mode){
        case MODE_ECRIT:
        trame = "Mode ecrit,";
        break;
        case MODE_DESSINE:
        trame = "Mode dessin,";
        break;
    }
    switch (_etat){
        case ETAT_ATTENTE:
        trame += "en attente, ";
        break;
        case ETAT_WORK:
        trame += "en cours, ";
        break;
        case ETAT_FINI:
        trame += "fini, ";
        break;
    }
    switch (_recState){
        case NOREC:
        trame += "rien recu";
        break;
        case LASTREC_GO:
        trame += "recu GO";
        break;
        case LASTREC_DESSINE: // finalement pas utilise
        trame += "recu dessine";
        break;
        case LASTREC_TEXTE: // finalement pas utilise
        trame += "recu : " + _aEcrire ;
        break;
        case LASTREC_MODEDESSIN:
        trame += "recu mode dessin et " ; // + aDessiner
        break;
        case LASTREC_MODETEXTE:
        trame += "recu mode texte et " + _aEcrire ;
        break;
        case LASTREC_UNKNOW:
        trame += "commande inconnue";
        break;
    }
    return trame;
}

boolean VOR13::go(){
    return ( _recState == LASTREC_GO );
}

void VOR13::interpreteTrame( String trame ){
    if ( trame == "GO" ){
        _recState = LASTREC_GO;
        return;
    } else if ( trame.indexOf('_') == 1 ){
        if ( trame.startsWith("D")){
            _mode = MODE_DESSINE;
            //aDessinner =  trame.substring(2);
            //verifier si le fichier exist
            //sinon => unknow file => retour mode ecrit
            // dessine reste a implementer
            _recState = LASTREC_MODEDESSIN;
        } else if ( trame.startsWith("E") ){
            _mode = MODE_ECRIT;
            _aEcrire = trame.substring(2);
            sp("-");SERIALDEBUG.print( _aEcrire.charAt(_aEcrire.length()-1 ), HEX );spl("-");
            _recState = LASTREC_MODETEXTE;
        }
    } else {
        _recState = LASTREC_UNKNOW;
    }
}










