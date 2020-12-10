#include "DiscordClone.h"
#include "Nalog.h"
#include "Grupa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ProveriEmail(char* email)
{

    int i = 0;
    int pozicijaAt = -1;
    while (email[i] != '\0')
    {
        if(email[i] == '@')
        {
            pozicijaAt = i;
            break;
        }

        i++;
    }


    if (pozicijaAt < 1)
    {
        return 0;
    }

    int pozicijaTacke = -1;

    // Uvecaj brojac
    i++;

    while (email[i] != '\0')
    {
        // Ako nadjemo drugi @, znaci da je greska
        if (email[i] == '@')
        {
            return 0;
        }

        // Ako nadjemo tacku ODMAH iza @, javi gresku
        if (i == pozicijaAt + 1 && email[i] == '.')
        {
            return 0;
        }

        if (email[i] == '.')
        {

            // Greska, nasli smo 2 tacke, jednu pored druge
            if (i == pozicijaTacke + 1)
            {
                return 0;
            }

            pozicijaTacke = i;
        }

        i++;
    }


    if (pozicijaTacke == i - 1)
    {
        return 0;
    }

    return 1;
}

void Start()
{
    FILE* fileNalozi = fopen("nalozi.txt", "a");
    fclose(fileNalozi);

    FILE* fileGrupe = fopen("grupe.txt", "a");
    fclose(fileGrupe);

    Nalog ulogovan = PrazanNalog();
    while(1)
    {
        int izbor = Meni(ulogovan);

        switch(izbor)
        {
        case 0:

            return;
        case 1:
            Registracija();
            break;
        case 2:
            if(DaLiJePrazan(&ulogovan))
            {
                ulogovan = Login();
            }
            else
            {
                ulogovan = PrazanNalog();
            }

            break;
        case 3:
            Izmena(&ulogovan);
            break;
        case 4:

            if(Brisanje(&ulogovan))
            {
                ulogovan = PrazanNalog();
            }
            break;
        case 5:
            DodavanjeGrupe(&ulogovan);
            break;
        case 6:
            IzmenaGrupe(&ulogovan);
            break;
        case 7:
            BrisanjeGrupe(&ulogovan);
            break;
        case 8:
            UlazakUGrupu(&ulogovan);
            break;
        case 9:
            Prijatelji(&ulogovan);
        }
    }
}

int MeniPrijatelji()
{
    printf("************************************\n");
    printf("* 1. Pretraga naloga               *\n");
    printf("* 2. Dodavanje prijatelja          *\n");
    printf("* 3. Prikaz prijatelja             *\n");
    printf("*                                  *\n");
    printf("* 0. Povratak na glavni meni       *\n");
    printf("************************************\n");

    int i = -1;

    IzprazniInput();

    while (i < 0 || i > 3)
    {
        printf(">");
        scanf("%d", &i);
    }

    return i;
}

void PretragaNaloga()
{
    IzprazniInput();
    printf("Unesite naziv ili deo naziva naloga koji trazite: ");
    char naziv[100];
    gets(naziv);

    PrikaziNaloge(naziv);
}

void DodavanjePrijatelja(Nalog* nalog)
{
    IzprazniInput();
    printf("Unesite nadimak prijatelja kojeg zelite da dodate: ");
    char nadimak[100];
    gets(nadimak);

    Nalog prijatelj = NadjiNalog(nadimak, 1, 0);
    if(DaLiJePrazan(&prijatelj))
    {
        printf("Ne postoji nalog sa tim nadimkom\n");
        return;
    }

    if(strcmp(nadimak, nalog->nadimak) == 0)
    {
        printf("Ne mozete dodati samog sebe za prijatelja\n");
        return;
    }

    DodajPrijatelja(nalog, nadimak);
}

void PrikazPrijatelja(Nalog* nalog)
{
    if(nalog->brojPrijatelja == 0)
    {
        printf("Nemate prijatelja.\n");
        return;
    }

    printf("Vasi prijatelji:\n");

    for(int i = 0; i < nalog->brojPrijatelja; i++)
    {
        printf("%s\n", nalog->prijatelji[i]);
    }
}

void Prijatelji(Nalog* nalog)
{
    while(1)
    {
        int izbor = MeniPrijatelji();

        switch(izbor)
        {
        case 1:
            PretragaNaloga();
            break;
        case 2:
            DodavanjePrijatelja(nalog);
            break;
        case 3:
            PrikazPrijatelja(nalog);
            break;
        case 0:
            return;
        }
    }
}

void UlazakUGrupu(Nalog* nalog)
{
    IzprazniInput();
    printf("Unesite kod za pristup grupi: ");
    char kod[100];
    gets(kod);

    Grupa grupa = NadjiGrupu(kod);

    if(DaLiJePrazna(&grupa))
    {
        printf("Ne postoji grupa sa tim kodom");
        return;
    }

    if(grupa.brojClanova == grupa.maxClanova)
    {
        printf("Grupa je popunjena, nije moguce dodati nove clanove");
        return;
    }

    if(KorisnikovTipUGrupi(&grupa, nalog) != Nepostojeci())
    {
        printf("Vec ste clan ove grupe");
        return;
    }

    PridruziSeGrupi(&grupa, nalog);
}

int MeniGrupa(int dozvoljenIzmena)
{
    int iMax = 1;
    printf("************************************\n");
    printf("* 1. Izmeni naziv                  *\n");

    if(dozvoljenIzmena)
    {
        printf("* 2. Izmeni clanove                *\n");
        iMax = 2;
    }

    printf("*                                  *\n");
    printf("* 0. Povratak na glavni meni       *\n");
    printf("************************************\n");

    int i;

    while (i < 0 || i > iMax)
    {
        printf(">");
        scanf("%d", &i);
    }

    return i;
}

void BrisanjeGrupe(Nalog* nalog)
{
    Grupa grupa = IzaberiGrupu(nalog);

    if(DaLiJePrazna(&grupa))
    {
        return;
    }

    printf("Da li zelite da obrisete grupu (y/n): ");

    while(1)
    {
        IzprazniInput();
        char d;
        scanf("%c",&d);

        if(d=='y' || d=='Y')
        {
            ObrisiGrupu(&grupa);
            return;
        }
        else if(d=='n' || d=='N')
        {
            return;
        }
    }
}

void IzmenaGrupe(Nalog* nalog)
{
    Grupa grupa = IzaberiGrupu(nalog);

    if(DaLiJePrazna(&grupa))
    {
        return;
    }

    int tipUGrupi = KorisnikovTipUGrupi(&grupa, nalog);
    int dozvoljenIzmena = tipUGrupi == Admin() || tipUGrupi == Kreator();
    while(1)
    {
        printf("************************************\n");
        IspisGrupe(&grupa);
        int izbor = MeniGrupa(dozvoljenIzmena);

        switch(izbor)
        {

        case 1:
            IzprazniInput();
            printf("Koji je novi naziv grupe: ");
            gets(grupa.naziv);
            break;
        case 2:
            IzmenaKorisnika(nalog, &grupa, tipUGrupi);
            break;


        case 0:
            IzmeniGrupu(&grupa);
            return;
        }
    }
}

int MeniKorisnikUGrupi(int dozvoljenoIzbacivanje)
{
    int iMax = 1;
    printf("************************************\n");
    printf("* 1. Izmeni tip korisnika          *\n");

    if(dozvoljenoIzbacivanje)
    {
        printf("* 2. izbaci iz grupe           *\n");
        iMax = 2;
    }

    printf("*                                  *\n");
    printf("* 0. Povratak na prethodni meni    *\n");
    printf("************************************\n");

    int i;

    while (i < 0 || i > iMax)
    {
        printf(">");
        scanf("%d", &i);
    }

    return i;
}

void IzmeniTipKorisnika(NalogUGrupi* izabraniNalog)
{
    printf("Izaberite novi tip korisnika: \n");
    printf("1. Admin: \n");
    printf("2. Korisnik: \n");

    int tip = -1;
    while (tip < 1 || tip > 2)
    {
        printf(">");
        scanf("%d", &tip);
    }

    izabraniNalog->tipNaloga = tip;
}

void IzmenaKorisnika(Nalog* nalog, Grupa* grupa, int tipUGrupi)
{
    NalogUGrupi* izabraniNalog = IzaberiKorisnika(grupa);

    if(strcmp(nalog->nadimak, izabraniNalog->nadimak) == 0)
    {
        printf("Ne mozete menjati svoje parametre u grupi\n\n");
        return;
    }

    if(izabraniNalog->tipNaloga == Kreator())
    {
        printf("Ne mozete menjati parametre kreatora grupe\n\n");
        return;
    }

    int dozvoljenoIzbacivanje = tipUGrupi < izabraniNalog->tipNaloga;

    int izbor = MeniKorisnikUGrupi(dozvoljenoIzbacivanje);

    switch(izbor)
    {
    case 1:
        IzmeniTipKorisnika(izabraniNalog);
        return;
    case 2:
        IzbaciKorisnikaIzGrupe(grupa, izabraniNalog);
        return;
    case 0:
        return;
    }
}

void DodavanjeGrupe(Nalog* kreator)
{
    Grupa grupa;
    IzprazniInput();

    printf("Dodavanje grupe\n");
    printf("Unesite naizv grupe: ");
    gets(grupa.naziv);


    srand(time(NULL));
    for(int i = 0; i < 5; i++)
    {
        grupa.kod[i] = 'A' + (rand() % 26);
    }

    printf("Generisani kod: %s\n", grupa.kod);

	int maxBrojClanova = 0;
	while(maxBrojClanova < 2 || maxBrojClanova > 100)
	{
		printf("Unesite maksimalni broj clanova u grupi (2-100): ");

		scanf("%d",&maxBrojClanova);
	}

	grupa.maxClanova = maxBrojClanova;


    strcpy(grupa.korisnici[0].nadimak, kreator->nadimak);
    grupa.korisnici[0].tipNaloga = Kreator();
	grupa.brojClanova = 1;

	DodajGrupu(&grupa);
}

int Brisanje(Nalog* nalog)
{
    printf("Da li zelite da obrisete nalog (y/n): ");

    while(1)
    {
        IzprazniInput();
        char d;
        scanf("%c",&d);

        if(d=='y' || d=='Y')
        {
            ObrisiNalog(nalog->nadimak);
            return 1;
        }
        else if(d=='n' || d=='N')
        {
            return 0;
        }
    }
}

int Meni(Nalog nalog)
{
    printf("\n");
    int iMax = 2;
    if(!DaLiJePrazan(&nalog))
    {
        printf("Ulogovan korisnik: %s\n", nalog.nadimak);
        iMax = 9;
    }

    printf("************************************\n");
    printf("* Uzaberite uslugu:                *\n");
    printf("* 1. Registracija                  *\n");

    if(DaLiJePrazan(&nalog))
    {
        printf("* 2. Ulogujte se                   *\n");
    }
    else
    {
        printf("* 2. Izlogujte se                  *\n");
        printf("* 3. Izmenite nalog                *\n");
        printf("* 4. Obrisite nalog                *\n");
        printf("*                                  *\n");
        printf("* 5. Napravite grupu               *\n");
        printf("* 6. Izmenite grupu                *\n");
        printf("* 7. Obrisite grupu                *\n");
        printf("* 8. Ulazak u grupu                *\n");
        printf("* 9. Prijatelji                    *\n");
    }

    printf("*                                  *\n");
    printf("* 0. Izadjite iz programa          *\n");
    printf("************************************\n");


    int i = -1;

    while (i < 0 || i > iMax)
    {
        printf(">");
        scanf("%d", &i);
    }

    return i;
}

void UnesiEmail(Nalog* nalog)
{
    while (1)
    {
        printf("Unesite Vasu email adresu: ");
        gets(nalog->email);


        if (ProveriEmail(nalog->email))
        {

            Nalog trazen = NadjiNalog(nalog->email, 0, 1);
            if(DaLiJePrazan(&trazen))
            {
                return;
            }

            printf("Email vec postoji, molimo izaberite drugi");
        }
        else
        {
            printf("Niste dobro uneli mejl!! Probajte opet!\n");
        }
    }
}

void UnesiLozinku(Nalog* nalog)
{
    char lozinka[100];
    while(1)
    {
        printf("Koja je vasa lozinka: ");
        gets(nalog->lozinka);

        printf("Ponovo unesite lozinku: ");
        gets(lozinka);


        if (strcmp(lozinka, nalog->lozinka) == 0)
        {
            return;
        }

        printf("Niste dobro uneli lozinku! Probajte opet. \n");
    }
}

void UnesiNadimak(Nalog* nalog)
{
    IzprazniInput();
    while(1)
    {
        printf("Koji je Vas nadimak: ");
        gets(nalog->nadimak);


        Nalog trazen = NadjiNalog(nalog->nadimak, 1, 0);
        if(DaLiJePrazan(&trazen))
        {
            return;
        }

        printf("Nadimak vec postoji, molimo izaberite drugi");
    }
}

void Izmena(Nalog* nalog)
{
    char stariNadimak[100];
    strcpy(stariNadimak, nalog->nadimak);

    while(1)
    {
        printf("***************************\n");
        printf("* Izmena naloga           *\n");
        printf("* 1. Ime                  *\n");
        printf("* 2. Prezime              *\n");
        printf("* 3. Mejl adresa          *\n");
        printf("* 4. Nadimak              *\n");
        printf("* 5. Lozinka              *\n");
        printf("* 0. Izlaz na glavni meni *\n");
        printf("***************************\n");
        printf(">");

        IzprazniInput();
        int t;
        scanf("%i",&t);
        if (t < 0 || t > 5)
        {
            continue;
        }

        switch(t)
        {
        case 0:
            IzmeniNalog(stariNadimak, nalog);
            return;
        case 1:
            IzprazniInput();
            printf("Koje je Vase ime: ");
            gets(nalog->ime);
            break;
        case 2:
            IzprazniInput();
            printf("Koje je Vase prezime: ");
            gets(nalog->prezime);
            break;
        case 3:
            UnesiEmail(nalog);
            break;
        case 4:
            UnesiNadimak(nalog);
            break;
        case 5:
            UnesiLozinku(nalog);
            break;
        }
    }
 }

void Registracija()
{
    Nalog nalog;

    UnesiNadimak(&nalog);

    UnesiEmail(&nalog);

    IzprazniInput();
    printf("Koje je Vase ime: ");
    gets(nalog.ime);

    IzprazniInput();
    printf("Koje je Vase prezime: ");
    gets(nalog.prezime);

    UnesiLozinku(&nalog);

    nalog.brojPrijatelja = 0;

    DodajNalog(&nalog);
}

Nalog Login()
{
    IzprazniInput();
    printf("Unesite nadimak ili email: ");
    char nadimakIliEmail[100];
    gets(nadimakIliEmail);

    char lozinka[100];
    printf("Unesite lozinku: ");
    gets(lozinka);

    Nalog nalog = NadjiNalog(nadimakIliEmail, 1, 1);
    if(DaLiJePrazan(&nalog) || strcmp(lozinka, nalog.lozinka) != 0)
    {
        printf("Niste dobro uneli mejl,nadimak ili lozinku!");
        return PrazanNalog();
    }

    return nalog;
}

void IzprazniInput()
    {
    fseek (stdin, 0, SEEK_END);
}

