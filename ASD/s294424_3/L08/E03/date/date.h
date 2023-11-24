#ifndef DATE_H_DEFINED
#define DATE_H_DEFINED
#include <stdio.h>
#include <stdlib.h>


typedef struct date_s * Date;

struct date_s{
    int year;
    int month;
    int day;
    long unix_time;
    int hour;
    int minute;
};

long DATEConvertDateToUnixTime(struct date_s date);
struct date_s DATEInit(int year, int month, int day, int hour, int minute);

#endif
