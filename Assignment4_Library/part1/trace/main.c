#include <stdio.h>

void msg(){
	printf("Hello!\n");
}


int main(){

	int i;
	for(i= 0;i  < 100000; ++i){
		msg();
	}

	return 0;
}
