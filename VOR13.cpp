


#include <Arduino.h>
#include "VOR13.h"

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
        case LASTREC_DESSINE:
        trame += "recu dessine";
        break;
        case LASTREC_TEXTE:
        trame += "recu texte";
        break;
        case LASTREC_MODEDESSIN:
        trame += "recu mode dessin";
        break;
        case LASTREC_MODETEXTE:
        trame += "recu mode texte";
        break;
        case LASTREC_UNKNOW:
        trame += "commande inconnue";
        break;
    }
    return trame;
}

String VOR13::get_aEcrire(){
    return _aEcrire;
}