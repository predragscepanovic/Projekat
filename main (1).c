#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dodajNalog(char* e[])
{

    printf("Ime: ");
    char ime[50];
    gets(ime);
    printf("Prezime: ");
    char prezime[50];
    gets(prezime);
    printf("Email: ");
    char email[50];
    gets(email);
    char username[50];
    printf("Korisnicko ime: ");
    gets(username);
    char sifra[50];
    printf("Sifra: ");
    gets(sifra);
    char sifra1[50];
    printf("Potvrdi sifru: ");
    if(strcmp(sifra, sifra1)!=0)
    {
        printf("Sifre se ne poklapaju\n");
        printf("Potvrdi sifru: ");
        gets(sifra1);
    }
    FILE* nalogFajl = fopen("DiscordAccounts.txt", "a");
    fprintf(nalogFajl, "%s %s %s %s %s\n", ime, prezime, email, username, sifra);
    fclose(nalogFajl);
    strcpy(e, email);
}

void Login(char* e[])
{
    int w = 0;
    FILE* nalogFajl = fopen("DiscordAccounts.txt", "r");
    char email[100];
    while(w==0)
    {

        memset(email, 0, sizeof(char)*100);
        printf("Email: ");
        gets(email);
        char sifra[100]= {0};
        printf("Sifra: ");
        gets(sifra);

        fseek(nalogFajl, 0, SEEK_SET);
        char c[100]= {0};




        while(!feof(nalogFajl))
        {
            int broj = 0;
            int i = 0;
            while(broj!=2)
            {
                fscanf(nalogFajl, "%s", c);
                ++broj;
            }
            fscanf(nalogFajl, "%s", c);

            if(strcmp(email, c)==0)
            {
                ++i;

            }
            fscanf(nalogFajl, "%s", c);
            fscanf(nalogFajl, "%s", c);
            if(i!=0)
            {

                if(strcmp(sifra, c)==0)
                {
                    ++w;
                    break;
                }
                else
                {
                    printf("Uneli ste pogresnu sifru ili email!\n");
                    break;
                }
            }

        }
        if(w==0)
        {
            printf("Uneli ste pogresnu sifru ili email!\n");

        }

    }
    fclose(nalogFajl);
    strcpy(e, email);
}


void logout(char* e[])
{

    memset(e, 0, sizeof(char)*100);

}

void izmena(char email[])
{
    int i = 0;
    while(1==1)
    {
        printf("Sta zelite da izmenite?\n");
        printf("1. Ime\n");
        printf("2. Prezime\n");
        printf("3. email\n");
        printf("4. Korisnicko ime\n");
        printf("5. Sifru\n");
        printf("6. Kraj\n");

        scanf("%i", &i);
        getchar();
        if(i==6)
        {
            break;
        }
        FILE* nalogFajl = fopen("DiscordAccounts.txt", "r");
        fseek(nalogFajl, 0, SEEK_SET);
        char e[160]= {0};
        FILE* edit = fopen("edit.txt", "w");
        while(fgets(e, 160, nalogFajl)!=NULL)
        {
            char editString[50]= {0}, mail[50]= {0}, ime[50]= {0}, prezime[50]= {0}, sifra[50]= {0}, korisnickoIme[50]= {0};
            sscanf(e, "%s %s %s %s %s", ime, prezime, mail, korisnickoIme, sifra);
            printf("%s\n", mail);
            if(strcmp(email, mail)==0)
            {
                gets(editString);

                if(i==1)
                {

                    fprintf(edit, "%s %s %s %s %s\n", editString, prezime, mail, korisnickoIme, sifra);
                    continue;
                }
                if(i==2)
                {

                    fprintf(edit, "%s %s %s %s %s\n", ime, editString, mail, korisnickoIme, sifra);
                    continue;
                }
                if(i==3)
                {

                    fprintf(edit, "%s %s %s %s %s\n", ime, prezime, editString, korisnickoIme, sifra);
                    continue;
                }
                if(i==4)
                {

                    fprintf(edit, "%s %s %s %s %s\n", ime, prezime, mail, editString, sifra);
                    continue;
                }
                if(i==5)
                {

                    fprintf(edit, "%s %s %s %s %s\n", ime, prezime, mail, korisnickoIme, editString);
                    continue;
                }
                continue;
            }
            fprintf(edit, "%s", e);
        }
        fclose(nalogFajl);
        fclose(edit);
        remove("DiscordAccounts.txt");
        rename("edit.txt", "DiscordAccounts.txt");
    }

}

void izbrisiProfil(char email[])
{
    FILE* nalogFajl = fopen("DiscordAccounts.txt", "r");
    fseek(nalogFajl, 0, SEEK_SET);
    FILE* edit = fopen("edit.txt", "w");
    char e[160]= {0};
    while(fgets(e, 160, nalogFajl)!=NULL)
    {
        char mail[50]= {0}, ime[50]= {0}, prezime[50]= {0}, sifra[50]= {0}, korisnickoIme[50]= {0};
        sscanf(e, "%s %s %s %s %s", ime, prezime, mail, korisnickoIme, sifra);
        if(strcmp(email, mail)==0)
        {
            continue;
        }
        fprintf(edit, e);
    }
    fclose(nalogFajl);
    fclose(edit);
    remove("DiscordAccounts.txt");
    rename("edit.txt", "DiscordAccounts.txt");
}

void meni()
{
    char email[100] = {0};

    int i=0;
    while(1==1)
    {
        if(strlen(email)==0)
        {
            printf("1. Dodaj novi nalog\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            scanf("%i", &i);
            getchar();
            if(i==1)
            {
                dodajNalog(&email);

            }
            if(i==2)
            {
                Login(&email);

            }
            if(i==3)
            {
                break;
            }
        }

        else
        {

            printf("1. Edit profile\n");
            printf("2. Delete profile\n");
            printf("3. Logout\n");
            scanf("%i", &i);
            getchar();
            if(i==1)
            {
                izmena(email);

            }
            if(i==2)
            {
                izbrisiProfil(email);
                logout(&email);
            }
            if(i==3)
            {
                logout(&email);
            }
        }
    }
}




int main()
{
    meni();

}
