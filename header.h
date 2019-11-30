#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include "bloc.h"
#include "svgfile.h"
#include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }


class cmgl {};

void lireFichier(Bloc*& racine);
void Menu();
Bloc* store(Bloc* racine);

#endif // HEADER_H_INCLUDED
