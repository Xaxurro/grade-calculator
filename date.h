#ifndef DATE_H
#define DATE_H
#include <stdlib.h>
typedef struct date {
	int day;
	int month;
} date;

date stringToDate(char *str);
int compareDates(date date1, date date2);
#endif
