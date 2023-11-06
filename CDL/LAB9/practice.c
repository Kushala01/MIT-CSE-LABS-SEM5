#include "la.c"

struct token cur;
FILE *f;

void program();
void declarations();
void statementList();
void identifierList();
void statement();
void dataTypes();
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
void decisionStat();
void dPrime();
void loopingStat();
void ternaryExp();

void valid() {
    printf("-----------------------SUCCESS-----------------------\n");
    exit(EXIT_SUCCESS);
}

void invalid(char* str) {
    printf("Missing %s at Row : %d and Column : %d\n", str, cur.row, cur.col);
    exit(EXIT_FAILURE);
}

void match() {
    cur = getNextToken(f);
}

void declarations() {
    dataTypes();
    identifierList();
    if (!strcmp(cur.lexeme, ";")) {
        match();
        if (isDataType(cur.lexeme)) declarations();    
    } else invalid("\";\"");
}

void dataTypes() {
    if (isDataType(cur.lexeme)) match();
    else invalid("Data Type");
}

void identifierList() {
    if (strcmp(cur.type, "Identifier")) invalid("Identifier");
    match();
    if (!strcmp(cur.lexeme, ",")) {
        match();
        identifierList();
    } else if (!strcmp(cur.type, "[")) {
        match();
        if (strcmp(cur.type, "Number")) invalid("Number");
        match();
        if (strcmp(cur.type, "]")) invalid("\"]\"");
        match();
        if (!strcmp(cur.lexeme, ",")) {
            match();
            identifierList();
        }
    }
}

void statementList() {
    if (!strcmp(cur.type, "Identifier") || !strcmp(cur.type, "Keyword")) {
        statement();
        statementList();
    }
}

void statement() {
    if (!strcmp(cur.type, "Identifier")) {
        assignStat();
        if (strcmp(cur.lexeme, ";")) invalid("\";\"");
        else match();
    } else if (!strcmp(cur.lexeme, "if")) decisionStat();
    else if (!strcmp(cur.lexeme, "while") || !strcmp(cur.lexeme, "for")) loopingStat();
}

void expn() {
    simpleExpn();
    ePrime();
}

int isRelOp(const char* str) {
    return !strcmp(str, "==") || !strcmp(str, "!=") || !strcmp(str, "<=") || !strcmp(str, ">=") || !strcmp(str, ">") || !strcmp(str, "<");
}

void ePrime() {
    if (isRelOp(cur.lexeme)) {
        relOp();
        simpleExpn();
    }
}

void simpleExpn() {
    term();
    sePrime();
}

int isAddOp(const char* str) {
    return !strcmp(str, "+") || !strcmp(str, "-");
}

void sePrime() {
    if (isAddOp(cur.lexeme)) {
        addOp();
        term();
        sePrime();
    }
}

void term() {
    factor();
    tPrime();
}

int isMulOp(const char* str) {
    return !strcmp(str, "*") || !strcmp(str, "/") || !strcmp(str, "%");
}

void tPrime() {
    if (isMulOp(cur.lexeme)) {
        mulOp();
        factor();
        tPrime();
    }
}

void factor() {
    if (!strcmp(cur.type, "Identifier") || !strcmp(cur.type, "Number")) {
        match();
    } else if (!strcmp(cur.lexeme, "(")) {
        match();
        expn();
        if (strcmp(cur.lexeme, ")")) invalid("\")\"");
        match();
    } else if (!strcmp(cur.lexeme, "intmax")) {
        match();
        if (strcmp(cur.lexeme, "=")) invalid("\"=\"");
        match();
        ternaryExp();
    } else {
        invalid("Identifier / Number / Nested Expression / intmax");
    }
}

void ternaryExp() {
    expn(); // Evaluate the first expression
    if (cur.lexeme == NULL || strcmp(cur.lexeme, "?") != 0) {
        // If the current lexeme is NULL or not a '?', then it's not a ternary expression.
        // Handle this case appropriately, maybe it's not an error depending on your grammar.
        return;
    }

    match(); // Match the '?'
    expn(); // Evaluate the second expression

    if (cur.lexeme == NULL || strcmp(cur.lexeme, ":") != 0) {
        invalid("\":\""); // If the current lexeme is not ':', it's an error.
        return;
    }

    match(); // Match the ':'
    expn(); // Evaluate the third expression
}

void relOp() {
    if (isRelOp(cur.lexeme)) match();
    else invalid("Relational Operator");
}

void addOp() {
    if (isAddOp(cur.lexeme)) match();
    else invalid("Addition Operator");
}

void mulOp() {
    if (isMulOp(cur.lexeme)) match();
    else invalid("Multiplication Operator");
}

void assignStat() {
    if (!strcmp(cur.type, "Identifier")) {
        match();
        if (!strcmp(cur.lexeme, "=")) {
            match();
            ternaryExp();
        } else {
            invalid("\"=\"");
        }
    } else {
        invalid("Identifier");
    }
}

void program() {
    match();
    if (strcmp(cur.lexeme, "main")) invalid("Main Function");
    match();
    if (strcmp(cur.lexeme, "(")) invalid("\"(\"");
    match();
    if (strcmp(cur.lexeme, ")")) invalid("\")\"");
    match();
    if (strcmp(cur.lexeme, "{")) invalid("\"{\"");
    match();
    declarations();
    statementList();
    if (strcmp(cur.lexeme, "}")) invalid("\"}\"");
}

void decisionStat() {
    if (strcmp(cur.lexeme, "if")) invalid("if");
    match();
    if (strcmp(cur.lexeme, "(")) invalid("\"(\"");
    match();
    expn();
    if (strcmp(cur.lexeme, ")")) invalid("\")\"");
    match();
    if (strcmp(cur.lexeme, "{")) invalid("\"{\"");
    match();
    statementList();
    if (strcmp(cur.lexeme, "}")) invalid("\"}\"");
    match();
    dPrime();
}

void dPrime() {
    if (!strcmp(cur.lexeme, "else")) {
        match();
        if (strcmp(cur.lexeme, "{")) invalid("\"{\"");
        match();
        statementList();
        if (strcmp(cur.lexeme, "}")) invalid("\"}\"");
        match();
        if (!strcmp(cur.lexeme, "else")) {
            match();
            dPrime();
        }
    }
}

void loopingStat() {
    if (!strcmp(cur.lexeme, "while")) {
        match();
        if (strcmp(cur.lexeme, "(")) invalid("\"(\"");
        match();
        expn();
        if (strcmp(cur.lexeme, ")")) invalid("\")\"");
        match();
        if (strcmp(cur.lexeme, "{")) invalid("\"{\"");
        match();
        statementList();
        if (strcmp(cur.lexeme, "}")) invalid("\"}\"");
        match();
    } else if (!strcmp(cur.lexeme, "for")) {
        match();
        if (strcmp(cur.lexeme, "(")) invalid("\"(\"");
        match();
        assignStat();
        if (strcmp(cur.lexeme, ";")) invalid("\";\"");
        match();
        expn();
        if (strcmp(cur.lexeme, ";")) invalid("\";\"");
        match();
        assignStat();
        if (strcmp(cur.lexeme, ")")) invalid("\")\"");
        match();
        if (strcmp(cur.lexeme, "{")) invalid("\"{\"");
        match();
        statementList();
        if (strcmp(cur.lexeme, "}")) invalid("\"}\"");
        match();
    } else invalid("Looping Statement");
}

void main(int argc, char** argv) {
    assert(argc == 2);
    f = fopen(argv[1], "r");
    if (!f) {
        perror("ERROR\n");
        exit(EXIT_FAILURE);
    }
    program();
    valid();
}

//check when is epsilon is used
//check if its cur.type/cur.lexme
//added Modify the RD parser to handle compound expressions present in C program----changed from 148-155---compound statements are a+(c+d)
//Modify the RD parser to handle ternary statements present in C program---changed from---ternary statements---expn ? expn : expn