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



void stats(const char *directory)
{
    struct dirent **namelist;
    
    /* set the position of file in a list */  
    int pos=0; 
    
    struct stat st;
    char name_header[15] = "nom";
    char date_header[15] = "date";
    char size_header[15] = "taille";
    
    /* Resetting files counter */
    int total_files = 0; 
    
    float  total_size = 0  
    float size = 0;
    
    /*Header tab : name - Date of latest modifications - files size */
    printf ("\n");
    printf (" |%s                     |%s               |%s\n",name_header,date_header,size_header);
    printf ("-|------------------------|-------------------|------------------");
    printf ("\n");
    
    /* Exploring a directory and returning number of files from current directory */
    int n = scandir(directory, &namelist,NULL,alphasort);
    
    /* Returning -1 in case of error */
    if (n < 0)
    {
        perror("scandir");
    }
    else 
    {
        while (pos<n)
        {
            stat (namelist[pos]->d_name, &st);
            time_t t = st.st_atime;
            struct tm tm = *localtime (&t);
            char date[32]; /* creating a format date */
            char name[32];
            strftime (date, sizeof date, "%d/%m/%Y %H:%M:%S", &tm);
            float size = st.st_size;
            
             /*Not showing  "." , ".." and ".DC_Store" files in the tab*/
            if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0 && strcmp(namelist[i]->d_name, ".DS_Store")!=0 )
            {
                if (strlen(namelist[i]->d_name)>10)
                {
                if (r > 1024*1024*1024 && size< 1099511627776)
                {
                    printf ("%25s |%10s| %1.2f G\n",strncpy(name,namelist[i]->d_name,20),date,size/(1024*1024*1024));
                }
                if (r > 1024*1024 && r < 1024*1024*1024)
                {
                    printf ("%25s |%10s| %1.2f M\n",strncpy(name,namelist[i]->d_name,20),date,size/(1024*1024));
                }
                if (r > 1024 && r < 1024*1024)
                {
                    printf ("%25s |%10s| %1.2f K\n",strncpy(name,namelist[i]->d_name,20),date,size/1024);
                }
                if (r < 1024)
                {
                    printf ("%25s |%10s| %1.2f B\n",strncpy(name,namelist[i]->d_name,20),date,size);
                }
                }
                total_files++;
                total_size+=size;
            }
            ++pos;
        }
        
        /* footer tab */
        printf ("-|------------------------|-------------------|------------------");
        printf ("\n");
        
        /*Printing a summary of the directory */
        printf ("Résumé\n");
        printf (" ------\n");
        printf ("\n");
      
        if (total_size > 1024*1024*1024 && total_size < 1099511627776)
        {
            printf ("Taille totale du dossier : %1.2f G\n",total_size/(1024*1024*1024));
        }
        if (total_size > 1024*1024 && total_size < 1024*1024*1024)
        {
            printf ("Taille totale du dossier : %1.2f M\n",total_size/(1024*1024));
        }
        if (total_size > 1024 && total_size < 1024*1024)
        {
            printf ("Taille totale du dossier : %1.2f K\n",total_size/1024);
        }
        if (total_size < 1024)
        {
            printf ("Taille totale du dossier : %1.2f B\n",total_size);
        }
        printf ("Nombre total de fichiers : %d\n",total_files);
    }
}

 
