#include "mpos-app.h"
#include "lib.h"

void start(void) {
int x = 0; /* note that local variable x lives on the stack */

/* YOUR CODE HERE */
volatile int *child = &x;
int* volatile parent = &x;
pid_t p = sys_fork();
if (p == 0)		//child process
{
*child = 1;
*parent = 1;
}
else if (p > 0)		//parent process
sys_wait(p); // assume blocking implementation
app_printf("%d", x);
sys_exit(0);
}
