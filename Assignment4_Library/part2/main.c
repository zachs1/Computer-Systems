#include <stdio.h>
#include "my_hashmap.h"

int unitTest1(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    // Does hashmap contain key?
    printf("pig was added should be 1: %d\n",hashmap_hasKey(myHashmap,"pig"));
    // Print out the keys
    hashmap_printKeys(myHashmap);
    // Retrieve pig's value 
    printf("pig's value is %s\n",hashmap_getValue(myHashmap, "pig"));
    hashmap_update(myHashmap,"pig","a really cool farm animal");    
    printf("pig's value is updated to: %s\n",hashmap_getValue(myHashmap, "pig"));
    // Remove a key
    hashmap_removeKey(myHashmap,"pig");
    // Does hashmap contain key?
    printf("pig was removed should be 0: %d\n",hashmap_hasKey(myHashmap,"pig"));
    // Finally terminate our hashmap
    hashmap_delete(myHashmap);
}

int unitTest2(){
    // Create our hashmap
    hashmap_t* myHashmap = hashmap_create(5); 
    // Insert a first key/value pair
    hashmap_insert(myHashmap,"pig", "a farm animal");
    hashmap_insert(myHashmap,"bat", "a farm creature");
    hashmap_insert(myHashmap,"cat", "a funny farm animal");
    hashmap_insert(myHashmap,"dog", "a fun farm animal");
    hashmap_insert(myHashmap,"bear", "a wild farm animal");
    hashmap_insert(myHashmap,"ox", "another farm animal");
    hashmap_insert(myHashmap,"cow", "a favorite farm animal");
    hashmap_insert(myHashmap,"hippo", "a farm animal?");
    hashmap_insert(myHashmap,"elephant", "not a farm animal");
    hashmap_insert(myHashmap,"human", "an animal that farms");
    // Print the keys
    hashmap_printKeys(myHashmap);
	hashmap_removeKey(myHashmap, "dog");
    // Finally terminate our hashmap
    hashmap_printKeys(myHashmap);
    hashmap_delete(myHashmap);
}

int unitTest3(){
	hashmap_t* myHashmap = hashmap_create(20);
	hashmap_insert(myHashmap, "a", "letr");
	hashmap_insert(myHashmap, "aa", "letr");
	hashmap_insert(myHashmap, "aaa", "letr");
	hashmap_insert(myHashmap, "aaaa", "letr");
	hashmap_insert(myHashmap, "aaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aaaaaaaaaaaaaaaaaaaa", "letr");
	hashmap_insert(myHashmap, "aa", "boop");
	hashmap_insert(myHashmap, "a", "the");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "quick");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "brown");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "fox");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "was");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "pretty");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "fast");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_insert(myHashmap, "a", "lol");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));
	hashmap_printKeys(myHashmap);
	hashmap_insert(myHashmap, "a", "fast");
	printf("'a' updated to: %s\n",hashmap_getValue(myHashmap, "a"));	
	hashmap_removeKey(myHashmap, "a");
	hashmap_insert(myHashmap, "a", "fast");
	hashmap_printKeys(myHashmap);
	hashmap_delete(myHashmap);
}
int main(){

    printf("============ unitTest1() ================\n");
    unitTest1();
    printf("============ unitTest2() ================\n");
    unitTest2();
    printf("============ unitTest3() ================\n");
    unitTest3();
	return 0;
}
