//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
#include "Lettres.h"


// 11/7 : decision de fonctionner avec begin dans Traceur 
// plutot que dans le constructeur
Lettres::Lettres( ){
    // _carac = toupper (c);
    // traceLettre();
}



void Lettres::traceLettre(char c){
    _carac = toupper( c );
    //sp(F("Trace lettre : ")); spl(_carac);
    //spl( freeRam ());
    int nbCmd = readBufferFromSD( "letters", String( _carac) );
    //dspl( nbCmd );
#ifdef DEBUG
    printBufferCmd();
    //tracerDebug();
#else
    //--------------------------------------------------------------------------
    //traceBuffer();
#endif
    //--------------------------------------------------------------------------
}











