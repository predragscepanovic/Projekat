#include "nalog.h"
#include <stdio.h>
#include <string.h>

void DodajNalog(Nalog* nalog)
{
    FILE* file = fopen("nalozi.txt", "a");
    if (file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return;
    }


    fseek(file, 0, SEEK_END);


    fprintf(file, "%s", nalog->ime);
    fputc(' ', file);
    fprintf(file, "%s", nalog->prezime);
    fputc(' ', file);
    fprintf(file, "%s", nalog->email);
    fputc(' ', file);
    fprintf(file, "%s", nalog->nadimak);
    fputc(' ', file);
    fprintf(file, "%s", nalog->lozinka);
    fprintf(file, " ");

    fprintf(file, "%d", nalog->brojPrijatelja);
    fprintf(file, " ");

    for(int i = 0; i < nalog->brojPrijatelja; i++)
    {
        fprintf(file, "%s", nalog->prijatelji[i]);
    }

    fclose(file);
}

Nalog UcitajNalog(FILE* file)
{
    Nalog nalog;
    fscanf(file,"%s", nalog.ime);

    if(feof(file))
    {
        return PrazanNalog();
    }

    fgetc(file);
    fscanf(file,"%s", nalog.prezime);
    fgetc(file);
    fscanf(file,"%s", nalog.email);
    fgetc(file);
    fscanf(file,"%s", nalog.nadimak);
    fgetc(file);
    fscanf(file,"%s", nalog.lozinka);
    fgetc(file);
    fscanf(file,"%d", &nalog.brojPrijatelja);
    fgetc(file);
    for(int i = 0; i < nalog.brojPrijatelja; i++)
    {
        fscanf(file,"%s", nalog.prijatelji[i]);
        fgetc(file);
    }

    return nalog;
}

void DodajPrijatelja(Nalog* nalog, char* nadimak)
{
    strcpy(nalog->prijatelji[nalog->brojPrijatelja], nadimak);
    nalog->brojPrijatelja++;

    IzmeniNalog(nalog->nadimak, nalog);
}

void IzmeniNalog(char* nadimak, Nalog* izmenjenNalog)
{
    if(ObrisiNalog(nadimak))
    {
        DodajNalog(izmenjenNalog);
    }
}

int ObrisiNalog(char* nadimak)
{

    rename("nalozi.txt","starinalozi.txt");

    FILE* stariFile = fopen("starinalozi.txt", "r+");
    if(stariFile == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return 0;
    }


    while(1)
    {
        Nalog nalog = UcitajNalog(stariFile);

        if(DaLiJePrazan(&nalog))
        {
            break;
        }


        if(strcmp(nadimak, nalog.nadimak) != 0)
        {
            DodajNalog(&nalog);
        }
    }

    fclose(stariFile);

    remove("starinalozi.txt");

    return 1;
}

Nalog PrazanNalog()
{

    Nalog nalog;
    nalog.nadimak[0] = '\0';
    return nalog;
}

int DaLiJePrazan(Nalog* nalog)
{
    return nalog->nadimak[0] == '\0';
}

void PrikaziNaloge(char* deoNadimka)
{
    FILE* file= fopen("nalozi.txt","r+");
    if(file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return;
    }

    while(1)
    {
        Nalog nalog = UcitajNalog(file);


        if(DaLiJePrazan(&nalog))
        {
            break;
        }


        if(strstr(nalog.nadimak, deoNadimka) != NULL)
        {
            printf("%s\n", nalog.nadimak);
        }
    }

    fclose(file);
}

Nalog NadjiNalog(char* nadimakIliEmail, int proveriNadimak, int proveriEmail)
{
    FILE* file= fopen("nalozi.txt","r+");
    if(file == NULL)
    {
        printf("Nije moguce otvoriti fajl, molimo Vas pokusajte ponovo.\n");
        return PrazanNalog();
    }

    while(1)
    {
        Nalog nalog = UcitajNalog(file);


        if(DaLiJePrazan(&nalog))
        {
            fclose(file);
            return PrazanNalog();
        }


        if((proveriNadimak && strcmp(nadimakIliEmail, nalog.nadimak) == 0) || (proveriEmail && strcmp(nadimakIliEmail, nalog.email) == 0))
        {
            fclose(file);
            return nalog;
        }
    }
}
