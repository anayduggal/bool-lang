
#include <stdio.h>
#include <stdlib.h>

typedef struct StatementTree {

    // syntax tree, nodes contain a string

    char* contents;
    struct StatementTree* left;
    struct StatementTree* right;

} Tree;

typedef struct MapChainNode {
    struct MapChainNode* next;          // next node
    char* key;                          // string key
    void* value;                        // value (any type)
} Node;

typedef struct Hashmap {
    struct MapChainNode** table;        // array of node
    int table_size;                     // size of table
} Map;

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_FUNCTION,
    TOKEN_LITERAL,

} TokenType;

struct Token {
    TokenType type;
    char* string;
};

Tree* treeInit(char* contents);
void treeAppendLeft(Tree* origin, Tree* new_tree);
void treeAppendRight(Tree* origin, Tree* new_tree);
void treeFree(Tree* origin_node);

int djb2(char* string);

Map* mapInit(int table_size);
void mapInsert(Map* m, char* key, void* value);
void* mapGet(Map* m, char* key);
void mapFree(Map* m);

Node* nodeInit(char* key, void* value);
void nodeFree(Node* n);
void listFree(Node* n);

int binaryToDenary(char* num_string);
char* denaryToBinary(int num);


