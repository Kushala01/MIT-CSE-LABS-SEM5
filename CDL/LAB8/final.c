#include "la.c"

struct token cur;
FILE *f;

void declarations();
void dataTypes();
void identifierList();
void assignStat();
void expn();
void simpleExpn();
void ePrime();
void relOp();
void sePrime();
void addOp();
void term();
void tPrime();
void factor();
void mulOp();
int isRelOp(const char* str);
int isAddOp(const char* str);
int isMulOp(const char* str);

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
    if (!isDataType(cur.lexeme)) return;
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
    if (strcmp(cur.lexeme, "[") == 0)
    {
        cur = getNextToken(f);
        checkTokenAndFetchNext("Number", "Missing Number at Row : %d and Column : %d\n", 1);
        checkTokenAndFetchNext("]", "Missing \"]\" at Row : %d and Column : %d\n", 0);
    }
    if (strcmp(cur.lexeme, ",") == 0)
    {
        cur = getNextToken(f);
        identifierList();
    }
}

void assignStat()
{
    checkTokenAndFetchNext("Identifier", "Missing Identifier at Row : %d and Column : %d\n", 1);
    if (strcmp(cur.lexeme, "[") == 0)
    {
        cur = getNextToken(f);
        checkTokenAndFetchNext("Number", "Missing Number at Row : %d and Column : %d\n", 1);
        checkTokenAndFetchNext("]", "Missing \"]\" at Row : %d and Column : %d\n", 0);
    }
    checkTokenAndFetchNext("=", "Missing \"=\" at Row : %d and Column : %d\n", 0);
    expn(); // modified this line to call expn instead of simpleExpn
    checkTokenAndFetchNext(";", "Missing \";\" at Row : %d and Column : %d\n", 0);
}

void expn()
{
    simpleExpn();
    ePrime();
}

void simpleExpn()
{
    term();
    sePrime();
}

void ePrime()
{
    if (isRelOp(cur.lexeme))
    {
        relOp();
        simpleExpn();
    }
}

void term()
{
    factor();
    tPrime();
}

void sePrime()
{
    if (isAddOp(cur.lexeme))
    {
        addOp();
        term();
        sePrime();
    }
}

void tPrime()
{
    if (isMulOp(cur.lexeme))
    {
        mulOp();
        factor();
        tPrime();
    }
}

void factor()
{
    if (strcmp(cur.type, "Identifier") == 0 || strcmp(cur.type, "Number") == 0)
    {
        cur = getNextToken(f);
    }
    else
    {
        printf("Missing Identifier or Number at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}


int isRelOp(const char* str)
{
    return strcmp(str, "==") == 0 || strcmp(str, "!=") == 0 ||
           strcmp(str, "<=") == 0 || strcmp(str, ">=") == 0 ||
           strcmp(str, "<") == 0 || strcmp(str, ">") == 0;
}

int isAddOp(const char* str)
{
    return strcmp(str, "+") == 0 || strcmp(str, "-") == 0;
}

int isMulOp(const char* str)
{
    return strcmp(str, "*") == 0 || strcmp(str, "/") == 0 || strcmp(str, "%") == 0;
}

void relOp()
{
    if (isRelOp(cur.lexeme))
    {
        cur = getNextToken(f);
    }
    else
    {
        printf("Missing Relational Operator at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void addOp()
{
    if (isAddOp(cur.lexeme))
    {
        cur = getNextToken(f);
    }
    else
    {
        printf("Missing Additive Operator at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void mulOp()
{
    if (isMulOp(cur.lexeme))
    {
        cur = getNextToken(f);
    }
    else
    {
        printf("Missing Multiplicative Operator at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void program()
{
    cur = getNextToken(f);
    checkTokenAndFetchNext("main", "Missing main function at Row : %d and Column : %d\n", 0);
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