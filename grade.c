#include "grade.h"
#include "date.h"

#define MAX_GRADES 32
#define MAX_SCORE 100

static grade gradeArray[MAX_GRADES];
static int gradeArraySize = 0;

int getGradeArraySize() {
	return gradeArraySize;
}

grade getGrade(int index) {
	return gradeArray[index];
}

void addGrade(cJSON *subject, cJSON *weight, cJSON *score, cJSON *date) {
	grade newGrade;

	/* subject */
	if (subject != NULL) {
		newGrade.subject = cJSON_GetStringValue(subject);
	}

	/* weight */
	if (weight  != NULL) {
		newGrade.weight = cJSON_GetNumberValue(weight);
	}

	/* score */
	if (score != NULL) {
		newGrade.score = cJSON_GetNumberValue(score);
		newGrade.hasScore = true;
	} else {
		newGrade.hasScore = false;
	}

	/* date */
	if (date != NULL) {
		newGrade.date = stringToDate(cJSON_GetStringValue(date));
	} else {
		newGrade.date = stringToDate("0-0");
	}

	gradeArray[gradeArraySize] = newGrade;
	gradeArraySize += 1;
}

void printGrade(grade grade) {
	printf("\t%s(%d-%d): %.0f%% -> %.0f\n", grade.subject, grade.date.day, grade.date.month, grade.weight * 100, grade.score);
}

double getWeightedScore(grade grade) {
	return grade.score * grade.weight;
}

void sortGrades() {
	/* bubble sort */
	for (int i = 0; i < gradeArraySize - 1; i++) {
		for (int j = 0; j < gradeArraySize - i - 1; j++) {
			if (compareDates(gradeArray[j].date, gradeArray[j + 1].date) == 1) {
				grade temporal = gradeArray[j];
				gradeArray[j] = gradeArray[j + 1];
				gradeArray[j + 1]  = temporal;
			}
		}
	}
}

