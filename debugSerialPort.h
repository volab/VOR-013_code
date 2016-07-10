#ifndef DEBUGSERIALPORT_H
#define DEBUGSERIALPORT_H

#define DEBUG
//comment to pass in non debug mode

#define SERIALDEBUG Serial

#define sp(X) SERIALDEBUG.print(X)
#define spl(X) SERIALDEBUG.println(X)

#ifdef DEBUG
#define dsp(X) sp(X)
#define dspl(X) spl(X)
#else
#define dsp(X) sp(X)
#define dspl(X) spl(X)
#endif

#endif