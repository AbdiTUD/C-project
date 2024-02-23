#ifndef _PROJECT__H_
#define _PROJECT__H_
typedef struct {
    char* name;
    float price;
    float revenue;
}gameShop;

int main(void);
gameShop* addGame(gameShop *shop, char *name, float price);
gameShop* buyGame(gameShop* shop, char* name, int count);
int cmpfunc (const void * a, const void * b);
void printDatabase(gameShop* shop);
int saveToFile(gameShop* shop, char* filename);
gameShop *loadFromFile(char* filename);
#endif //! _PROJECT__H_