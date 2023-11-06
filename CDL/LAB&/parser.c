#include "la.c"

struct token cur;
FILE *f;

void declarations();
void dataTypes();
void identifierList();
void assignStat();

void checkTokenAndFetchNext(const char* expectedToken, const char* errorMsg, int compareType)
{
    if (compareType == 0) // compare lexeme
    {
        if (strcmp(cur.lexeme, expectedToken) != 0)
        {
            printf(errorMsg, cur.row, cur.col);
            exit(EXIT_FAILURE);
        }
    }
    else if (compareType == 1) // compare type
    {
        if (strcmp(cur.type, expectedToken) != 0)
        {
            printf(errorMsg, cur.row, cur.col);
            exit(EXIT_FAILURE);
        }
    }
    cur = getNextToken(f);
}

void declarations()
{
    dataTypes();
    identifierList();
    checkTokenAndFetchNext(";", "Missing \";\" at Row : %d and Column : %d\n", 0);
    if (isDataType(cur.lexeme) == 0) return;
    declarations();
}

void dataTypes()
{
    if (!isDataType(cur.lexeme))
    {
        printf("Missing Data Type at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
    cur = getNextToken(f);
}

void identifierList()
{
    checkTokenAndFetchNext("Identifier", "Missing Identifier at Row : %d and Column : %d\n", 1);
    if (strcmp(cur.lexeme, ",") == 0)
    {
        cur = getNextToken(f);
        identifierList();
    }
}

void assignStat()
{
    checkTokenAndFetchNext("Identifier", "Missing Identifier at Row : %d and Column : %d\n", 1);
    checkTokenAndFetchNext("=", "Missing \"=\" at Row : %d and Column : %d\n", 0);
    if (strcmp(cur.type, "Identifier") != 0 && strcmp(cur.type, "Number") != 0)
    {
        printf("Missing Identifier or Number at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
    cur = getNextToken(f);
    checkTokenAndFetchNext(";", "Missing \";\" at Row : %d and Column : %d\n", 0);
}

void program()
{
    cur = getNextToken(f);
    checkTokenAndFetchNext("main", "\nMissing main function\n\n", 0);
    checkTokenAndFetchNext("(", "Missing \"(\" at Row : %d and Column : %d\n", 0);
    checkTokenAndFetchNext(")", "Missing \")\" at Row : %d and Column : %d\n", 0);
    checkTokenAndFetchNext("{", "Missing \"{\" at Row : %d and Column : %d\n", 0);
    declarations();
    assignStat();
    checkTokenAndFetchNext("}", "Missing \"}\" at Row : %d and Column : %d\n", 0);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf(argc < 2 ? "Insufficient Arguments\n" : "Extra Arguments\n");
        exit(EXIT_FAILURE);
    }
    f = fopen(argv[1], "r");
    if (!f)
    {
        printf("ERROR\n");
        exit(EXIT_FAILURE);
    }
    program();
    printf("-----------------------COMPILED-----------------------\n");
    exit(EXIT_SUCCESS);
}