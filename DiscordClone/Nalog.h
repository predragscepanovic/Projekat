#ifndef NALOG_H
#define NALOG_H

typedef struct
{
    char ime[100];
    char prezime[100];
    char email[100];
    char nadimak[100];
    char lozinka[100];
    int brojPrijatelja;
    char prijatelji[100][100];
} Nalog;

void DodajNalog(Nalog* nalog);
Nalog PrazanNalog();
Nalog NadjiNalog(char* nadimakIliEmail, int proveriNadimak, int proveriEmail);
void PrikaziNaloge(char* deoNadimka);
int ObrisiNalog(char* nadimak);
void IzmeniNalog(char* nadimak, Nalog* izmenjenNalog);
int DaLiJePrazan(Nalog* nalog);
void DodajPrijatelja(Nalog* nalog, char* nadimak);

#endif
