// Implement your cycle count tool here.'
#include <stdio.h>
#include <string.h>

#define ADD		0
#define SUB		1
#define MOV		2
#define LEA		3
#define PUSH	4
#define POP		5
#define RET		6
#define INSTRS	31

void findInstr( char* word, int* count){
	const char *instrs[INSTRS] = {"addq", "addl", "addw", "addb", "add",\
									"subq", "subl", "subw", "subb", "sub",\
									"movq", "movl", "movw", "movb", "mov",\
									"leaq", "leal", "leaw", "leab","lea",\
									"pushq", "pushl", "pushw", "pushb", "push",\
									"popq", "popl", "popw", "popb", "pop",\
									"ret"};
	int i = 0;
	for( i; i < INSTRS; i++){
		if( !strcasecmp(word, instrs[i]) ){
			if( i >= 0 && i <= 4)		count[ADD]+=1;
			else if( i > 4 && i <= 9)	count[SUB]+=1;
			else if( i > 9 && i <= 14)	count[MOV]+=1;
			else if( i > 14 && i <= 19) count[LEA]+=1;
			else if( i > 19 && i <= 24) count[PUSH]+=1;
			else if( i > 24 && i <= 29) count[POP]+=1;
			else if (i == 30)			count[RET]+=1;
		}
	}
}

void printInstrs( int* count ){
	printf("Instructions tallied:\nADDs: %d\nSUBs: %d\nMOVs: %d\nLEAs: %d\nPUSHs: %d\nPOPs: %d\nRETs: %d\n", \
		count[ADD], count[SUB], count[MOV], count[LEA], count[PUSH], count[POP], count[RET]);
	
	// cyles are approximated
	double cycles[INSTRS] = {1.5, 1.5, 1, 1, 1.5, 3, 2};
	double total_cycles = count[ADD]*cycles[ADD] +\
						count[SUB]*cycles[SUB] +\
						count[MOV]*cycles[MOV] +\
						count[LEA]*cycles[LEA] +\
						count[PUSH]*cycles[PUSH] +\
						count[POP]*cycles[POP] +\
						count[RET]*cycles[RET];

	printf("Total cycles (approximation): %.0f\n", total_cycles);
}

int main(int argc, char* argv[]){
	printf("argv: %s\n", argv[1]);
	
	char* file = argv[1];
	char buf[255];
	
	// track count of each of our instruction categories
	int counts[INSTRS] = {0};
	
	FILE* myFile;
	myFile = fopen(file, "r");

	if(myFile == NULL){
		printf("Unable to read file given path %s\n", file);
	}
	
	while( fscanf(myFile, "%s", buf) != EOF ){
		findInstr(buf, counts);
	}

	printInstrs(counts);
	fclose(myFile);
	return 0;
}
