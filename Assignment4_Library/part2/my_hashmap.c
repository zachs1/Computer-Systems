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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "containers.h"
#include "my_hashmap.h"


// Simple hash function that will put a key into a bucket
// The module operator will make sure we do not go out of bounds.
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
hashmap_t* hashmap_create(unsigned int _buckets){
    // Allocate memory for our hashmap
    hashmap_t* _hm = (hashmap_t*)malloc(sizeof(hashmap_t));	
    // Set the number of buckets
	_hm->buckets = _buckets;
    // Initialize our array of lists for each bucket
	_hm->arrayOfLists = (node_t**)malloc(_buckets * sizeof(node_t*));
    // Setup our hash function to point to our
    // stringHash function	
	_hm->hashFunction = stringHash;
    // Return the new map that we have created
    return _hm;
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// Attempting to delete a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap){
    if(_hashmap != NULL){
		int i;
		node_t* curr_node;
		node_t* next_node;
		for(i = 0; i < _hashmap->buckets; i++){
			curr_node = _hashmap->arrayOfLists[i];
			next_node = curr_node;
			while(curr_node != NULL){
				next_node = curr_node->next;
				free(curr_node->kv->key);
				free(curr_node->kv->value);
				free(curr_node->kv);
				free(curr_node);
				curr_node = next_node;
			}
		}
		free(_hashmap->arrayOfLists);
		free(_hashmap);
    }
	else {
		exit(1);
	}
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Attempting hashmap_hasKey on a NULL hashmap should exit(1)
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search (i.e. iterate through) that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key){
	int index = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* curr_bucket = _hashmap->arrayOfLists[index];
	if( curr_bucket == NULL ){
		return 0;
	}

	do {
		if( !strcmp(curr_bucket->kv->key, key) ){
			return 1;
		}
		curr_bucket = curr_bucket->next;
	} while(curr_bucket != NULL);
	
	return 0;
}


// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
//  - Attempting hashmap_insert on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value){
    if(_hashmap == NULL){
		exit(1);
	}
	if( hashmap_hasKey(_hashmap, key) ){
		hashmap_update(_hashmap, key, value);
		return;
	}	

	pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
    newpair->key    = (char*)malloc(strlen(key)     * sizeof(char));
    newpair->value  = (char*)malloc(strlen(value)   * sizeof(char));
    // Copy the string passed by the user to our node
    strcpy(newpair->key     ,key); 
    strcpy(newpair->value   ,value); 
    // Create a new node
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    newnode->next = NULL;
    newnode->kv = newpair;

    // Which bucket to search
    unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
    
	// ... Insert node to appropriate linked list
	// Check for empty bucket
	if(_hashmap->arrayOfLists[bucket] == NULL){
		_hashmap->arrayOfLists[bucket] = (node_t*)malloc(sizeof(node_t));
		node_t* iter = _hashmap->arrayOfLists[bucket];
		memcpy(iter, newnode, sizeof(node_t));
	}
    
	else{	
	// Create an iterator that points to the head of list for appropriate bucket
		node_t* iter = _hashmap->arrayOfLists[bucket];
		while(1){
			if(iter->next == NULL){
				iter->next = (node_t*)malloc(sizeof(node_t)); 
				memcpy(iter->next, newnode, sizeof(node_t));
				break;
			}
			iter = iter->next;
		}
	}

	free(newnode);
    return; 
}
// Return a value from a key 
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
//  - Attempting hashmap_getValue on a NULL hashmap should exit(1)
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key){
	if(_hashmap == NULL){
		exit(1);
	}
	unsigned int index = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* curr_node = _hashmap->arrayOfLists[index];
	while(curr_node != NULL){
		if( !strcmp(curr_node->kv->key, key) ){
			return curr_node->kv->value;
		}
		curr_node = curr_node->next;
	}
	return NULL;
}

// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
//  - Attempting hashmap_removeKey on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key){
	if(_hashmap == NULL) {
		exit(1);
	}
	unsigned index = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* curr_node = _hashmap->arrayOfLists[index];
	node_t* prev_node = curr_node;
	do {
		if( !strcmp(curr_node->kv->key, key) ){
			// if we want to remove the first node, need to push 2nd node to head of linked list
			// only matters if the size of the list in that bucket is > 1
			if(curr_node == prev_node) {
				_hashmap->arrayOfLists[index] = curr_node->next;
			}
			if( curr_node->next != NULL ){
				prev_node->next = curr_node->next;	
			}
			
			free(curr_node->kv->key);
			free(curr_node->kv->value);
			free(curr_node->kv);
			free(curr_node);
			break;
		}
		else {
			if(curr_node != prev_node){
				curr_node = curr_node->next;
				prev_node = prev_node->next;
			}
			else {
				curr_node = curr_node->next;
			}
		}
	} while (curr_node != NULL);
	return;
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
//  - Attempting hashmap_update on a NULL hashmap should exit(1)
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue){
	if(_hashmap == NULL){
		exit(1);
	}
	unsigned int index = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* curr_node = _hashmap->arrayOfLists[index];
	if(curr_node == NULL) {
		return;
	}

	while (curr_node != NULL){
		if( !strcmp(curr_node->kv->key, key) ){
			free(curr_node->kv->value);
			char* value = (char*)malloc(strlen(newValue) * sizeof(char));
			strcpy(value, newValue);
			curr_node->kv->value = value;
			return;
		}
		curr_node = curr_node->next;
	}
}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
//  - Attempting hashmap_printKeys on a NULL hashmap should exit(1)
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
	if(_hashmap == NULL){
		exit(1);
	}
	int i;
	for(i = 0; i < _hashmap->buckets; i++){
		node_t* curr_node = _hashmap->arrayOfLists[i];
		if(curr_node == NULL){
			continue;
		}
		else {
			printf("%s\n", curr_node->kv->key);
			while(curr_node->next != NULL){
				curr_node = curr_node->next;
				printf("%s\n", curr_node->kv->key);
			}
		}
	}
}

