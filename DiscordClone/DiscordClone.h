#ifndef DISCORDCLONE_H
#define DISCORDCLONE_H

#include "Nalog.h"
#include "Grupa.h"

void IzprazniInput();
void Start();
Nalog Login();
void Registracija();
void UnesiLozinku(Nalog* nalog);
void UnesiEmail(Nalog* nalog);
int Meni(Nalog nalog);
int ProveriEmail(char* email);
int Brisanje(Nalog* nalog);
void Izmena(Nalog* nalog);
void DodavanjeGrupe(Nalog* kreator);
void IzmenaGrupe(Nalog* nalog);
void BrisanjeGrupe(Nalog* nalog);
void IzmenaKorisnika(Nalog* nalog, Grupa* grupa, int tipUGrupi);
void UlazakUGrupu(Nalog* nalog);
void Prijatelji(Nalog* nalog);
int MeniPrijatelji();
void PrikazPrijatelja(Nalog* nalog);
void DodavanjePrijatelja(Nalog* nalog);

#endif
