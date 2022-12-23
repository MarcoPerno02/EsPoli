#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "date.h"

long DATEConvertDateToUnixTime(Date date) {
    struct tm t ={0};
    time_t t_of_day;
    t.tm_year = (date->year)-1900;  // Year - 1900
    t.tm_mon = (date->month)-1;     // Month, where 0 = jan
    t.tm_mday = date->day;
    t.tm_hour = date->hour;
    t.tm_min = date->minute;
    t_of_day = mktime(&t);
    return t_of_day;
}

Date DATEInit(int year, int month, int day, int hour, int minute) {
    Date date = malloc(sizeof(struct date_s));
    date->year = year;
    date->month = month;
    date->day = day;
    date->hour = hour;
    date->minute = minute;
    date->unix_time = DATEConvertDateToUnixTime(date);
    return date;
}

Date DATEFree(Date date) {
    free(date);
}
