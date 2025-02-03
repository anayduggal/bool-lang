
#include <stdio.h>
#include <stdlib.h>
#include "boolcompiler.h"

Tree* treeInit(char* contents) {
    Tree* t = malloc(sizeof(Tree));

    if (t == NULL) {return NULL;}

    t->contents = contents;
    t->left = NULL;
    t->right = NULL;

    return t;

}

void treeFree(Tree* origin_node) {
    if (origin_node->left != NULL) {
        treeFree(origin_node->left);
    }

    if (origin_node->right != NULL) {
        treeFree(origin_node->right);
    }

    free(origin_node);

}

void treeAppendLeft(Tree* origin, Tree* new_tree) {
    origin->left = new_tree;
}

void treeAppendRight(Tree* origin, Tree* new_tree) {
    origin->right = new_tree;
}

int djb2(char* string) {
    int hash = 5381;
    int i;

    while (i != 0) {
        i = *string++;
        hash = (hash << 5) + hash + i;
    }

    return hash;

}

Map* mapInit(int table_size) {
    Map* m = malloc(sizeof(Map));

    if (m == NULL) {return NULL;}

    m->table_size = table_size;
    m->table = malloc(table_size * sizeof(Node*));

    if (m->table == NULL) {
        free(m);
        return NULL;
    }

    for (int i=0;i<table_size;i++) {
        m->table[i] = NULL;
    }

    return m;
}

void mapInsert(Map* m, char* key, void* value) {

    Node* n = nodeInit(key, value);
    if (n == NULL) {return NULL;}

    int hash_index = djb2(n->key) % m->table_size;

    Node* space = m->table[hash_index];

    if (space == NULL) {
        m->table[hash_index] = n;
    } else {
        while (space->next != NULL) {
            space = space->next;
        }
        space->next = n;
    }

}

void* mapGet(Map* m, char* key) {
    int hash_index = djb2(key) % m->table_size;

    Node* temp = m->table[hash_index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }

    return NULL;

}

void mapPop(Map* m, char* key) {
    int hash_index = djb2(key) % m->table_size;

    Node* temp = m->table[hash_index];

    // case of empty bucket
    if (temp == NULL) {return;}

    // case of first node match
    if (strcmp(temp->key, key) == 0) {
        if (temp->next == NULL) {
            // no more nodes
            m->table[hash_index] = NULL;
        } else {
            // at least one more node
            m->table[hash_index] = temp->next;
        }
        nodeFree(temp);
        return;
    }

    // case of not first node match

    while (temp->next != NULL && temp->next->key != key) {  
        temp = temp->next;
    }

    if (temp->next == NULL) {return;}           // no matches

    Node* node_to_pop = temp->next;
    temp->next = temp->next->next;
    nodeFree(node_to_pop);

}

void mapFree(Map* m) {

    for (int i=0;i<m->table_size;i++) {
        nodeFree(m->table[i]);
    }

    free(m->table);
    free(m);
}

Node* nodeInit(char* key, void* value) {
    Node* n = malloc(sizeof(Node));

    if (n == NULL) {return NULL;}

    n->next = NULL;
    n->key = key;
    n->value = value;

    return n;

}

void nodeFree(Node* n) {

    // frees one node
    // TODO ACCOUNT FOR DYNAMIC/STATIC ALLOCATION

    if (n == NULL) {return;}
    free(n);
}

void listFree(Node* n) {

    // frees an entire chain of nodes
    // TODO ACCOUNT FOR DYNAMIC/STATIC ALLOCATION

    if (n == NULL) {return;}
    nodeFree(n->next);
    free(n);
}

int binaryToDenary(char* num_string) {
    int result = 0; 
    char* i = num_string;

    // find end of string

    while (*i != 0) {
        i++;
    }

    int end = i - num_string - 1;

    // calculate denary

    for (int j=0;j<=end;j++) {
        if (num_string[j] == 49) {
            result += 1 << (end - j);
        }
        
    }

    return result;

}

char* denaryToBinary(int num) {

    // 0 edge case

    if (num == 0) {
        char* zero = malloc(2);
        zero[0] = '0';
        zero[1] = '\0';
        return zero;
    }

    // calculate length of binary string

    int length = 0;
    int temp = num;

    while (temp > 0) {
        temp >>= 1;
        length++;
    }

    // allocate memory

    char* result = malloc(length + 1);
    if (result == NULL) {return NULL;}

    // create binary number

    result[length] = 0;     // null terminate

    for (int i=length-1;i>=0;i--) {
        result[i] = num % 2 == 0 ? '0' : '1';
        num /= 2;
    }

    return result;

}

