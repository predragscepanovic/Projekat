#ifndef GRUPA_H
#define GRUPA_H

#include "Nalog.h"
#include <stdio.h>

typedef struct
{
    char nadimak[100];
	int tipNaloga;
} NalogUGrupi;

typedef struct
{
    char naziv[100];
    char kod[5];
    int maxClanova;
    int brojClanova;
	NalogUGrupi korisnici[100];
} Grupa;

void DodajGrupu(Grupa* grupa);
Grupa UcitajGrupu(FILE* file);
int DaLiJePrazna(Grupa* grupa);
int Kreator();
int Admin();
int Korisnik();
int Nepostojeci();
int KorisnikovTipUGrupi(Grupa* grupa, Nalog* nalog);
Grupa IzaberiGrupu(Nalog* nalog);
Grupa NadjiGrupu(char* kod);
void IspisGrupe(Grupa* grupa);
void IzmeniGrupu(Grupa* grupa);
int ObrisiGrupu(Grupa* grupa);
NalogUGrupi* IzaberiKorisnika(Grupa* grupa);
void IzbaciKorisnikaIzGrupe(Grupa* grupa, NalogUGrupi* nalogUGrupi);
void PridruziSeGrupi(Grupa* grupa, Nalog* nalog);

#endif // GRUPA_H
