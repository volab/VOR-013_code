//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
// Les constantes du robot

#ifndef VOR13_H
#define VOR13_H

#define MODE_ECRIT 0
#define MODE_DESSINE 1

#define ETAT_ATTENTE 0
#define ETAT_WORK 1
#define ETAT_FINI 2

#define NOREC 0
#define LASTREC_GO 1
#define LASTREC_DESSINE 2
#define LASTREC_TEXTE 3
#define LASTREC_MODEDESSIN 4
#define LASTREC_MODETEXTE 5
#define LASTREC_UNKNOW 6

class VOR13 {
    String _aEcrire;
    int _mode;
    int _etat;
    int _recState;
    
    public:
    VOR13();
    void begin();
    String buildStateTrame();
    String get_aEcrire(){ return _aEcrire; };
    void interpreteTrame( String recTrame );
    boolean go();
    void setState( int etat ){ _etat = etat; };
};

#endif

