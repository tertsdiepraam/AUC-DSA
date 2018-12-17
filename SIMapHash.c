#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SIMap.h"

typedef struct SIMapData* SIMap;

typedef struct ListNodeData* ListNode;

struct ListNodeData {
    char* key;
    int value;
    ListNode next;
};

struct SIMapData {
    ListNode* buckets;
    int table_allocated;
    int table_used;
};

// out: an empty SIMap
SIMap sim_create() {
    int size = 8000;
    SIMap M = (SIMap) malloc(sizeof(struct SIMapData));
    if (M == NULL) { printf("Could not allocate SIMap"); exit(1); }
    
    M->buckets = (ListNode*) malloc(sizeof(ListNode)*size);
    if (M->buckets == NULL) { printf("Could not allocate buckets for SIMap"); exit(1); }
    
    for (int i=0; i < size; i++) {
        M->buckets[i] = NULL;
    }
    M->table_allocated = size;
    M->table_used = 0;
    return M;
}

// in: a SIMap
// side effect: the map is destroyed and all memory freed
void sim_destroy(SIMap M) {
    for (int i=0; i < M->table_allocated; i++) {
        ListNode current = M->buckets[i];
        while (current != NULL) {
            ListNode next = current->next;
            free(current);
            current = next;
        }
    }
    free(M->buckets);
    free(M);
}

// in: a SIMap M, a key and a value.
// side effect: the key is bound to the value in M.
//   if the key was already in the map, the old association is removed.
int hash(char* s) {
    int h = 0;
    for (int i=0; s[i]!='\0'; i++) {
        h = 31*h + (int)s[i];
    }
    return abs(h);
}

void sim_set(SIMap M, char* key, int value) {
    //printf("sim_set key: %s, value: %d\n", key, value);
    int index = hash(key) % M->table_allocated;
    //printf("Setting at index: %d\n", index);
    ListNode* address;
    if (M->buckets[index] == NULL) {
        address = &(M->buckets[index]);
    } else {
        ListNode current = M->buckets[index];
        if (strcmp(current->key, key) == 0) { current->value = value; return; }
        while (current->next != NULL) {
            current = current->next;
            if (strcmp(current->key, key) == 0) { current->value = value; return; }
        }
        address = &(current->next);
    }

    ListNode new_node = (ListNode) malloc(sizeof(struct ListNodeData));
    if (new_node == NULL) { printf("Could not allocate new node"); exit(1); }
    
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    *address = new_node;
    M->table_used++;
}


// in: a SIMap M and a key.
// side effect: if the key k occurs in the map, it is removed.
void sim_remove(SIMap M, char* key) {
    int index = hash(key) % M->table_allocated;
    ListNode to_remove;
    if (M->buckets[index]->key == key) {
        to_remove = M->buckets[index];
        M->buckets[index] = to_remove->next;
        free(to_remove);
    } else {
        ListNode current= M->buckets[index];
        while (current->next != NULL) {
            if (current->next->key == key) {
                to_remove = current->next;
                current->next = to_remove->next;
                free(to_remove);
                return;
            }
        }
    }
}

// in: a SIMap M and a key k.
// out: -1 if key is not in M,
//      value if a binding (key,value) is in the map.
int sim_lookup(SIMap M, char* key) {
    //printf("sim_lookup key: %s\n", key);
    //printf("Looking up at index: %d\n", hash(key) % M->table_allocated);
    ListNode current = M->buckets[hash(key) % M->table_allocated];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) { return current->value; } 
        current = current->next;
    }
    return -1;
}

// in: a SIMap M
// out: the number of bindings in the SIMap
int sim_size(SIMap M) {
    return M->table_used++;
}