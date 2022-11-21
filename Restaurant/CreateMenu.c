#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd, wbytes, i, count = 2, j, k = 0, dots;
    char typeDish[256], dish[256], dishName[256], price[256], temp = 'a', * dest, * order = "_Order";
    if (argc != 3) { perror("wrong number of prameters"); exit(1); } // checking if there are not 3 parameters
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777); //opening a file
    if (wbytes = write(fd, " ", 1) == -1) { perror("write"); exit(1); }
    if (wbytes = write(fd, argv[1], strlen(argv[1])) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
    if (wbytes = write(fd, " Menu\n", 6) == -1) { perror("write"); exit(1); }//writing to a file + checking if it was succeeded
    for (i = 0; i < atoi(argv[2]); i++) { // a loop that gets from the user the type dishes + dishes to the menu
    //and writing into the file
        if (wbytes = write(fd, "\n ", 2) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
        if (wbytes = write(fd, &temp, 1) == -1) { perror("write"); exit(1); }
        if (wbytes = write(fd, ". ", 2) == -1) { perror("write"); exit(1); }
        printf("Insert Type Dish %c : \n", temp);
        temp++; //getting the next letter
        fgets(typeDish, 256, stdin); //getting type dish from the user
        if (wbytes = write(fd, typeDish, strlen(typeDish)) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
        printf("Insert dish name 1 : \n");
        fgets(dish, 256, stdin); //getting the first dish
        while (strcmp(dish, "Stop\n") != 0) { //a loop for getting the dishes until getting 'Stop'
            memset(dishName, 0, sizeof(dishName)); //resetting the char array
            if (wbytes = write(fd, "   ", 3) == -1) { perror("write"); exit(1); }
            for (j = 0; j < strlen(dish); j++) {//a loop that splits the dish with its' price to a 2 seperate arrays of chars
                if (isdigit(dish[j]) == 0)
                    dishName[j] = dish[j];
                else {
                    price[k] = dish[j];
                    k++;
                }
            }
            dishName[strlen(dishName) - 1] = '\0'; //converting an array of chars to string
            price[k] = '\0'; //converting an array of chars to string
            k = 0;
            dots = 30 - strlen(dishName); //gets the amount of dots needed in the row
            if (wbytes = write(fd, dishName, strlen(dishName)) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
            for (j = 0; j < dots; j++) // a loop that prints the dots
                if (wbytes = write(fd, ".", 1) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
            if (wbytes = write(fd, price, strlen(price)) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
            if (wbytes = write(fd, "NIS\n", 4) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
            printf("Insert dish name %d : \n", count);
            fgets(dish, 256, stdin);//getting the next dish
            count++;
        }
        count = 2; //setting count back to 2
    }
    if (wbytes = write(fd, "\n\n               Bon Apetit\n", 28) == -1) { perror("write"); exit(1); } //writing to a file + checking if it was succeeded
    printf("Successfully created\n");
    dest = (char*)malloc(sizeof(char) * (strlen(argv[1]) + strlen(order))); //allocating memory for dest
    if (dest == NULL) { perror("allocation failed"); exit(1); } //checking if allocation was succeeded
    strcpy(dest, argv[1]); //copying argv[1] to dest
    strcat(dest, order);
    mkdir(dest, 0777); //creating a new folder and setting permissions
    free(dest); //freeing allocated memory
    close(fd); //closing file's grip
    return 0;
}