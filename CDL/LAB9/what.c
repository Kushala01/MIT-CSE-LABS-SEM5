#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_KEYWORDS (sizeof(Keywords) / sizeof(char*))
#define NUM_SPECIAL_SYMBOLS (sizeof(specialsymbols) / sizeof(specialsymbols[0]))
#define NUM_ARITHMETIC_SYMBOLS (sizeof(arithmeticsymbols) / sizeof(arithmeticsymbols[0]))

struct token{
    char lexeme[128];
    int row,col;
    char type[128];
};

int gotToken=0;
static int row=1,col=1;

const char specialsymbols[] = {'?', ';', ':', ','};
const char *Keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"};
const char arithmeticsymbols[] = {'*', '/', '-', '+', '%'};
const char *DataTypes[] = {"int", "float", "char", "void","double","long"};

int charBelongTo(int c, const char *arr, int len){
    for(int i=0;i<len;i++){
        if(c==arr[i]) return 1;
    }return 0;
}

void fillToken(struct token *tkn, char c, int row, int col, const char *type) {
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    tkn->lexeme[0] = c;
    tkn->lexeme[1] = '\0';
    gotToken=1;
}

void newLine() {
    ++(row);
    col = 1;
}

int isKeyword(const char *str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, Keywords[i]) == 0)
            return 1;
    }return 0;
}

int isDataType(const char *str)
{
    for (int i = 0; i < sizeof(DataTypes) / sizeof(char *); i++){
        if (strcmp(str, DataTypes[i]) == 0)
            return 1;
    }return 0;
}

struct token getNextToken(FILE *fin){
    int c;
    struct token tkn;
    tkn.row=-1;
    gotToken=0;

    while(!gotToken && (c=fgetc(fin))!=EOF){
        if(c=='/'){
            int d=fgetc(fin);
            if(d=='/'){
                while((c=fgetc(fin)!=EOF)&&c!='\n') ++col;
            }else if(d=='*'){
                do{
                    if(d=='\n') newLine();
                    while((c=fgetc(fin)!=EOF)&&c!='*'){
                        ++col;
                        if(c=='\n') newLine();
                    }
                    ++col;
                }while((d=fgetc(fin))!='/'&&col++&&d!=EOF);
                ++col;
            }else{
                fillToken(&tkn,c,row,--col,"/");
                fseek(fin,-1,SEEK_CUR);
            }
        }else if(charBelongTo(c, specialsymbols, NUM_SPECIAL_SYMBOLS)){
            char symbol[2]={c,'\0'};
            fillToken(&tkn, c, row, col, symbol);
            ++col;
        }else if (charBelongTo(c, arithmeticsymbols, NUM_ARITHMETIC_SYMBOLS)) {
            char symbol[2] = {c, '\0'};
            fillToken(&tkn, c, row, col, symbol); // Set token for arithmetic symbol
            ++col;
        }else if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']') {
            char symbol[2] = {c, '\0'};
            fillToken(&tkn, c, row, col, symbol); 
            ++col;
        }else if (c == '+' || c == '-') {
            int d = fgetc(fin);
            if (d != c) {
                char symbol[2] = {c, '\0'};
                fillToken(&tkn, c, row, col, symbol); 
                ++col;
                fseek(fin, -1, SEEK_CUR);
            } else if(d==c){
                char symbol[3] = {c, c, '\0'};
                fillToken(&tkn, c, row, col, symbol); 
                strcpy(tkn.lexeme, symbol);
                col += 2;
            }else fseek(fin, -1, SEEK_CUR);
        }else if (c == '!' || c == '=' || c == '<' || c == '>') {
            char symbol[2] = {c, '\0'};
            fillToken(&tkn, c, row, col, symbol); 
            gotToken = 1;
            ++col;
            int d = fgetc(fin);
            if (d == '=') {
                ++col;
                strcat(tkn.lexeme, "=");
            } else fseek(fin, -1, SEEK_CUR);
        }else if (isdigit(c)) {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isdigit(c)) {
                tkn.lexeme[k++] = c;
                col++;
            }
            tkn.lexeme[k] = '\0';
            strcpy(tkn.type, "Number");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }else if (c == '#') {
            while ((c = fgetc(fin)) != EOF && c != '\n');
            newLine(); 
        }else if (c == '\n') {
            newLine(); 
            c = fgetc(fin);
            if (c == '#') {
                while ((c = fgetc(fin)) != EOF && c != '\n');
                newLine();
            } else if (c != EOF) fseek(fin, -1, SEEK_CUR);
        } else if (isspace(c)) ++col;
        else if (isalpha(c) || c == '_') {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isalnum(c)) {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '\0';
            if (isKeyword(tkn.lexeme)) strcpy(tkn.type, "Keyword");
            else strcpy(tkn.type, "Identifier");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }else if (c == '"') {
            tkn.row = row;
            tkn.col = col;
            strcpy(tkn.type, "StringLiteral");
            int k = 1;
            tkn.lexeme[0] = '"';
            while ((c = fgetc(fin)) != EOF && c != '"') {
                tkn.lexeme[k++] = c;
                ++col;
            }tkn.lexeme[k] = '"';
            tkn.lexeme[k++] = '\0';
            gotToken = 1;
        }else if (c == '&' || c == '|') {
            int d = fgetc(fin);
            if (d == c) {
                tkn.lexeme[0] = tkn.lexeme[1] = c;
                tkn.lexeme[2] = '\0';
                tkn.row = row;
                tkn.col = col;
                ++col;
                gotToken = 1;
                char symbol[3] = {c, c, '\0'};
                strcpy(tkn.type,"logicalOperation");
            } else fseek(fin, -1, SEEK_CUR);
            ++col;
        }else ++col;
    }return tkn;
}
int main() {
    FILE *fin;
    struct token tkn;
    char filename[100];

    printf("Enter the name of the C source file: ");
    scanf("%s", filename);

    fin = fopen(filename, "r");
    if (fin == NULL) {
        printf("File not found or cannot be opened.\n");
        return 1;
    }

    do {
        tkn = getNextToken(fin);
        if (tkn.row != -1) {
            printf("Row: %d, Col: %d, Type: %s, Lexeme: %s\n", tkn.row, tkn.col, tkn.type, tkn.lexeme);
        }
    } while (tkn.row != -1);

    fclose(fin);
    return 0;
}