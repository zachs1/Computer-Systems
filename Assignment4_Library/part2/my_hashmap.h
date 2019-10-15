// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf  output. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// - You may add any helper functions that you think you need (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>
#include "containers.h"

int stringHash(char* myKey, int numberOfBuckets);

typedef int(*hash_function)(char*,int); 

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hash_function)(char*,int) ; 

// Chained implementation of a hashmap
typedef struct hashmap{
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way
                            //      - an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    // Note: function pointers are a new concept, but we can
    //       have pointers to functions just like we can have pointers
    //       to variables. Again, a pointer just stores an address!
    hash_function hashFunction;
}hashmap_t;

hashmap_t* hashmap_create(unsigned int _buckets);
void hashmap_delete(hashmap_t* _hashmap);
int hashmap_hasKey(hashmap_t* _hashmap, char* key);
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value);
char* hashmap_getValue(hashmap_t* _hashmap, char* key);
void hashmap_removeKey(hashmap_t* _hashmap, char* key);
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue);
void hashmap_printKeys(hashmap_t* _hashmap);

#endif
