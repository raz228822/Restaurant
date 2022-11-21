#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 1) { perror("error with number of parameters"); exit(1); } //checking if there is not only 1 parameter;
    printf("Goodbye\n");
    return 0;
}