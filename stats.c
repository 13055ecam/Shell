#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <inttypes.h>
#include <wchar.h>
#include "stats.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


/* Ne compte pas la taille des dossiers mais seulement des fichiers dans les dossiers !*/


void stats()
{
    struct dirent **namelist;
    int n;
    int i=0;
    struct stat st;
    char nom[15] = "nom";
    char date[15] = "date";
    char taille[15] = "taille";
    int nbr = 0; /* nombre de fichier*/
    float  v=0,r,ptr;
    
    printf ("\n");
    printf (" |%s                     |%s               |%s\n",nom,date,taille);
    printf ("-|------------------------|-------------------|------------------");
    printf ("\n");
    n = scandir(".", &namelist,NULL,alphasort);
    if (n < 0)
    {
        perror("scandir");
    }
    else 
    {
        while (i<n)
        {
            stat (namelist[i]->d_name, &st);
            time_t t = st.st_atime;
            struct tm tm = *localtime (&t);
            char s[32];
            char name[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
            float r = st.st_size;
            /**
             int err;
             regex_t preg;
             const char *str_request = namelist[i]->d_name;
             const char *str_regex = ".*\\.pdf";
             err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
             if (err == 0)
             {
             int match;
             match = regexec (&preg, str_request, 0, NULL, 0);
             regfree (&preg);
             if (match == 0)
             {
             printf ("type pdf");
             }
             else
             {
             printf ("Inconnu");
             }
             }
             **/ 
            
            if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0 && strcmp(namelist[i]->d_name, ".DS_Store")!=0 )
            {
                if (strlen(namelist[i]->d_name)>10)
                {
                /* nom - date de la dernière modif - taille du fichier*/
                if (r > 1024*1024*1024 && r < 1099511627776)
                {
                    printf ("%25s |%10s| %1.2f G\n",strncpy(name,namelist[i]->d_name,20),s,r/(1024*1024*1024));
                }
                if (r > 1024*1024 && r < 1024*1024*1024)
                {
                    printf ("%25s |%10s| %1.2f M\n",strncpy(name,namelist[i]->d_name,20),s,r/(1024*1024));
                }
                if (r > 1024 && r < 1024*1024)
                {
                    printf ("%25s |%10s| %1.2f K\n",strncpy(name,namelist[i]->d_name,20),s,r/1024);
                }
                if (r < 1024)
                {
                    printf ("%25s |%10s| %1.2f B\n",strncpy(name,namelist[i]->d_name,20),s,r);
                }
                }
                nbr++;
                v+=r;
            }
            ++i;
        }
        printf ("-|------------------------|-------------------|------------------");
        printf ("\n");
        printf ("Résumé\n");
        printf (" ------\n");
        printf ("\n");
        
        /* taille totale du dossier */
        
        if (v > 1024*1024*1024 && v < 1099511627776)
        {
            printf ("Taille totale du dossier : %1.2f G\n",v/(1024*1024*1024));
        }
        if (v > 1024*1024 && v < 1024*1024*1024)
        {
            printf ("Taille totale du dossier : %1.2f M\n",v/(1024*1024));
        }
        if (v > 1024 && v < 1024*1024)
        {
            printf ("Taille totale du dossier : %1.2f K\n",v/1024);
        }
        if (v < 1024)
        {
            printf ("Taille totale du dossier : %1.2f B\n",v);
        }
        printf ("Nombre total de fichiers : %d\n",nbr);
    }
}

 
