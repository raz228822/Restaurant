#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[])
{
    char buffer[256];
    int fd, rbytes;
    if (argc != 2) { perror("wrong number of prameters"); exit(1); } // checking if there are not 2 parameters
    if ((fd = open(argv[1], O_RDONLY)) == -1) { perror("error opening file"); exit(1); }
    while ((rbytes = read(fd, buffer, 255)) > 0) //reading from the file untill the end of the file
    {// add fail test
        buffer[255] = '\0'; //converting array of chars to string
        printf("%s", buffer); //printing the buffer
        memset(buffer, 0, sizeof(buffer)); //resetting the buffer

    }
    close(fd); //closing file's grip
    return 0;
}