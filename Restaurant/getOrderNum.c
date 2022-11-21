#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    int fCt = 0;

    struct dirent* dir;
    DIR* d;
    if (argc != 2) { perror("error number of argument"); exit(1); } //checking if there are not 2 parameters
    strcat(argv[1], "_Order");
    d = opendir(argv[1]); //opening the restaurant directory
    if (d == NULL) { printf("%s was not opened!\n", argv[1]); exit(0); } //checking if the directory failed to open
    while ((dir = readdir(d)) != NULL) { // a loop that counts the number of files in the directory
        if (dir != NULL)
            fCt++;
    }
    printf("%d Orders\n", fCt - 2);
    return 0;
}