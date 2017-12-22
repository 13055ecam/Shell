#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shrink.h"

int MIN_SIZE = 0;

/* Seek the zip executable file in every directory in the $PATH, and returns
 * the location of this executable. */
char *find_zip_executable() {
    char *path = getenv("PATH");
    char zip[] = "/zip";
    size_t zip_length = 4;

    char *dir = strtok(path, ":");
    while (dir != NULL) {
        // for every directory in the path
        // look for the zip executable
        size_t dir_length = strlen(dir);
        char *exec = malloc(zip_length + dir_length + 1);
        if (exec == NULL) {
            perror("Cannot allocate memory");
            return NULL;
        }
        exec[0] = '\0'; // ensure this is a new string for strcat
        strcat(exec, dir);
        strcat(exec, zip);
        if (access(exec, R_OK|X_OK) != -1) {
            // if the zip executable is found
            return exec;
        }
        free(exec);
        dir = strtok(NULL, ":");
    }
    return NULL;
}


/* Auxiliary function of find_compressible() to filter the files by size. */
int filter(const struct dirent * dir) {
    struct stat st;
    int err = stat(dir->d_name, &st);
    if (err == -1) {
        perror("filter");
        return 0;
    }
    if (st.st_size > MIN_SIZE)
        return 1;
    return 0;
}


/* List every file stored in the current directory which are larger than 500 MiB
 * The function returns the number of element passing the filter `elem'.
 * `relist' is filled by the function. */
int find_compressible(struct dirent ***retlist) {
    struct stat st;

    int elem = scandir(".", &(*retlist), filter, alphasort);
    if (elem == -1) {
        perror("scandir");
        return -1;
    }
    return elem;
}


/* Call the zip executable on every file contained in retlist. There are an
 * `entries' number of file.
 * The zip executable is located at the adress `zip_executable'. */
int zip_files(struct dirent ***retlist, int entries , char *zip_executable) {
    char filename[255] = "\0";
    char extension[] = ".zip";

    for (int i = 0; i < entries; i++) {
        filename[0] = '\0';
        strcat(filename, (*retlist)[i]->d_name);
        strcat(filename, extension);
        pid_t pid = fork();
        if (pid == -1) {
            perror("Cannot fork() a process");
            return -1;
        } else if (pid != 0) {
            int status = 0;
            waitpid(pid, &status, 0);
            if (!WIFEXITED(status)) {
                perror("The zip process exited abnormally");
                return -1;
            }
        } else {
            const char *argv[4] = {
                (const char *) zip_executable,         // /bin/zip
                (const char *) filename,               // myBill.pdf.zip
                (const char *) (*retlist)[i]->d_name,  // myBill.pdf
                (const char *) NULL
            };
            int err = execv(argv[0], (char *const *)argv);
            if (err == -1) {
                // let's be clear that this code should never be reached
                // or there is something really wrong with the system.
                perror("Cannot execute the zip executable");
                exit(1);
            }
        }
    }
    return 0;
}


int shrink(char argv[25][50]) {
    int min_size = atoi(argv[1]);
    if (min_size < 1024 * 1024) { // at least 1MiB
        fprintf(stderr, "Unaccepted minimal shrink size.\n");
        return EXIT_FAILURE;
    }
    char *file;
    file = find_zip_executable();
    if (file == NULL) {
        perror("Could not find the zip executable in the path");
        return EXIT_FAILURE;
    }
    struct dirent **retlist;
    int entries = find_compressible(&retlist);
    if (entries < 0) {
        perror("Could not list the compressible files");
        return EXIT_FAILURE;
    }
    zip_files(&retlist, entries, file);
    free(file);
    for (int i = 0; i < entries; i++) {
        if (retlist[i] != NULL) free(retlist[i]);
    }
    if (retlist != NULL) free(retlist);
    return EXIT_SUCCESS;
}
