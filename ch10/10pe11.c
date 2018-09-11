/* 10pe11.c */
/* ===================================80 chars=============================== */

/*
 * Create two structures named metric and British which store the values of
 * distances. The metric structure stores the values in metres and centimetres
 * and the British structure stores the values in feet and inches. Write a
 * program that reads values for the structure variables and adds values
 * contained in one variable of metric to the contents of another variable of
 * British. The program should display the result in the format of feet and
 * inches or metres and centimetres as required.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe11.c -o binary/10pe11
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "METRIC AND BRITISH STRUCTS"
#define CFGDEBUG 0

/* BEGIN: FLUSH rev.03 */
#ifdef _WIN32
#define FLUSH fflush(stdin);
/*#elif defined __unix__
#define FLUSH fpurge(stdin);*/
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#elif defined __gnu_linux__
#include <stdio_ext.h>
#define FLUSH __fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH rev.03 */

struct len_metric_t {
	int mt; /* meters */
	int cm; /* centimeters */
};

struct len_british_t {
	int ft; /* foot */
	int in; /* inches */
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
int takeInputInt(void);
void displayMessageRequestMetricCm(void);
void displayMessageRequestMetricMt(void);
void handleDataInputMetric(struct len_metric_t *sm);
void displayMessageRequestBritishFt(void);
void displayMessageRequestBritishIn(void);
void handleDataInputBritish(struct len_british_t *sb);
void displayBothStructs(struct len_metric_t *sm, struct len_british_t *sb);
void convertCopyMetricToBritish(struct len_metric_t *sm,
				struct len_british_t *sb);
void convertCopyBritishToMetric(struct len_metric_t *sm,
				struct len_british_t *sb);
void actionChoice(int choice, struct len_metric_t *sm,
		  struct len_british_t *sb);
void printMainMenu(void);
int getChoice(void);
void mainLoop(struct len_metric_t *sm, struct len_british_t *sb);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct len_metric_t sm = {0, 0};
	struct len_british_t sb = {0, 0};

	cls();
	displayHeaderLine();
	displayHeaderText();
	mainLoop(&sm, &sb);
	displayFooter();

	return EXIT_SUCCESS;
}
/**************************************/
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeaderLine(void)
{
	int n;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}

void displayHeaderText(void)
{
	char s[] = TITLE;
	printf("%s\n", s);
}

void displayFooter(void)
{
	int n = 0;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}
/**************************************/
int takeInputInt(void)
{
	int ret;
	scanf("%d", &ret);
	return ret;
}

void displayMessageRequestMetricCm(void)
{
	printf("Enter centimeters value: ");
}

void displayMessageRequestMetricMt(void)
{
	printf("Enter meters value: ");
}

void handleDataInputMetric(struct len_metric_t *sm)
{
	int mt, cm;
	displayMessageRequestMetricMt();
	mt = takeInputInt();
	displayMessageRequestMetricCm();
	cm = takeInputInt();
	sm->mt = mt;
	sm->cm = cm;
}

void displayMessageRequestBritishFt(void)
{
	printf("Enter feets value: ");
}

void displayMessageRequestBritishIn(void)
{
	printf("Enter inches value: ");
}

void handleDataInputBritish(struct len_british_t *sb)
{
	int ft, in;
	displayMessageRequestBritishFt();
	ft = takeInputInt();
	displayMessageRequestBritishIn();
	in = takeInputInt();
	sb->ft = ft;
	sb->in = in;
}

void displayBothStructs(struct len_metric_t *sm, struct len_british_t *sb)
{
	printf("Metric struct: %d m, %d cm\n", sm->mt, sm->cm);
	printf("British struct: %d ft, %d in\n", sb->ft, sb->in);
}

void convertCopyMetricToBritish(struct len_metric_t *sm,
				struct len_british_t *sb)
{
	int total_cm = (sm->mt * 100) + (sm->cm);
	int total_in = total_cm / 2.54;
	sb->ft = total_in / 12;
	sb->in = total_in % 12;
	printf("Converted and saved into British struct: %dm %dcm = %dft %din\n"
	       , sm->mt, sm->cm, sb->ft, sb->in);
}

void convertCopyBritishToMetric(struct len_metric_t *sm,
				struct len_british_t *sb)
{
	int total_in = (sb->ft * 12) + sb->in;
	int total_cm = total_in * 2.54;
	sm->mt = total_cm / 100;
	sm->cm = total_cm % 100;

	printf("Converted and saved into Metric struct: %dft %din = %dm %dcm",
	       sb->ft, sb->in, sm->mt, sm->cm);
}

void actionChoice(int choice, struct len_metric_t *sm, struct len_british_t *sb)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: ENTER/UPDATE data into the Metric "
		       "struct\n");
		handleDataInputMetric(sm);
		break;
	case 2:
		printf("\nACTIONING: ENTER/UPDATE data into the British "
		       "struct\n");
		handleDataInputBritish(sb);
		break;
	case 3:
		printf("\nACTIONING: DISPLAY both structs\n");
		displayBothStructs(sm, sb);
		break;
	case 4:
		printf("\nACTIONING: CONVERT & COPY into: Metric -> British\n");
		convertCopyMetricToBritish(sm, sb);
		break;
	case 5:
		printf("\nACTIONING: CONVERT & COPY into: Metric <- British\n");
		convertCopyBritishToMetric(sm, sb);
		break;
	case 6:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
	default:
		printf("ERROR: hit default entry in switch?!\n");
		exit(EXIT_FAILURE);
	}
}

void printMainMenu(void)
{
	/* without this ugly hack double quotes do get printed :( */
	char title[] = XSTR(TITLE);
	unsigned int len = strlen(title);
	title[0] = ' ';       /* first double quote */
	title[len - 1] = ' '; /* second double quote */

	printf("\n\n\n***%s- MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: ENTER/UPDATE data into the Metric struct\n"
	       "\t2: ENTER/UPDATE data into the British struct\n"
	       "\t3: DISPLAY both structs\n"
	       "\t4: CONVERT & COPY into Metric -> British\n"
	       "\t5: CONVERT & COPY into Metric <- British\n"
	       "\t6: EXIT program\n"
	       "Enter your choice: ",
	       title);
}

int getChoice(void)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 6

	int num;

	do {
		printMainMenu();
		FLUSH
		scanf("%d", &num);
		if (num < ENTRY_LOWEST || num > ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < ENTRY_LOWEST || num > ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void mainLoop(struct len_metric_t *sm, struct len_british_t *sb)
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, sm, sb);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
