#include <stdio.h>
#include <time.h>

static int __FunctionsExecuted__ = 0;
static double __Time_Elapsed__ = 0;
time_t __now__;
time_t __later__;
void* __main__ = NULL;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){
	if(__FunctionsExecuted__ == 0){
		__main__ = this_fn;
		time(&__now__);
	}

	__FunctionsExecuted__++;
	printf("\tFunction entered 0x%x from 0x%x\n", this_fn, call_site);

}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){
	printf("\tFunction exited 0x%x from 0x%x\n", this_fn, call_site);

	if(this_fn == __main__){
		time(&__later__);
		__Time_Elapsed__ = difftime(__later__, __now__);
		printf("Total functions called: %d\n", __FunctionsExecuted__);
		printf("Total elapsed time: %f\n", __Time_Elapsed__);
	}
}

