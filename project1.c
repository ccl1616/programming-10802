#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// lex.h------------------------------------------------
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE, 
    INT, ID,
    ADDSUB, MULDIV, LOGICAL,
    INCDEC, ASSIGN, 
    LPAREN, RPAREN
} TokenSet;

// Test if a token matches the current token 
int match(TokenSet token);

// Get the next token
void advance(void);

// Get the lexeme of the current token
char *getLexeme(void);

// parser.h----------------------------------------------
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, NOUNUSED
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    //int regpos;
    struct _Node *left; 
    struct _Node *right;
} BTNode;

BTNode *treeroot;
// The symbol table
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);

// Get the value of a variable
int getval(char *str);

// Set the value of a variable
int setval(char *str, int val);

// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
void freeTree(BTNode *root);

BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);
void statement(void);

// Print error message and exit the program
void err(ErrorType errorNum);

// codegen.h---------------------------------------------
int evaluateTree(BTNode *root);
int r[9];
bool used[9];
int* rt;
int* lt;

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

extern void initialRegister();
extern int findUnused();
extern void toUsed(int i);
extern int putIntReg(int data);
extern int putIdReg(char *str);
extern void cleanReg(int pos);

// lex.c-------------------------------------------------

static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void) {
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } 
    else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == lexeme[0]) {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } 
        else {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } 
    else if (c == '&' || c == '|' || c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return LOGICAL;
    } 
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } 
    else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } 
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } 
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } 
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } 
    else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } 
    else if (c == EOF) {
        return ENDFILE;
    } 
    else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}

// parser.c--------------------------------------------------

int sbcount = 0;
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i;

    error(NOTFOUND);
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return i;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return sbcount-1;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  | 
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN |
//           INCDEC ID 
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    }
    else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (!match(ASSIGN)) {
            retp = left;
        }
        else {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = expr();
        }
    }
    else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme());
            advance();
        }
        else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            advance();
        }
        else if (match(LPAREN)) {
            advance();
            retp->right = expr();
            if (match(RPAREN))
                advance();
            else
                error(MISPAREN);
        }
        else {
            error(NOTNUMID);
        }
    }
    else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        retp->left = makeNode(INT, "0"); 
        advance();
        if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            advance();
        }
        else error(SYNTAXERR);
    }
    else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    }
    else {
        error(NOTNUMID);
    }
    return retp;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return term_tail(node);
    } 
    else {
        return left;
    }
}

// expr := term expr_tail
BTNode *expr(void) {
    BTNode *node = term();
    return expr_tail(node);
}

// expr_tail := ADDSUB term expr_tail | NiL
// --> ADDSUB_LOGICAL term expr_tail | NiL
BTNode *expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    } 
    else if(match(LOGICAL)){
        node = makeNode(LOGICAL, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    }
    else {
        return left;
    }
}

// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        for(int i = 0;i < 3; i ++){
            r[i] = table[i].val;
            printf("MOV r%d [%d]\n",i,i*4);
            //printf("%s %d\n",table[i].name,r[i]);
        }
        
        if(PRINTERR){
            for(int i = 0; i < 3; i ++)
                printf("r[%d] %d\n",i,r[i]);
        }
        printf("EXIT 0\n");
        exit(0);
    } 
    else if (match(END)) {
        //printf(">> ");
        advance();
    } 
    else {
        retp = expr();
        treeroot = retp;
        if (match(END)) {
            int i = evaluateTree(retp);
            //printf("%d\n", evaluateTree(retp));
            //printf("Prefix traversal: ");
            if(PRINTERR)
                printPrefix(retp);
            //printf("\n");
            initialRegister();
            freeTree(retp);
            //printf(">> ");
            advance();
        } 
        else {
            error(SYNTAXERR);
        }
    }
}


void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            case NOUNUSED:
                fprintf(stderr, "no unused register\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }

    }
    printf("EXIT 1\n");
    exit(0);
}

// codegen.c--------------------------------------------------

void initialRegister()
{
    for(int i = 0; i < 8; i ++){
        used[i] = false;
        r[i] = -1;
    }
    return;
}

int findUnused()
{
    int i;
    for(i = 0; i < 8; i ++){
        if(used[i] == false){
            used[i] = true;
            return i;
        }
    }
    if(i >= 8)
        error(NOUNUSED);
    return 0;
}

void toUsed(int i)
{
    used[i] = true;
    return;
}

int putIntReg(int data)
{
    int i = findUnused();
    r[i] = data;
    //toUsed(i);
    printf("MOV r%d %d\n",i,data);
    return i;
}

int putIdReg(char *str)
{
    // get table pos
    int i = getval(str);
    // get empty register pos
    int j = findUnused();
    r[j] = table[i].val;
    //toUsed(j);
    printf("MOV r%d [%d]\n",j,i*4);
    return j;
}

void cleanReg(int pos)
{
    // printf("clean : r%d\n",pos);
    r[pos] = -1;
    used[pos] = false;
}

// 為了看分母有沒有變數
int findId(BTNode *root)
{
    if(root != NULL){
        if(root->data == ID )
            return 1;
        else if(root->data == INT)
            return 0;
        else {
            return findId(root->left)+findId(root->right);
        }
    }
    return 0;
}


int findUnusedMem(int reg)
{
    for(int i = TBLSIZE-1 ; ; i --){
        if(strcmp(table[i].name,"used")){
            table[i].val = r[reg];
            printf("MOV [%d] r%d\n",4*i,reg);
            strcpy(table[i].name,"used");
            return i;
        }
    }
    printf("Impossible for not finding a null memory\n");
    return 0;
}
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    int saveToMem = 0;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                //retval = getval(root->lexeme);
                retval = putIdReg(root->lexeme);
                break;
            case INT:
                //retval = atoi(root->lexeme);

                retval = putIntReg( atoi(root->lexeme) );
                break;
            case ASSIGN:
                if(root->right->data != ASSIGN){
                    rv = evaluateTree(root->right);
                    retval = setval(root->left->lexeme, r[rv]); // setval return table pos
                    printf("MOV [%d] r%d\n",retval*4,rv);
                    retval = rv;
                    // cleanReg(rv);
                }
                else {
                    rv = evaluateTree(root->right);
                    retval = setval(root->left->lexeme, r[rv]);
                    printf("MOV [%d] r%d\n",retval*4,rv);
                    retval = rv;
                    if(root == treeroot){
                        cleanReg(rv);
                    }
                }

                break;
            case ADDSUB:
            case MULDIV:
            case LOGICAL:
                lv = evaluateTree(root->left);
                if(lv == 6 && root->right->data >= 5){
                    lv = findUnusedMem(lv);
                    saveToMem = 1;
                    cleanReg(6);
                }
                rv = evaluateTree(root->right);
                if(saveToMem){
                    int temp = lv;
                    lv = findUnused();
                    //toUsed(lv);
                    r[lv] = table[temp].val;
                    strcpy(table[temp].name,"clean");
                    printf("MOV r%d [%d]\n",lv,4*temp);
                }

                if (strcmp(root->lexeme, "+") == 0) {
                    r[lv] += r[rv];
                    printf("ADD r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv ;
                } 
                else if (strcmp(root->lexeme, "-") == 0) {
                    r[lv] -= r[rv];
                    printf("SUB r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                } 
                else if (strcmp(root->lexeme, "*") == 0) {
                    r[lv] *= r[rv];
                    printf("MUL r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                } 
                else if (strcmp(root->lexeme, "/") == 0) {
                    if (r[rv] == 0 && findId(root->right) <= 0)
                        error(DIVZERO);

                    r[lv] /= r[rv];
                    printf("DIV r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                    
                }
                else if(strcmp(root->lexeme, "&") == 0){
                    r[lv] = r[lv]&r[rv];
                    printf("AND r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                }
                else if(strcmp(root->lexeme, "|") == 0){
                    r[lv] = r[lv] |r[rv];
                    printf("OR r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                }
                else if(strcmp(root->lexeme, "^") == 0){
                    r[lv] = r[lv]^r[rv];
                    printf("XOR r%d r%d\n",lv,rv);
                    cleanReg(rv);
                    retval = lv;
                }
                break;
            case INCDEC:
                if (strcmp(root->lexeme, "++") == 0) {
                    // rv is variable's pos in table
                    rv = getval(root->right->lexeme);

                    // variable's register
                    retval = findUnused();
                    //toUsed(retval);
                    printf("MOV r%d [%d]\n",retval,rv*4);
                    r[retval] = table[rv].val;

                    // "1"'s register 
                    lv = findUnused();
                    //toUsed(lv);
                    printf("MOV r%d 1\n",lv);

                    printf("ADD r%d r%d\n",retval,lv);
                    r[retval] ++;

                    printf("MOV [%d] r%d\n",rv*4,retval);
                    table[rv].val ++;

                    cleanReg(lv);
                }

                else if (strcmp(root->lexeme, "--") == 0) {
                    // rv is variable's pos in table
                    rv = getval(root->right->lexeme);

                    // variable's register
                    retval = findUnused();
                    //toUsed(retval);
                    printf("MOV r%d [%d]\n",retval,rv*4);
                    r[retval] = table[rv].val;

                    // "1"'s register 
                    lv = findUnused();
                    //toUsed(lv);
                    printf("MOV r%d 1\n",lv);

                    printf("SUB r%d r%d\n",retval,lv);
                    r[retval] --;

                    printf("MOV [%d] r%d\n",rv*4,retval);
                    table[rv].val --;

                    cleanReg(lv);
                }
                break;
            default:
                retval = 0;
        }
    }
    
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {

        printf("%s  ", root->lexeme);

        printf("L");
        printPrefix(root->left);
        printf("R");
        printPrefix(root->right);
    }
}


// main--------------------------------------------------
int main() {
    //freopen("input.txt", "w", stdout);
    initTable();
    //printf(">> ");
    while (1) {
        statement();
        // initialRegister();
    }
    return 0;
}
