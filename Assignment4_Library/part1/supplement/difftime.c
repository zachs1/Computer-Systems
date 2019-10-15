// Author: Michael D. Shah
// Last Updated: 6/5/19
// Please do not redistrubte without asking
// Please learn from this example however!
// 
// gcc difftime.c -o difftime
//
// The following example shows how to compute an elapsed time.
// You can think of it like a stop watch, where you hit the start and
// stop timer. You will also see some #define statements showing how
// the preprocessor is used to turn on and off the 'sleeping' of our
// program.
//
// This implies anytime you are timing something, you will need to store
// two times, then to compute the elapsed time, you would subtract
// the larger time(i.e. an event that happened later) from the start 
// time(i.e. an event that happened earlier).
//
// Time_elapsed = end - start; // This gives us some number
//
// In computer systems, most hardware has a timer that keeps track of
// the number of 'seconds' or 'milliseconds' since the beginning of time.
// (The beginning of time just being some fixed date...which
// in systems is Thursday, Jan. 1, 1970 apparently). The example below
// shows the elapsed time in seconds. Sometimes that will not be a 
// fine enough grained resolution (e.g. think about a short sprinting race
// that comes to within hundredths of seconds to determine the winner).
//
// After doing this example, see if you can find more fine-grained resolution
// timers in the C-library!
//
#include <stdio.h>  // I/O functions
#include <time.h>   // Contains handy things like: time_t and difftime
#include <unistd.h> // For the 'sleep' command

// Programmers will often use the pre-processor
// to insert 'switches' to configure how there 
// program runs. In this case, we have a 'DEBUG'
// mode which will put our program to sleep
// for some duration of time.
#define DEBUG 1
#define SLEEPTIME 5

int main ()
{
    // Create two clocks that will record the time.
    time_t now;
    time_t later; 
    // Get the starting time
    time(&now);  /* get current time; same as: now = time(NULL)  */
    // Put our program to sleep for 'SLEEPTIME' seconds
#if DEBUG
    sleep(SLEEPTIME);
#endif
    // Get the time at this point (i.e. roughly 5 seconds later)  
    time(&later);
    // Now compute the difference
    double time_elapsed = difftime(later,now);

    printf ("%.f seconds elapsed\n", time_elapsed);

    return 0;
}
