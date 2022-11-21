#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

char** build_argv(char*);
int numOfPar(char**);

char** build_argv(char* buffer) { //a function that returns a new argv
    int i = 0;
    char* token, ** par, path[256] = "/bin/";
    par = (char**)malloc(sizeof(char*)); //allocating memory
    if (par == NULL) { printf("memory allocation error"); exit(1); } //checking if the allocation succeded
    if ((strcmp(buffer, "exit\n")) == 0) { //checking if the buffer is "exit"
        par[0] = "exit";
        return par;
    }
    buffer[strlen(buffer) - 1] = '\0';
    while (strlen(buffer) == 0) { //checking if this is an empty command
        par[0] = "empty";
        return par;
    }
    token = strtok(buffer, " "); //getting the first word
    while (token != NULL)
    {
        par[i] = token; //assuming token into par[i]
        token = strtok(NULL, " "); //getting the next word
        i++;
        par = (char**)realloc(par, (i + 1) * sizeof(char*)); //allocating new memory size for par
        if (par == NULL) { printf("memory allocation error"); exit(1); }//checking if the allocation succeded
    }
    par[i - 1] = strtok(par[i - 1], "\n");//removing "\n" from the end of the string
    par[i] = NULL; //setting the last place at par to NULL
    if (strcmp(par[0], "CreateMenu") && strcmp(par[0], "getMenu") && strcmp(par[0], "MakeOrder") && strcmp(par[0], "getPrice") && strcmp(par[0], "getOrderNum")) { //checking if the command is not a kitchen command
        strcat(path, par[0]);//adding to "/bin/" the first string in par(system command) 
        par[0] = path;//assuming path into par[0]
    }
    return par;
}

int numOfPar(char** argv) { // a function that counts the number of arguments of newArgv
    int i = 0;
    while (argv[i] != NULL)
        i++;
    return i;
}

int main() {
    int pid = 1;
    char buffer[256], ** newArgv;
    printf("AdvShell>");//printing a message
    memset(buffer, 0, sizeof(buffer)); //resetting the buffer
    fgets(buffer, 256, stdin); //getting the command + parameters(if there are)
    newArgv = build_argv(buffer); //creating a new argv with function build_argv
    while (!strcmp(newArgv[0], "empty") || numOfPar(newArgv) > 5) { //checking if this is an empty command or with more than 3 paramters
        if (strcmp(newArgv[0], "empty"))
            printf("Not Supported\n");
        printf("AdvShell>");
        memset(buffer, 0, sizeof(buffer)); //resetting the buffer
        fgets(buffer, 256, stdin);
        newArgv = build_argv(buffer);
    }
    while ((strcmp(newArgv[0], "exit")) != 0) //a loop that runs untill user enters command exit
    {
        pid = fork();//creating a sub-process
        if (pid == -1) { perror("fork failed"); exit(1); } //checking if the fork failed    
        if (pid == 0)//checking if this is the sub-process
        {
            execv(newArgv[0], newArgv); //executing a new process
            printf("Not Supported\n");
            exit(1);
        }
        else
        {
            wait(1);
            printf("AdvShell>");//printing a message
            memset(buffer, 0, sizeof(buffer)); //resetting the buffer
            fgets(buffer, 256, stdin); //getting the command + parameters(if there are)
            newArgv = build_argv(buffer); //creating a new argv with function build_argv
            while (!strcmp(newArgv[0], "empty") || numOfPar(newArgv) > 5) { //checking if this is an empty command or with more than 3 paramters
                if (strcmp(newArgv[0], "empty"))
                    printf("Not Supported\n");
                printf("AdvShell>");
                memset(buffer, 0, sizeof(buffer)); //resetting the buffer
                fgets(buffer, 256, stdin);
                newArgv = build_argv(buffer);
            }
        }
    }
    //executing command exit
    pid = fork();
    if (pid == -1) { perror("fork failed"); exit(1); } //checking if the fork failed    
    if (pid == 0)//checking if this is the sub-process
    {
        execv(newArgv[0], newArgv); //executing a new process
        printf("Not Supported\n");
        exit(1);
    }
    wait(1);
    free(newArgv); //freeing newArgv
    return 0;
}
