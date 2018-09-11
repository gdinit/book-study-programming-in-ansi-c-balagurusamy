/* 10pe15.c */
/* ===================================80 chars=============================== */

/*
 * Design a structure student_record to contain name, date of birth, and total
 * marks obtained. Use the date structure designed in Exercise 10.4 to represent
 * the date of birth.
 *
 * Develop a program to read data for 10 students in a class and list them rank
 * wise.
 */

/*
 * Improvement Ideas 
 *
 * -Revisit all sections in code marked with TODO.
 * -Change validate input behaviour so that a bad date entry attempt won't kill
 *  program's execution but only display error message and return & request
 *  entry.
 * -Improve const correctness.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe15.c -o binary/10pe15
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "STUDENT & DATE STRUCTS"
#define CFGDEBUG 1
/**************************************/
#define NAME_LENGTH 15
#define NAME_LENGTH_PLUS_ONE 16
#define DB_SIZE 10
#define PAGINATION 25
#define MENU_ENTRY_LOWEST 1
#define MENU_ENTRY_HIGHEST 4
#define MAX_MARK 150

#define YEAR_MIN 1
#define YEAR_MAX 2400
#define YEAR_UNKNOWN -1
#define YEAR_COMMON 0
#define YEAR_LEAP 1
#define LEGALITY_UNKNOWN -9
#define LEGALITY_ILLEGAL -1
#define LEGALITY_LEGAL 0

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

/**************************************/
struct date_t {
	int d;
	int m;
	int y;
};

struct student_t {
	char name[NAME_LENGTH_PLUS_ONE];
	struct date_t dob;
	int mark;
};
/**************************************/
enum CountryNames {
	Not_in_use,
	Australia,
	England,
	India,
	New_Zealand,
	Pakistan,
	South_Africa,
	Sri_Lanka,
	West_Indies,
	Zimbabwe,
	COUNTRY_COUNT_PLUS_ONE
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void printMainMenu(void);
void actionChoice(int choice, struct student_t db[DB_SIZE]);
int getChoice(void);
void zInitAllEntries(struct student_t db[DB_SIZE]);
void mainLoop(struct student_t db[DB_SIZE]);
void fillWithTestData(struct student_t db[DB_SIZE]);
void toUpperStr(char *p_str);
void toUpperFirstCharLowerRest(char *p_str);
void displayOneEntry(const struct student_t db[DB_SIZE], const int id);
void displayAllEntries(struct student_t db[DB_SIZE]);
void displayMsgReqInputChooseID(void);
void enforceCapitalisationPolicy(struct student_t db[DB_SIZE]);
void enforceCapitalisationPolicy1(struct student_t db[DB_SIZE], int id);
void displayMsgReqInputName(void);
void handleDataInputName(struct student_t db[DB_SIZE], int id);
void displayMsgReqInputMark(void);
void handleDataInputMark(struct student_t db[DB_SIZE], int id);
void displayMsgReqInputDOB(void);
int checkIfLeap(int year, int print_out);
void validateDateInput(struct date_t *d);
void handleDataInputDOB(struct student_t db[DB_SIZE], int id);
int handleChooseEntryToEdit(void);
void handleDataEntry(struct student_t db[DB_SIZE]);
void zInitEntry(struct student_t *s);
int cmpMarkDesc(const void *v1, const void *v2);
void sortMarkDesc(struct student_t db[DB_SIZE]);
int cmpAlphabeticalAsc(const void *v1, const void *v2);
void sortNameAlphabeticAsc(struct student_t db[DB_SIZE]);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct student_t db[DB_SIZE];

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
void printMainMenu(void)
{
	/* without this ugly hack double quotes do get printed :( */
	char title[] = XSTR(TITLE);
	unsigned int len = strlen(title);
	title[0] = ' ';       /* first double quote */
	title[len - 1] = ' '; /* second double quote */

	printf("\n***%s- MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: DISPLAY All Students Order by Name (asc.)\n"
	       "\t2: DISPLAY All Students Order by Rank (desc.)\n"
	       "\t3: ENTER/UPDATE Data for a Student\n"
	       "\t4: EXIT Program\n"
	       "Enter your choice: ",
	       title);
}

void actionChoice(int choice, struct student_t db[DB_SIZE])
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: DISPLAY All Students Order by Name (asc.)"
		       "\n");
		sortNameAlphabeticAsc(db);
		displayAllEntries(db);
		break;
	case 2:
		printf("\nACTIONING: DISPLAY All Students Order by Rank (desc.)"
		       "\n");
		sortMarkDesc(db);
		displayAllEntries(db);
		break;
	case 3:
		printf("\nACTIONING: ENTER/UPDATE Data for a Student\n");
		handleDataEntry(db);
		break;
	case 4:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
	default:
		printf("ERROR: hit default entry in switch?!\n");
		exit(EXIT_FAILURE);
	}
}

int getChoice(void)
{
	int num;

	do {
		printMainMenu();
		FLUSH
		scanf("%d", &num);
		if (num < MENU_ENTRY_LOWEST || num > MENU_ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < MENU_ENTRY_LOWEST || num > MENU_ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void zInitAllEntries(struct student_t db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		strcpy(db[n].name, "z"); /* fill with Z but display as - */
		db[n].dob.d = 0;
		db[n].dob.m = 0;
		db[n].dob.y = 0;
		db[n].mark = 0;
	}
}

void mainLoop(struct student_t db[DB_SIZE])
{
	int firstRun = 1;
	int choice;

	while (1) {
		if (firstRun) {
			choice = 1; /* show entries on initial run */
		} else {
			choice = getChoice();
		}
		actionChoice(choice, db);
		if (firstRun) {
			firstRun = 0;
		}
	}
}

void fillWithTestData(struct student_t db[DB_SIZE])
{
	strcpy(db[0].name, "Bradman");
	db[0].dob.d = 19;
	db[0].dob.m = 6;
	db[0].dob.y = 1998;
	db[0].mark = 140;

	strcpy(db[1].name, "Voges");
	db[1].dob.d = 21;
	db[1].dob.m = 3;
	db[1].dob.y = 1987;
	db[1].mark = 61;

	strcpy(db[2].name, "Smith");
	db[2].dob.d = 11;
	db[2].dob.m = 4;
	db[2].dob.y = 1984;
	db[2].mark = 91;

	strcpy(db[3].name, "Pollock");
	db[3].dob.d = 1;
	db[3].dob.m = 3;
	db[3].dob.y = 1966;
	db[3].mark = 58;

	strcpy(db[4].name, "Headley");
	db[4].dob.d = 9;
	db[4].dob.m = 7;
	db[4].dob.y = 1977;
	db[4].mark = 82;

	strcpy(db[5].name, "Sutcliffe");
	db[5].dob.d = 8;
	db[5].dob.m = 11;
	db[5].dob.y = 1955;
	db[5].mark = 48;

	strcpy(db[6].name, "Paynter");
	db[6].dob.d = 28;
	db[6].dob.m = 2;
	db[6].dob.y = 1947;
	db[6].mark = 28;

	strcpy(db[7].name, "Barrington");
	db[7].dob.d = 5;
	db[7].dob.m = 6;
	db[7].dob.y = 1967;
	db[7].mark = 28;

	strcpy(db[8].name, "Weekes");
	db[8].dob.d = 5;
	db[8].dob.m = 8;
	db[8].dob.y = 1962;
	db[8].mark = 88;

	strcpy(db[9].name, "Hammond");
	db[9].dob.d = 2;
	db[9].dob.m = 6;
	db[9].dob.y = 1958;
	db[9].mark = 38;

	enforceCapitalisationPolicy(db);
}

void toUpperStr(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);

	for (n = 0; n < len; n++) {
		p_str[n] = toupper(p_str[n]);
	}
}

void toUpperFirstCharLowerRest(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);

	for (n = 0; n < len; n++) {
		p_str[n] = tolower(p_str[n]);
	}
	p_str[0] = toupper(p_str[0]);
}

void displayOneEntry(const struct student_t db[DB_SIZE], const int id)
{
	int n = id;
	static char idn[] = "ID";
	static char nam[] = "NAME";
	static char dob[] = "DATE OF BIRTH";
	static char mar[] = "TOTAL MARKS";
	/* blank entries in db is stored as 'z' 
	 * but during display this string is shown */
	const static char bla[] = "-";

	printf("-----------------------------------------------"
	       "-----------------------------------------\n");
	if (0 == n) {
		printf("LISTING ONE STUDENT\n");
	}
	/* id number is just a visual cue to assist user when
	 * entering data */
	printf("%-2s", idn);
	printf(" | %-14s", nam);
	/* DOB style: DD-MM-YYYY -- e.g.: 09-08-1979 */
	printf(" | %-13s", dob);
	printf(" | %10s\n", mar);

	printf("%02d | ", n + 1);
	/* print name */
	if ('z' == db[n].name[0]) {
		printf("%-14s | ", bla);
	} else {
		printf("%-14s | ", db[n].name);
	}
	printf("%02d-%02d-%04d    | ", /*         DOB style: DD-MM-YYYY */
	       db[n].dob.d, db[n].dob.m, db[n].dob.y); /* 09-08-1979 */
	printf("%11d\n", db[n].mark);

	printf("\nDISPLAYED ONE STUDENT.\n"
	       "-----------------------------------------------"
	       "-----------------------------------------\n");
}

void displayAllEntries(struct student_t db[DB_SIZE])
{
	int n;
	static char idn[] = "ID";
	static char nam[] = "NAME";
	static char dob[] = "DATE OF BIRTH";
	static char mar[] = "TOTAL MARKS";
	/* blank entries in db is stored as 'z' 
	 * but during display this string is shown */
	const static char bla[] = "-";

	for (n = 0; n < DB_SIZE; n++) {
		if (n % PAGINATION == 0) {
			printf("-----------------------------------------------"
			       "-----------------------------------------\n");
			if (0 == n) {
				printf("LISTING ALL STUDENTS\n\n");
			}
			/* id number is just a visual cue to assist user when
			 * entering data */
			printf("%-2s", idn);
			printf(" | %-14s", nam);
			/* DOB style: DD-MM-YYYY -- e.g.: 09-08-1979 */
			printf(" | %-13s", dob);
			printf(" | %10s\n", mar);
		}

		printf("%02d | ", n + 1);
		/* print name */
		if ('z' == db[n].name[0]) {
			printf("%-14s | ", bla);
		} else {
			printf("%-14s | ", db[n].name);
		}
		printf("%02d-%02d-%04d    | ", /*         DOB style: DD-MM-YYYY */
		       db[n].dob.d, db[n].dob.m, db[n].dob.y); /* 09-08-1979 */
		printf("%11d\n", db[n].mark);
	}
	printf("\nDISPLAYED %d STUDENTS.\n"
	       "-----------------------------------------------"
	       "-----------------------------------------\n",
	       n);
}

void displayMsgReqInputChooseID(void)
{
	printf(
	    "Enter the record ID to modify (min: 1, max: " XSTR(DB_SIZE) "): ");
}

void enforceCapitalisationPolicy(struct student_t db[DB_SIZE])
{
	int n;

	for (n = 0; n < DB_SIZE; n++) {
		enforceCapitalisationPolicy1(db, n);
	}
}


/* Lastname should be first letter uppercase, rest lowercase e.g.: Johnson */
void enforceCapitalisationPolicy1(struct student_t db[DB_SIZE], int id)
{
	toUpperFirstCharLowerRest(db[id].name);
}

void displayMsgReqInputName(void)
{
	printf("Enter student's name (" XSTR(NAME_LENGTH) " chars max): ");
}

void handleDataInputName(struct student_t db[DB_SIZE], int id)
{
	char s[NAME_LENGTH_PLUS_ONE];

	displayMsgReqInputName();
	FLUSH
	scanf("%" XSTR(NAME_LENGTH) "[^\n]", s);
	toUpperFirstCharLowerRest(s);
	strcpy(db[id].name, s); /* TODO: use safer string copy (str5cpy) */
}

void displayMsgReqInputMark(void)
{
	printf("Enter student's marks total (e.g.: 90): ");
}

void handleDataInputMark(struct student_t db[DB_SIZE], int id)
{
	int n;

	do {
		displayMsgReqInputMark();
		FLUSH
		scanf("%d", &n);
		if (n < 0 || n >= MAX_MARK) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 0 || n >= MAX_MARK);
	db[id].mark = n;
}

void displayMsgReqInputDOB(void)
{
	printf("Enter student's Date of Birth in DD MM YYYY format (e.g.: 24 12"
	       " 1980): ");
}

int checkIfLeap(int year, int print_out)
{
	int r = YEAR_UNKNOWN;

	if (year % 4 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = YEAR_COMMON;
	} else if (year % 100 != 0) {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = YEAR_LEAP;
	} else if (year % 400 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = YEAR_COMMON;
	} else {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = YEAR_LEAP;
	}

	return r;
}

/* in case of any errors, will abruptly terminate the program execution */
void validateDateInput(struct date_t *d)
{
	int is_leap = checkIfLeap(d->y, 0);

	/* Eliminate obvious issues: YEAR */
	if (d->y < YEAR_MIN) {
		printf("ERROR: Illegal year -- too low value: %d! Supported "
		       "min year is: " XSTR(YEAR_MIN) "\n",
		       d->y);
		exit(EXIT_FAILURE);
	} else if (d->y > YEAR_MAX) {
		printf("ERROR: Illegal year -- too high value: %d! Supported "
		       "max year is: " XSTR(YEAR_MAX) "\n",
		       d->y);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: MONTH */
	if (d->m < 1 || d->m > 12) {
		printf("ERROR: Illegal month: %d!\n", d->m);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: DAY */
	if (d->d < 1 || d->d > 31) {
		printf("ERROR: Illegal day of month: %d!\n", d->d);
		exit(EXIT_FAILURE);
	}

	/*
	Second Pass on Month

	The 12 Months
	The Gregorian calendar consists of the following 12 months:
		January - 31 days
		February - 28 days in a common year and
			   29 days in leap years
		March - 31 days
		April - 30 days
		May - 31 days
		June - 30 days
		July - 31 days
		August - 31 days
		September - 30 days
		October - 31 days
		November - 30 days
		December - 31 days
	*/
	switch (d->m) {
	case 2:				       /* FEB */
		if (d->d >= 1 && d->d <= 28) { /* legal */
			break;
		} else if (is_leap && d->d == 29) { /* legal */
			break;
		} else if (!is_leap && d->d == 29) {
			printf("%d is a common year, February cannot be %d days"
			       "! \n",
			       d->y, d->d);
			exit(EXIT_FAILURE);
		} else if (d->d >= 30) {
			printf("February can never have %d days!\n", d->d);
			exit(EXIT_FAILURE);
		}
	case 1:  /* JAN */
	case 3:  /* MAR */
	case 5:  /* MAY */
	case 7:  /* JUL */
	case 8:  /* AUG */
	case 10: /* OCT */
	case 12: /* DEC */
		if (d->d > 31) {
			printf("ERROR: Too many days %d in month %d!\n", d->d,
			       d->m);
			exit(EXIT_FAILURE);
		} else {
			break;
		}
	case 4:  /* APR */
	case 6:  /* JUN */
	case 9:  /* SEP */
	case 11: /* NOV */
		if (d->d > 30) {
			printf("ERROR: Too many days %d in month %d!\n", d->d,
			       d->m);
			exit(EXIT_FAILURE);
		} else {
			break;
		}
	default:
		printf("ERROR: INVALID MONTH ENTRY (d->m = %d)\n", d->m);
		exit(EXIT_FAILURE);
	}
}


void handleDataInputDOB(struct student_t db[DB_SIZE], int id)
{
	struct date_t d;
	int validated = 0;

	do {
		displayMsgReqInputDOB();
		FLUSH
		scanf("%d %d %d", &d.d, &d.m, &d.y);
		validateDateInput(&d);
		validated = 1;
	} while (!validated);
	db[id].dob = d;
}

int handleChooseEntryToEdit(void)
{
	int n = -1;

	do {
		displayMsgReqInputChooseID();
		FLUSH
		scanf("%d", &n);
		if (n < 1 || n > DB_SIZE) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 1 || n > DB_SIZE);

	return n;
}

void handleDataEntry(struct student_t db[DB_SIZE])
{
	int id = -2;
	id = handleChooseEntryToEdit();
	id--; /* array starts with record id 0 */
	handleDataInputName(db, id);
	handleDataInputMark(db, id);
	handleDataInputDOB(db, id);
	enforceCapitalisationPolicy1(db, id);
	printf("Updated record %d as follows:\n", id + 1);
	displayOneEntry(db, id);
}

void zInitEntry(struct student_t *s)
{
	strcpy(s->name, "z");
	s->dob.d = 0;
	s->dob.m = 0;
	s->dob.y = 0;
	s->mark = 0;
}

int cmpMarkDesc(const void *v1, const void *v2) /* Descending */
{
	const struct student_t *p1 = (struct student_t *)v1;
	const struct student_t *p2 = (struct student_t *)v2;
	if (p1->mark < p2->mark) {
		return +1;
	} else if (p1->mark > p2->mark) {
		return -1;
	} else {
		return 0;
	}
}

void sortMarkDesc(struct student_t db[DB_SIZE]) /* Descending */
{
	qsort(db, DB_SIZE, sizeof(struct student_t), cmpMarkDesc);
}

int cmpAlphabeticalAsc(const void *v1, const void *v2) /* Ascending */
{
	const struct student_t *p1 = (struct student_t *)v1;
	const struct student_t *p2 = (struct student_t *)v2;
	int r = strcmp(p1->name, p2->name);

	if (r < 0) {
		return -1;
	} else if (r > 0) {
		return +1;
	} else {
		return 0;
	}
}

void sortNameAlphabeticAsc(struct student_t db[DB_SIZE]) /* Ascending */
{
	qsort(db, DB_SIZE, sizeof(struct student_t), cmpAlphabeticalAsc);
}

/* ===================================80 chars=============================== */
/* EOF */
