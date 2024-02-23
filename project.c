#include "project.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//function to add games to our database
gameShop* addGame(gameShop *shop, char *name, float price){
    
    int j=0;
    //check if we're in the last elemnt of the database that is a NULL
    while (shop[j].name != NULL)
    {
        if (strcmp(shop[j].name, name)==0)
        {
            printf("Game %s already is in the system.\n", name);
            return shop; 
        }j++;
    }
    if (price >0)
    {
    
    
    //if the first element is not NULL then allocate memory etc for 0+1 else 0 
    if (shop[0].name != NULL)
    {
    
        shop = realloc(shop, (j+2)*sizeof(gameShop));
        shop[j].name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(shop[j].name, name);
        shop[j].price = price;
        shop[j].revenue = 0.0;
        shop[j+1].name = NULL;
        printf("SUCCESS\n");
    }else{
        shop[0].name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(shop[0].name, name);
        shop[0].price = price;
        shop[0].revenue = 0.0;
        shop = realloc(shop, 2*sizeof(gameShop));
        shop[1].name = NULL;
        printf("SUCCESS\n");
    }
    }else{printf("Game price cannot be negative or zero.\n");
    }
    return shop;
}

//this is a function to buy a game in the database
gameShop* buyGame(gameShop* shop, char* name, int count){
    //we check if we're buying more than 0 since we cannot buy 0 games or -1 games
    if (count >0)
    {
    int i=0;
    int bought = 0;
    while (shop[i].name != NULL)
    {
        //if game is in the database we buy
        if (strcmp(shop[i].name, name)==0)
        {
            shop[i].revenue += count*shop[i].price;
            bought = 1;
            printf("SUCCESS\n");
            break;
        }i++;
    }
    if (!bought)
    {
        printf("couldn't find game in database\n");
    }
    }else{
        printf("Number of bought items cannot be less than 1.\n");
    }
    return shop;
}
//this function allows us to sort the database by revenue asc order

int cmpfunc (const void * a, const void * b) {
   float ra= ((gameShop*)a)->revenue;
   float rb = ((gameShop*)b)->revenue;
   if (ra < rb)
   {
    return 1;
   }else if (rb < ra)
   {
    return -1;
   }else{
    return 0;
   }
}

//function to print the database to console
void printDatabase(gameShop* shop){
    int i=0;
    while(shop[i].name != NULL)
    {
        i++;
    }
    // we sort the database using abpve function
    qsort(shop,i,sizeof(gameShop),cmpfunc );
    for (int j = 0; j < i; j++)
    {
        printf("%s %.2f %.2f\n", shop[j].name, shop[j].price, shop[j].revenue);
    }
    printf("SUCCESS\n");
}

//function to save the database to a file
int saveToFile(gameShop* shop, char* filename){
    FILE* fp = fopen(filename, "w");
    // if file opening is successful then we save it to that file
    if (fp != NULL)
    {
        for (int i = 0;shop[i].name != NULL; i++)
        {
            fprintf(fp, "%s %.2f %.2f\n", shop[i].name, shop[i].price, shop[i].revenue);
        }
        fclose(fp);
        printf("SUCCESS\n");
        return 1;
    }else{
       printf("Error, couldn't save to file.\n");
       return 0;
    }
}

//function to load from file
gameShop *loadFromFile(char* filename){
    FILE* fp = fopen(filename, "r");
    char str[1000];
    //if we cannot open up the created file then we get an error to console and return NULL else we continue with our function
    if (fp == NULL)
    {
       printf("Cannot open file %s for reading.\n",filename);
       return NULL;
    }
    
    //first we coount the number of gameShop elements in the file
    int k = 0;
    while (fgets(str,sizeof(str),fp))
    {
        k++;
    }
    //we rewind back to the start of the file
    rewind(fp);
    //we initialize a new database and allocate memory for it

    gameShop* newDatabase = calloc(k+1,sizeof(gameShop));
    char name[50];
    //we the read through every database element in the file and load them into our newDatabase
    //we replace the values in the newDatabase with the ones in the file
    for (int i = 0; i < k; i++)
    {
        fgets(str, 1000, fp);
        sscanf(str, "%s %f %f", name,&newDatabase[i].price ,&newDatabase[i].revenue);
        newDatabase[i].name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(newDatabase[i].name, name);
    }
    fclose(fp);
    printf("SUCCESS\n");
    return newDatabase;
}


int main(void){
    int gameOn = 1;
    char command[1000];
    char newline = '\0';
    int count;
    char name[50];
    float price = 0; 

    gameShop *shop = malloc(sizeof(gameShop));
    shop[0].name = NULL;
    while (gameOn)
    {
        fgets(command, 1000, stdin);
        sscanf(command, "%c", &newline);
        switch (newline)
        {
        case 'A':
            if (sscanf(command, "%c %s %f", &newline, name, &price) == 3)
            {
                shop = addGame(shop,name,price);
            }else{
                printf("A should be followed by exactly 2 arguments.\n");
            }break;
        case 'B':
            if (sscanf(command, "%c %s %d", &newline, name, &count) == 3)
            {
                shop = buyGame(shop,name,count);
            }else{
                printf("B should be followed by exactly 2 arguments.\n");
            }break;
        case 'L':
            if (sscanf(command, "%c", &newline)==1)
            {
                printDatabase(shop);
            }else{
                printf("Invalid command\n");
            }break;
        case 'W':
            if (sscanf(command, "%c %s", &newline, name)==2)
            {
                saveToFile(shop, name);
            }else{
                printf("Invalid command\n");
            }break;
        case 'O':
            if (sscanf(command, "%c %s", &newline, name)==2)
            {
                //first we free our memory (if the file can be found) and then the free'd gameShop is replaced with the new one that we load from
                int i = 0;
                gameShop *x = loadFromFile(name);
                if (x != NULL)
                {
                    
                    while (shop[i].name != NULL)
                    {
                        free(shop[i].name);
                        i++;
                    }
                    free(shop);
                    shop = x;
                }
            }else{
                printf("Invalid command\n");
            }
            break;

        case 'Q':
            printf("SUCCESS\n");
            gameOn =0;
            break;
        default: 
            printf("Invalid command %c\n", newline);
            break;
        }
    }

    //when the program is exited we free all the memory that is allocated
    for (int i = 0;shop[i].name != NULL; i++)
    {
        free(shop[i].name);
    }
    free(shop);
    
    return 0; 
}
    
    