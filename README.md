## Project Documentation 
 
### Overview 
 
This project consists of a game shop management system implemented in C. It provides functionalities to add games to a database, buy games, sort the database by revenue, print the database to the console, save the database to a file, and load the database from a file. 
 
### Files 
 
-	`project.h`: Header file containing function prototypes and structure definitions. 
-	`main.c`: Main C file containing the implementation of the functionalities. 
-	`README.md`: Documentation file explaining how to use the program. 
 
### Functions 
 
1. **addGame** 
-	Description: Adds a new game to the database if it doesn't already exist. 
-	Parameters: 
-	`gameShop *shop`: Pointer to the database of games. 
-	`char *name`: Name of the game to add. 
-	`float price`: Price of the game. 
-	Returns: Updated pointer to the database after adding the game. 
 
2. **buyGame** 
-	Description: Allows purchasing a game from the database by incrementing the revenue of the game. 
-	Parameters: 
-	`gameShop *shop`: Pointer to the database of games. 
-	`char *name`: Name of the game to buy. 
-	`int count`: Number of copies of the game to buy. 
-	Returns: Updated pointer to the database after purchasing the game. 
 
3. **cmpfunc** 
-	Description: Comparison function used for sorting the database by revenue in ascending order. 
-	Parameters: `const void *a`, `const void *b`. 
-	Returns: -1 if `a` has less revenue than `b`, 1 if `a` has more revenue than `b`, and 0 if revenues are equal. 
 
4. **printDatabase** 
-	Description: Prints the contents of the database to the console, sorted by revenue. 
-	Parameters: `gameShop *shop`: Pointer to the database of games. 
-	Returns: void. 
 
5. **saveToFile** 
-	Description: Saves the database to a file. 
-	Parameters: 
-	`gameShop *shop`: Pointer to the database of games. 
-	`char *filename`: Name of the file to save the database to. 
-	Returns: 1 on success, 0 on failure. 
 
6. **loadFromFile** 
-	Description: Loads the database from a file. 
-	Parameters: `char *filename`: Name of the file to load the database from. 
-	Returns: Pointer to the loaded database. 
 
### Usage 
 
1.	Compile the program using a C compiler (e.g., GCC): `gcc -o game_shop main.c`. 
2.	Run the compiled program: `./game_shop`. 
3.	Follow the prompts to add games, buy games, print the database, save the database to a file, load the database from a file, or quit the program. 
 
### Example 
 
```c 
#include "project.h" 
 
int main() { 
    // Initialize variables and structures 
    // Perform operations using functions from project.h 
    // Clean up memory 
    return 0; 
} 
``` 
 
### Dependencies 
 
- Standard C libraries: `stdio.h`, `stdlib.h`, `string.h`. 
 
