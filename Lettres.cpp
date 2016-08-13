//----------------------------------------------------------------------------------------------------------------------
// Projet VOR-013 Vor Marley the drawing Robots
// Major Lee
// CC-0
// Juillet 2016
//----------------------------------------------------------------------------------------------------------------------
#include "Lettres.h"

void Lettres::traceLettre(char c){
    _carac = toupper( c );
    dsp(F("Trace lettre : ")); dspl(_carac);
    //file name 8.3 lib SD
    int nbCmd = readBufferFromSD( "lhex", String( _carac) );
#ifdef DEBUG
    printBufferCmd();
    tracerDebug();
#else
    //--------------------------------------------------------------------------
    traceBuffer();
#endif
    //--------------------------------------------------------------------------
}











