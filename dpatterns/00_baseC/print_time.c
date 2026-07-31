#include <stdio.h>
#include <time.h>
#include <string.h>

/* Time structures manipulation example */

void print_time(const char *message)
{
    char ch_time[80];

    /* historically implemented as integer: secs since 1970-01-01 */
    time_t now;
    struct tm *current;

    time(&now);
    current = localtime(&now);

    strftime(ch_time, 80, "%H:%M:%S", current);
    printf("%s: %s\n", message, ch_time);
}


int main(void)
{
    print_time("Event happened at");
    return 0;
}
