#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int fd_file, fd_menu, i = 0, j = 0, sum = 0, wbytes, rbytes, amount, price = 0, temp = 0, flag = 0;
    char path[256], order[256] = { 0 }, dishName[256], buffer[1024], * token, * dish, headLine[256], totalPrice[256];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (argc != 3) { perror("wrong number of prameters"); exit(1); } // checking if there are not 3 parameters
    if ((fd_menu = open(argv[1], O_RDONLY)) == -1) { printf("Restaurant not found!\n"); exit(1); } //opening menu file
    //building path to create the file in the restaurant folder
    strcpy(path, argv[1]);
    strcat(path, "_Order/");
    strcat(path, argv[2]);
    if ((fd_file = open(path, O_WRONLY | O_CREAT, 0444)) == -1) { perror("error creating file"); exit(1); }; //creating an order file
    strcpy(headLine, argv[1]);
    strcat(headLine, " Order\n\n");
    if ((wbytes = write(fd_file, headLine, strlen(headLine))) == -1) { perror("write"); exit(1); } //writing into the order file
    printf("Insert your order (Finish to finish)\n");
    fgets(order, 256, stdin); //getting first dish
    order[strlen(order) - 1] = '\0'; //converting into a string
    while (strcmp(order, "Finish") != 0) // a loop the gets the orders
    {
        if ((wbytes = write(fd_file, order, strlen(order))) == -1) { perror("write"); exit(1); } //writing into the order file
        if ((wbytes = write(fd_file, "\n", 1)) == -1) { perror("write"); exit(1); }
        memset(dishName, 0, sizeof(dishName)); //resetting an array of chars
        token = strtok(order, " ");
        while (token != NULL) { // a loop that splits the dish into 2 different string - the name of the dish and its' amount
            if (atoi(token) != 0)
                break;
            strcat(dishName, " ");
            strcat(dishName, token);
            token = strtok(NULL, " ");
        }
        amount = atoi(token); // converting string to an int
        lseek(fd_menu, 0, SEEK_SET);//resetting pointer in the file to the begining
        while ((rbytes = read(fd_menu, buffer, 1024)) > 0) { //reading from the file untill the end of the file in order to find the order's price
            dish = strstr(buffer, dishName);
            if (dish != NULL) {
                while (isdigit(dish[i]) == 0) { //ignoring the dots
                    i++;
                }
                while (isdigit(dish[i]) != 0) { //calculating the price
                    price *= 10;
                    price += (dish[i] - '0');
                    i++;
                }
                sum += amount * price; //adding to the sum
                i = 0;
                price = 0;
                break;
            }
            else {
                printf("dish was not found\n");
            }
        }
        fgets(order, 256, stdin); //getting the next dish
        order[strlen(order) - 1] = '\0';
    }
    printf("Total Price : %d NIS (Confirm to approve/else cancel)\n", sum);
    sprintf(totalPrice, "Total Price : %d NIS\n\n%02d/%02d/%d", sum, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    if ((wbytes = write(fd_file, totalPrice, strlen(totalPrice))) == -1) { perror("write"); exit(1); }//writing into the order file
    while ((strcmp(fgets(order, 256, stdin), "Confirm\n")) != 0) // an infinite loop that waits for the user to enter Confirm
        printf("Please enter Confirm\n");
    printf("Order Created !\n");
    close(fd_menu); //closing files' grip
    close(fd_file);
    return 0;
}