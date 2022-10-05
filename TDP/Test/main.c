#include <stdio.h>

int main(void) 
{  
    enum DAY            /* Defines an enumeration type    */
    {
        saturday,       /* Names day and declares a       */
        sunday,     /* variable named workday with    */
        monday,         /* that type                      */
        tuesday,
        wednesday,      /* wednesday is associated with 3 */
        thursday,
        friday
    } workday;
    int a = 2;
    enum DAY today = ( enum DAY ) a-1;
    return 0;
} 