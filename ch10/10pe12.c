/* 10pe12.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure named census with the following three members:
 * -A character array city[] to store names
 * -A long integer to store population of the city
 * -A float member to store the literacy level
 *
 * Write a program to do the following:
 * -To read details for 5 cities randomly using an array variable,
 * -To sort the list alphabetically
 * -To sort the list based on literacy level
 * -To sort the list based on population
 * -To display sorted lists
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe12.c -o binary/10pe12
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
#define TITLE "CITIES IN CENSUS STRUCT. CITY SORT FUNCTIONS"
#define CFGDEBUG 1
#define CITY_LENGTH 32
#define DB_SIZE 5

/* BEGIN: FLUSH */
#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif defined __unix__
#define FLUSH fpurge(stdin);
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH */

struct census_t {
	char city[CITY_LENGTH];
	long int population;
	float literacy;
};

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
void zInitAllEntries(struct census_t db[DB_SIZE]);
void displayAllCities(struct census_t db[DB_SIZE]);
void displayMsgReqInputCityName(void);
void displayMsgReqInputCityPopulation(void);
void displayMsgReqInputCityLiteracy(void);
void handleDataInputCity(struct census_t db[DB_SIZE], int id);
void handleDataInputPopulation(struct census_t db[DB_SIZE], int id);
void handleDataInputLiteracy(struct census_t db[DB_SIZE], int id);
void handleDataEntry(struct census_t db[DB_SIZE], int id);
int cmpAlphabeticalAsc(const void *v1, const void *v2); /* Ascending */
int cmpPopulationAsc(const void *v1, const void *v2);   /* Ascending */
int cmpLiteracyAsc(const void *v1, const void *v2);     /* Ascending */
void sortAlphabeticAsc(struct census_t db[DB_SIZE]);    /* Ascending */
void sortPopulationAsc(struct census_t db[DB_SIZE]);    /* Ascending */
void sortLiteracyAsc(struct census_t db[DB_SIZE]);      /* Ascending */
void fillWithTestData(struct census_t db[DB_SIZE]);
void actionChoice(int choice, struct census_t db[DB_SIZE]);
void printMainMenu(void);
int getChoice(void);
void mainLoop(struct census_t db[DB_SIZE]);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct census_t db[DB_SIZE];

	cls();
	displayHeaderLine();
	displayHeaderText();
	zInitAllEntries(db);
	fillWithTestData(db);
	mainLoop(db);
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
void zInitAllEntries(struct census_t db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		strcpy(db[n].city, "not-in-use");
		db[n].population = -1;
		db[n].literacy = -1.f;
	}
}

void displayAllCities(struct census_t db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		printf("---------- RECORD ID: %d ----------------\n", n);
		printf("City:\t\t%s\n", db[n].city);
		printf("Population:\t%ld\n", db[n].population);
		printf("Literacy:\t%02.02f\n\n", db[n].literacy);
	}
}

void displayMsgReqInputCityName(void) { printf("Enter city name: "); }

void displayMsgReqInputCityPopulation(void)
{
	printf("Enter city's population: ");
}

void displayMsgReqInputCityLiteracy(void)
{
	printf("Enter city's literacy rate: ");
}

void handleDataInputCity(struct census_t db[DB_SIZE], int id)
{
	char s[CITY_LENGTH];

	displayMsgReqInputCityName();
	/* TODO switch to secure string entry here */
	scanf("%s", s);
	strcpy(db[id].city, s);
}

void handleDataInputPopulation(struct census_t db[DB_SIZE], int id)
{
	long int p;

	displayMsgReqInputCityPopulation();
	scanf("%ld", &p);
	db[id].population = p;
}

void handleDataInputLiteracy(struct census_t db[DB_SIZE], int id)
{
	float f;

	displayMsgReqInputCityLiteracy();
	scanf("%f", &f);
	db[id].literacy = f;
}

void handleDataEntry(struct census_t db[DB_SIZE], int id)
{
	/* set city name */
	handleDataInputCity(db, id);

	/* set population */
	handleDataInputPopulation(db, id);

	/* set literacy rate */
	handleDataInputLiteracy(db, id);
}

int cmpAlphabeticalAsc(const void *v1, const void *v2) /* Ascending */
{
	const struct census_t *p1 = (struct census_t *)v1;
	const struct census_t *p2 = (struct census_t *)v2;
	int r = strcmp(p1->city, p2->city);

	if (r < 0) {
		return -1;
	} else if (r > 0) {
		return +1;
	} else {
		return 0;
	}
}

int cmpPopulationAsc(const void *v1, const void *v2) /* Ascending */
{
	const struct census_t *p1 = (struct census_t *)v1;
	const struct census_t *p2 = (struct census_t *)v2;
	if (p1->population < p2->population) {
		return -1;
	} else if (p1->population > p2->population) {
		return +1;
	} else {
		return 0;
	}
}

int cmpLiteracyAsc(const void *v1, const void *v2) /* Ascending */
{
	const struct census_t *p1 = (struct census_t *)v1;
	const struct census_t *p2 = (struct census_t *)v2;
	if (p1->literacy < p2->literacy) {
		return -1;
	} else if (p1->literacy > p2->literacy) {
		return +1;
	} else {
		return 0;
	}
}

void sortAlphabeticAsc(struct census_t db[DB_SIZE]) /* Ascending */
{
	qsort(db, DB_SIZE, sizeof(struct census_t), cmpAlphabeticalAsc);
}

void sortPopulationAsc(struct census_t db[DB_SIZE]) /* Ascending */
{
	qsort(db, DB_SIZE, sizeof(struct census_t), cmpPopulationAsc);
}

void sortLiteracyAsc(struct census_t db[DB_SIZE]) /* Ascending */
{
	qsort(db, DB_SIZE, sizeof(struct census_t), cmpLiteracyAsc);
}

/*
 * Population: I have used Wikipedia data for each city (metropolitan area).
 *
 * Literacy Rate:
 * It has proven difficult to find city 'Literacy Rate' data online.
 * Instead I would use country literacy data however these 5 countries all have
 * 99% literacy rate, making it impossible to demonstrate sort-by-literacy-rate
 * feature.
 * Therefore, I have decided to to use made-up unique literacy rate for each
 * city for demonstration purposes.
 */
void fillWithTestData(struct census_t db[DB_SIZE])
{
	strcpy(db[0].city, "London");
	db[0].population = 14040163;
	db[0].literacy = 92.0f;

	strcpy(db[1].city, "New York City");
	db[1].population = 20320876;
	db[1].literacy = 97.0f;

	strcpy(db[2].city, "Paris");
	db[2].population = 12405426;
	db[2].literacy = 96.f;

	strcpy(db[3].city, "Tokyo");
	db[3].population = 38305000;
	db[3].literacy = 100.f;

	strcpy(db[4].city, "Berlin");
	db[4].population = 6004857;
	db[4].literacy = 91.f;
}

void actionChoice(int choice, struct census_t db[DB_SIZE])
{
	switch (choice) {
	case 0:
		printf("\nACTIONING: DISPLAY all cities\n");
		displayAllCities(db);
		break;
	case 1:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 0);
		break;
	case 2:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 1);
		break;
	case 3:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 2);
		break;
	case 4:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 3);
		break;
	case 5:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 4);
		break;
	case 6:
		printf("\nACTIONING: SORT alphabetically\n");
		sortAlphabeticAsc(db);
		displayAllCities(db);
		break;
	case 7:
		printf("\nACTIONING: SORT based on population\n");
		sortPopulationAsc(db);
		displayAllCities(db);
		break;
	case 8:
		printf("\nACTIONING: SORT based on literacy level\n");
		sortLiteracyAsc(db);
		displayAllCities(db);
		break;
	case 9:
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
	       "\t0: DISPLAY all cities\n"
	       "\t1: ENTER/UPDATE data for city slot #1\n"
	       "\t2: ENTER/UPDATE data for city slot #2\n"
	       "\t3: ENTER/UPDATE data for city slot #3\n"
	       "\t4: ENTER/UPDATE data for city slot #4\n"
	       "\t5: ENTER/UPDATE data for city slot #5\n"
	       "\t6: SORT alphabetically\n"
	       "\t7: SORT based on population\n"
	       "\t8: SORT based on literacy level\n"
	       "\t9: EXIT program\n"
	       "Enter your choice: ",
	       title);
}

int getChoice(void)
{
#define ENTRY_LOWEST 0
#define ENTRY_HIGHEST 9

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

void mainLoop(struct census_t db[DB_SIZE])
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, db);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
