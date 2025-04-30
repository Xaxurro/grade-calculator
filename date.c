#include <stdio.h>
#include "date.h"

date stringToDate(char *str) {
	date date;
	if (sscanf(str, "%d-%d", &date.day, &date.month) == 2) {
		return date;
	} 
	fprintf(stderr, "ERROR: Expected DD-MM format\n");
	date.day = 0;
	date.month = 0;
	return date;
}

/* returns 1 if date1 is bigger than date2
 * returns -1 if date2 is bigger than date1 
 * returns 0 if date1 equals date2 
 * always considers error dates (day && month == 0) as the biggest
 * meaning that it will be always at the end of the array*/
int compareDates(date date1, date date2) {
	if (date1.day != 0 && date2.day == 0) return -1;
	if (date1.day == 0 && date2.day != 0) return 1;
	if (date1.day == 0 && date2.day == 0) return 0;

	int difference = date1.month - date2.month;
	if (difference > 0) {
		return 1;
	}
	if (difference < 0) {
		return -1;
	}

	difference = date1.day - date2.day;
	if (difference > 0) {
		return 1;
	}
	if (difference < 0) {
		return -1;
	}
	return 0;
}
