#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#include "grade.h"

int readFile(char *filename, char *buffer, int bufferSize) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error: Unable to open file %s.\n", filename);
		return -1;
	}
	int length = fread(buffer, 1, bufferSize, fp);
	fclose(fp);
	return length;
}

cJSON* readJson(char *buffer) {
	cJSON *json = cJSON_Parse(buffer);
	if (json == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL) {
			printf("ERROR: %s\n", error_ptr);
		}
		cJSON_Delete(json);
	}
	return json;
}

double getScoreTotal() {
	double scoreTotal = 0;
	for (int i = 0; i < getGradeArraySize(); i++) {
		grade grade = getGrade(i);
		if (grade.hasScore) {
			scoreTotal += grade.score * grade.weight;
		}
	}
	return scoreTotal;
}

void printScoresCurrent() {
	printf("---------------\n");
	printf("CURRENT SCORES:\n");
	printf("---------------\n");
	for (int i = 0; i < getGradeArraySize(); i++) {
		grade grade = getGrade(i);
		if (grade.hasScore) {
			printGrade(grade);
		}
	}

}

void printScoresRemaining(double scoreMinimum, double scoreTotal) {
	printf("\n------------------------\n");
	printf("REQUIRED SCORES TO PASS:\n");
	printf("------------------------\n");

	double scoreRemaining = scoreMinimum - scoreTotal;
	for (int i = 0; i < getGradeArraySize(); i++) {
		grade grade = getGrade(i);
		if (!grade.hasScore) {
			double scoreNew = scoreRemaining * (1/grade.weight);
			if (scoreNew > 100) {
				scoreNew = 100;
			}
			if (scoreNew < 0) {
				scoreNew = 0;
			}
			scoreRemaining -= scoreNew * grade.weight;
			grade.score = scoreNew;
			printGrade(grade);
		}
	}
}

int main(int argc, char *argv[])
{
	char bufferJSON[1024];
	int fileLength = readFile(argv[1], bufferJSON, sizeof(bufferJSON));
	cJSON *json = readJson(bufferJSON);
	
	double scoreMinimum = cJSON_GetObjectItem(json, "minimum")->valuedouble;

	cJSON *gradeJSON = cJSON_GetObjectItem(json, "grades");
	cJSON *gradeNew = NULL;

	cJSON_ArrayForEach(gradeNew, gradeJSON) {
		cJSON *subject = cJSON_GetObjectItem(gradeNew, "subject");
		cJSON *weight = cJSON_GetObjectItem(gradeNew, "weight");
		cJSON *score = cJSON_GetObjectItem(gradeNew, "score");
		cJSON *date = cJSON_GetObjectItem(gradeNew, "date");

		addGrade(subject, weight, score, date);
	}

	sortGrades();

	printScoresCurrent();
	double scoreTotal = getScoreTotal();
	printScoresRemaining(scoreMinimum, scoreTotal);

	printf("\ntotal score: %.2f\n", scoreTotal);
	printf("minimum score: %.2f\n", scoreMinimum);

	cJSON_Delete(json);
	return 0;
}
