#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "Grupa.h"
#include "Nalog.h"


int Kreator()
{
    return 0;
}


int Admin()
{
    return 1;
}


int Korisnik()
{
    return 2;
}


int Nepostojeci()
{
    return -1;
}

Grupa PraznaGrupa()
{

    Grupa grupa;
    grupa.naziv[0] = '\0';
    return grupa;
}

Grupa UcitajGrupu(FILE* file)
{
    Grupa grupa;
    fscanf(file,"%s", grupa.naziv);

    if(feof(file))
    {
        return PraznaGrupa();
    }

    fgetc(file);
    fscanf(file,"%s", grupa.kod);
    fgetc(file);
    fscanf(file,"%d", &grupa.maxClanova);
    fgetc(file);
    fscanf(file,"%d", &grupa.brojClanova);
    fgetc(file);
    for(int i = 0; i < grupa.brojClanova; i++)
    {
        fscanf(file,"%s", grupa.korisnici[i].nadimak);
        fgetc(file);
        fscanf(file,"%d", &grupa.korisnici[i].tipNaloga);
        fgetc(file);
    }

    return grupa;
}

void DodajGrupu(Grupa* grupa)
{
    FILE* file = fopen("grupe.txt", "a");
    if (file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return;
    }


    fseek(file, 0, SEEK_END);


    fprintf(file, "%s", grupa->naziv);
    fputc(' ', file);
    fprintf(file, "%s", grupa->kod);
    fputc(' ', file);
    fprintf(file, "%d", grupa->maxClanova);
    fputc(' ', file);
    fprintf(file, "%d", grupa->brojClanova);
    fputc(' ', file);

    for(int i = 0; i < grupa->brojClanova; i++)
    {
        fprintf(file, "%s", grupa->korisnici[i].nadimak);
        fputc(' ', file);
        fprintf(file, "%d", grupa->korisnici[i].tipNaloga);
        fputc(' ', file);
    }
    fclose(file);
}

int DaLiJePrazna(Grupa* grupa)
{
    return grupa->naziv[0] == '\0';
}

void PridruziSeGrupi(Grupa* grupa, Nalog* nalog)
{
    grupa->korisnici[grupa->brojClanova].tipNaloga = Korisnik();
    strcpy(grupa->korisnici[grupa->brojClanova].nadimak, nalog->nadimak);
    grupa->brojClanova++;

    IzmeniGrupu(grupa);
}


int KorisnikovTipUGrupi(Grupa* grupa, Nalog* nalog)
{
    for(int i = 0; i < grupa->brojClanova; i++)
    {
        if(strcmp(grupa->korisnici[i].nadimak, nalog->nadimak) == 0)
        {
            return grupa->korisnici[i].tipNaloga;
        }
    }

    return Nepostojeci();
}

void IspisTipa(int tip)
{
    switch(tip)
    {
    case 0:
        printf("Kreator");
        break;
    case 1:
        printf("Administrator");
        break;
    case 2:
        printf("Korisnik");
        break;
    }
}

void IspisGrupe(Grupa* grupa)
{
    printf("Grupa: %s\n", grupa->naziv);
    printf("Kod: %s\n", grupa->kod);
    printf("Maksimalni broj clanova: %d\n", grupa->maxClanova);
    printf("Clanovi (%d):\n", grupa->brojClanova);
    for(int i = 0; i < grupa->brojClanova; i++)
    {
        printf("%s (", grupa->korisnici[i].nadimak);
        IspisTipa(grupa->korisnici[i].tipNaloga);
        printf(")\n");
    }
}

NalogUGrupi* IzaberiKorisnika(Grupa* grupa)
{
    printf("Izaberite korisnika: ");
    for(int i = 0; i < grupa->brojClanova; i++)
    {
        printf("%d. %s (", i, grupa->korisnici[i].nadimak);
        IspisTipa(grupa->korisnici[i].tipNaloga);
        printf(")\n");
    }

    int izabranKorisnik = -1;

    while(izabranKorisnik < 0 || izabranKorisnik > grupa->brojClanova - 1)
    {
        printf("Izaberite korisnika (0-%d): ", grupa->brojClanova - 1);
        scanf("%d",&izabranKorisnik);
    }

    return &grupa->korisnici[izabranKorisnik];
}

Grupa NadjiGrupu(char* kod)
{
    FILE* file= fopen("grupe.txt","r+");
    if(file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return PraznaGrupa();
    }

    while(1)
    {
        Grupa grupa = UcitajGrupu(file);

        if(DaLiJePrazna(&grupa))
        {
            break;
        }

        if(strcmp(grupa.kod, kod) == 0)
        {
            fclose(file);
            return grupa;
        }
    }

    fclose(file);

    return PraznaGrupa();
}

Grupa IzaberiGrupu(Nalog* nalog)
{
    FILE* file= fopen("grupe.txt","r+");
    if(file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return PraznaGrupa();
    }

    printf("Izaberite grupu:\n");

    int brojNadjenihGrupa = 0;
    Grupa nadjeneGrupe[100];
    while(1)
    {
        Grupa grupa = UcitajGrupu(file);

        if(DaLiJePrazna(&grupa))
        {
            break;
        }

        int tip = KorisnikovTipUGrupi(&grupa, nalog);
        if(tip == Admin() || tip == Kreator())
        {
            printf("%d. %s\n", brojNadjenihGrupa, grupa.naziv);
            nadjeneGrupe[brojNadjenihGrupa] = grupa;
            brojNadjenihGrupa++;
        }
    }

    fclose(file);

    if(brojNadjenihGrupa == 0)
    {
        printf("Nemate grupa u kojima ste admin ili kreator.\n");
        return PraznaGrupa();
    }

    int izabranaGrupa = -1;

    while(izabranaGrupa < 0 || izabranaGrupa > brojNadjenihGrupa - 1)
    {
        printf("Izaberite grupu (0-%d): ", brojNadjenihGrupa - 1);
        scanf("%d",&izabranaGrupa);
    }

    return nadjeneGrupe[izabranaGrupa];
}

void IzmeniGrupu(Grupa* grupa)
{
    if(ObrisiGrupu(grupa))
    {
        DodajGrupu(grupa);
    }
}

int ObrisiGrupu(Grupa* grupa)
{

    rename("grupe.txt","staregrupe.txt");

    FILE* stariFile = fopen("staregrupe.txt", "r+");
    if(stariFile == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return 0;
    }


    while(1)
    {
        Grupa ucitanaGrupa = UcitajGrupu(stariFile);

        if(DaLiJePrazna(&ucitanaGrupa))
        {
            break;
        }


        if(strcmp(grupa->kod, ucitanaGrupa.kod) != 0)
        {
            DodajGrupu(&ucitanaGrupa);
        }
    }

    fclose(stariFile);

    remove("staregrupe.txt");

    return 1;
}

void IzbaciKorisnikaIzGrupe(Grupa* grupa, NalogUGrupi* nalogUGrupi)
{

    int pozicijaNaloga = 0;
    while(pozicijaNaloga < grupa->brojClanova)
    {
        if(strcmp(grupa->korisnici[pozicijaNaloga].nadimak, nalogUGrupi->nadimak) == 0)
        {
            break;
        }

        pozicijaNaloga++;
    }


    grupa->brojClanova--;


    for(int i = pozicijaNaloga; i < grupa->brojClanova; i++)
    {
        grupa->korisnici[i].tipNaloga = grupa->korisnici[i + 1].tipNaloga;
        strcpy(grupa->korisnici[i].nadimak, grupa->korisnici[i + 1].nadimak);
    }
}
