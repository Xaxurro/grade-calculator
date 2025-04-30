#ifndef GRADE_H
#define GRADE_H
#include <stdio.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

#include "date.h"
typedef struct grade {
	double weight;
	double score;
	char* subject;
	date date;
	bool hasScore;
} grade;

int getGradeArraySize();
grade getGrade(int index);

void addGrade(cJSON *subject, cJSON *weight, cJSON *score, cJSON *date);
void printGrade(grade grade);
double getWeightedScore(grade grade);
void sortGrades();
#endif
