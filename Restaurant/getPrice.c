#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd, i = 0, j, rbytes, price = 0;
    char buffer[1024], * dishName, onlyName[256];
    for (j = 3; j < argc; j++) { //a loop for dishes with 2 or more words
        strcat(argv[2], " ");
        strcat(argv[2], argv[j]);
    }
    if (argc < 3) { perror("error number of argument"); exit(1); } //checking if there are less than 3 parameters
    if ((fd = open(argv[1], O_RDONLY, 0644)) == -1) { printf("Restaurant not found!\n"); exit(1); }
    while ((rbytes = read(fd, buffer, 1024)) > 0) { //reading from the file untill the end of the file in order to find the order's price
        dishName = strstr(buffer, argv[2]); //getting the pointer of the substring argv[2]
        if (dishName != NULL) {
            while (isdigit(dishName[i]) == 0) { //ignoring the letters/dots
                i++;
            }
            while (isdigit(dishName[i]) != 0) { //calculating the price
                price *= 10;
                price += (dishName[i] - '0');
                i++;
            }
            break;
        }
        else {
            printf("dish was not found\n");
            return 0;
        }
    }
    printf("%d NIS\n", price);
    close(fd); //closing file's grip
    return 0;
}