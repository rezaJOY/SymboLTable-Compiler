/*    

  MD ZIAUR REZA JOY
    ID: 19204030

*/

#include <iostream>
using namespace std;

#define CHAIN_LENGTH 20
#define M 128

// Two columns of the symbol table with symbol and type.
struct SymbolInfo
{
    char *symbol;
    char *type;
    struct SymbolInfo *next;
} * block[CHAIN_LENGTH];

// Hashing and performing Modulo operation to go to any bucket from 0 to CHAIN_LENGTH

int cHash(char *symbol)
{
    int idx = 0;
    for (int i = 0; symbol[i]; ++i)
    {
        idx = idx + symbol[i];
    }
    return (idx % CHAIN_LENGTH);
}

// If no element then new element is added in front or else through hashing
// then we insert the new element at the beginning of the chain and
// the rest elements is linked to the end of new node.

void insert(char *symbol, char *type)
{
    int pos = cHash(symbol);

    if (block[pos] == NULL)
    {
        block[pos] = new SymbolInfo();
        block[pos]->symbol = symbol;
        block[pos]->type = type;
        block[pos]->next = NULL;
    }
    else
    {
        SymbolInfo *newNode = new SymbolInfo();
        newNode->symbol = symbol;
        newNode->type = type;

        // pointer swap
        SymbolInfo *nextNode = block[pos];
        block[pos] = newNode;
        newNode->next = nextNode;
    }
}

// Go to certain chain through hashing since we know others will not contain the searched value.
// Next in that chain doing linear search on all element to see if it is there.
bool lookup(char *symbol, char *type)
{
    // Implement
    int pos = cHash(symbol);

    SymbolInfo *temp = block[pos];

    while (temp != NULL)
    {
        if (!strcmp(temp->symbol, symbol) && !strcmp(temp->type, type))
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// If the symbol and type both matches then delete the element.
void Delete(char *symbol, char *type)
{
    int pos = cHash(symbol);

    SymbolInfo *temp = block[pos];
    if (temp == NULL)
        return;

    // At head but no one to follow
    if (temp->next == NULL && !strcmp(temp->symbol, symbol) && !strcmp(temp->type, type))
    {
        block[pos] = NULL;
    }
    // At head has followers
    else if (!strcmp(temp->symbol, symbol) && !strcmp(temp->type, type))
    {
        block[pos] = temp->next;
    }
    else
    {

        while (temp->next != NULL)
        {
            if (!strcmp(temp->next->symbol, symbol) && !strcmp(temp->next->type, type))
            {
                printf("FOUND IT %s : %s\n", temp->symbol, temp->type);
                break;
            }
            temp = temp->next;
        }

        if (temp != NULL)
        {
            SymbolInfo *found = temp->next;
            temp->next = found->next;
            delete (found);
        }
    }
}

// showing the symbol table chain wise.
void dump()
{
    // Implement
    for (int i = 0; i < CHAIN_LENGTH; ++i)
    {
        printf("%d:", i);

        // Do not modify the head
        SymbolInfo *temp = block[i];

        while (temp != NULL)
        {
            printf("->[%s|%s]", temp->symbol, temp->type);
            temp = temp->next;
        }

        printf("\n");
    }
}

int showMenu()
{
    cout << "========Menu:=========\n";
    cout << "======================\n";

    string message = "*Press 1 to insert a new symbol along with its type into the symbol-table\n"
                     "*Press 2 to lookup whether a given symbol exists in the symbol table or not\n"
                     "*Press 3 to delete a given symbol if it already exists in the symbol-table\n"
                     "*Press 4 to dump the contents of the symbol table to the console\n"
                     "*Press 0 to exit\n";

    cout << message << "\n";

    cout << "User Choice: ";
    int choice;
    scanf("%d", &choice);

    return choice;
}

int main()
{

    //take input from a file
    int choice = showMenu();
    while (1)
    {

        char *symbol = new char[M];
        char *type = new char[M];

        switch (choice)
        {
        case 1:
        {
            cout << "Input symbol and type to insert:\n";
            scanf("%s%s", symbol, type);

            // Omit the comma character if given
            int pos = strlen(symbol) - 1;
            if (symbol[pos] == ',')
            {
                symbol[pos] = '\0';
            }

            printf("%s %s\n", symbol, type);
            printf("%d\n", cHash(symbol));
            insert(symbol, type);
        }
        break;

        case 2:
        {
            cout << "Input symbol and type to lookup :\n";

            scanf("%s%s", symbol, type);

            // Omit the comma character if given
            int pos = strlen(symbol) - 1;
            if (symbol[pos] == ',')
            {
                symbol[pos] = '\0';
            }

            printf("%s %s\n", symbol, type);
            printf("%d\n", cHash(symbol));

            if (lookup(symbol, type))
            {
                printf("FOUND\n");
            }
            else
            {
                printf("NOT FOUND\n");
            }
        }
        break;
        case 3:
        {
            cout << "Input symbol and type to delete :\n";
            scanf("%s%s", symbol, type);

            // Omit the comma character if given
            int pos = strlen(symbol) - 1;
            if (symbol[pos] == ',')
            {
                symbol[pos] = '\0';
            }

            printf("%s %s\n", symbol, type);
            printf("%d\n", cHash(symbol));

            Delete(symbol, type);
        }
        break;
        case 4:
            cout << "Dump Selected\n";
            dump();
            break;
        default:
            return 0;
        };

        choice = showMenu();
    }

    return 0;
}
