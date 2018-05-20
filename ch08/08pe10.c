/* 08pe10.c */
/* ===================================80 chars=============================== */

/*
Develop a program that will read and store the details of a list of students in
the format:

	Roll No.		Name		Marks obtained
	...			...		...
	...			...		...
	...			...		...
and produce the following output list:
(a) Alphabetical list of names, roll numbers and marks obtained.
(b) List sorted on roll numbers.
(c) List sorted on marks (rank-wise list).
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
	-Wparentheses -Wformat-zero-length 08pe10.c str5cpy.c -o binary/08pe10
*/

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>
/* str5cpy (safe copy) */
#include "str5.h"

/*
Required to prevent -> "scanf: floating point formats not linked" in Borland 3
*/
/*
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern		_floatconvert;
#pragma extref _floatconvert
#endif
*/

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

/* CONFIGURATION */
#define TITLE "STUDENT DATABASE"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 64
#define NAMEMAXLEN 24
#define CARDS 12
/* repeat table headers after every n entries */
#define HEADER_THRESHOLD 30
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 1

struct studentCard_t {
	unsigned long int id;
	char name[NAMEMAXLEN];
	unsigned short int mark;
};
typedef struct studentCard_t studentCard;

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void toUpperStr(char *p_str);
void toLowerStr(char *p_str);
void sampleFillCards(studentCard *p_db);
void displayAllCards(studentCard *p_db);
void printHeader(void);
int scCompareIdAsc(const void *v1, const void *v2);
void orderByIdAsc(studentCard *p_db);
int scCompareMark(const void *v1, const void *v2);
void orderByMarkDesc(studentCard *p_db);
int scCompareNameAsc(const void *v1, const void *v2);
void orderByNameAsc(studentCard *p_db);
int getChoice(void);
void printMainMenu(void);
void mainLoop(studentCard *p_db);
void actionChoice(int choice, studentCard *p_db);
void zInit(studentCard *p_db);
void processDelete(studentCard *p_db);
void deleteEntry(studentCard *p_db, int id);
unsigned long int findNextID(studentCard *p_db);
void editEntry(studentCard *p_db);

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	studentCard db[CARDS];
	studentCard *p_db = &db[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	zInit(p_db);

	mainLoop(p_db);

	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	/* TODO space works in DOS but is not cross platform. fix or remove */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* FUNCTIONS */
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n%s\n\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n");
}

void toUpperStr(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);

	for (n = 0; n < len; n++) {
		p_str[n] = toupper(p_str[n]);
	}
}

void toLowerStr(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);

	for (n = 0; n < len; n++) {
		p_str[n] = tolower(p_str[n]);
	}
}

/* Fill Student Cards Database:
 * -begin filling in the array from the very first entry in array
 * -for names, use Manhattan Project Scientists' names
 * -far exam marks, generate random marks
 *
 * First 6 names are taken from:
 * https://graduate.norwich.edu/resource-mmh/articles-mmh/who-were-the-
 * manhattan-project-scientists/
 *
 * Remaining names are taken from a declassified U.S. Government Document
 * available at:
 * https://archive.org/details/1944_2dec_manhattan_project_scientists
 * Document ref no:  S/NDF/T193
 * Issued: [redacted] 21/5/1952
 * Original date: 1944-12-02
 **/
void sampleFillCards(studentCard *p_db)
{
	int n;
	int nextID = 0;
	int *p_nextID = &nextID;
	const char *sampleNames[] = {"J. Robert Oppenheimer",
				     "Leo Szilard",
				     "Hans Bethe",
				     "Ernest O. Lawrence",
				     "Klaus Fuchs",
				     "Glenn Seaborg",
				     "Nicls Dohr",
				     "Enrico Fermi",
				     "John Newman",
				     "Bruno Russi",
				     "George Kistiakowski",
				     "Emilio Secre"};

	/* ENTER TEST DATA into all Student Cards */
	for (n = 0; n < CARDS; n++) {
		int r;
		/* point to the next card */
		studentCard *p_card = &p_db[n];

		++*p_nextID;

		/* enter ID NUMBER:	enter the next available no,
					into current card */
		p_card->id = *p_nextID;

		/* enter NAME:	copy the next name from sampleNames array,
				into the card */
		if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1,
				 sampleNames[n])) < 0) {
			/* error */
			printf("strtcpy error: %d", r);
			exit(EXIT_FAILURE);
		}

		/* enter MARK: generate & fill in a random exam score,
		 * based on ASCII code of student name's first letter.
		 **/
		p_card->mark = p_card->name[0];
	}
	printf("Demo Data has been successfully loaded.\n\n");
}

void printHeader(void) { printf("\nNO\tNAME\t\t\t\tMARK\n"); }

/* Display All Student Cards from the database */
void displayAllCards(studentCard *p_db)
{
	int n;

	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		studentCard *card = &p_db[n];
		/* print HEADER upon entry & whenever we need to */
		if (n % HEADER_THRESHOLD == 0) {
			printHeader();
		}
		/* PRINT DATA from CURRENT RECORD */
		printf("%03lu\t", card->id);
		printf("%-24s\t", card->name);
		printf("%03d\n", card->mark);
	}
}

int scCompareIdAsc(const void *v1, const void *v2)
{
	const studentCard *p1 = (studentCard *)v1;
	const studentCard *p2 = (studentCard *)v2;
	if (p1->id < p2->id) {
		return -1;
	} else if (p1->id > p2->id) {
		return +1;
	} else {
		return 0;
	}
}

void orderByIdAsc(studentCard *p_db)
{
	qsort(p_db, CARDS, sizeof(studentCard), scCompareIdAsc);
}

int scCompareMarkDesc(const void *v1, const void *v2)
{
	const studentCard *p1 = (studentCard *)v1;
	const studentCard *p2 = (studentCard *)v2;
	if (p1->mark < p2->mark) {
		return +1;
	} else if (p1->mark > p2->mark) {
		return -1;
	} else {
		return 0;
	}
}

void orderByMarkDesc(studentCard *p_db)
{
	qsort(p_db, CARDS, sizeof(studentCard), scCompareMarkDesc);
}

int scCompareNameAsc(const void *v1, const void *v2)
{
	const studentCard *p1 = (studentCard *)v1;
	const studentCard *p2 = (studentCard *)v2;
	int r;

	r = strcmp(p1->name, p2->name);

	if (r < 0) {
		return -1;
	} else if (r > 0) {
		return +1;
	} else {
		return 0;
	}
}

void orderByNameAsc(studentCard *p_db)
{
	qsort(p_db, CARDS, sizeof(studentCard), scCompareNameAsc);
}

void mainLoop(studentCard *p_db)
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, p_db);
	}
}

int getChoice(void)
{
	int num;
	do {
		printMainMenu();
		FLUSH
		scanf("%d", &num);
		if (num < 1 || num > 7) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < 1 || num > 7);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void printMainMenu(void)
{
	printf("\n*** MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: LOAD sample data\n"
	       "\t2: ENTER data manually\n"
	       "\t3: DELETE an entry (based on ID)\n"
	       "\t4: VIEW all entries sorted by ID (asc.)\n"
	       "\t5: VIEW all entries sorted by Name (asc.)\n"
	       "\t6: VIEW all entries sorted by Mark (desc.)\n"
	       "\t7: EXIT program\n"
	       "Enter your choice: ");
}

void actionChoice(int choice, studentCard *p_db)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: LOAD sample data\n");
		/* ENTER DATA: fill database with demo data */
		sampleFillCards(p_db);
		break;
	case 2:
		printf("\nACTIONING: ENTER data manually\n");
		printf("\nPlease note that this only can be used to "
		       "overwrite an existing entry.\n");
		editEntry(p_db);
		break;
	case 3:
		printf("\nACTIONING: DELETE an entry (based on ID)\n");
		processDelete(p_db);
		break;
	case 4:
		printf("\nACTIONING: VIEW all entries sorted by ID asc."
		       "\n");
		orderByIdAsc(p_db);
		displayAllCards(p_db);
		break;
	case 5:
		printf("\nACTIONING: VIEW all entries sorted by Name "
		       "asc.\n");
		orderByNameAsc(p_db);
		displayAllCards(p_db);
		break;
	case 6:
		printf("\nACTIONING: VIEW all entries sorted by Mark "
		       "asc.\n");
		orderByMarkDesc(p_db);
		displayAllCards(p_db);
		break;
	case 7:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

/* reset fields, in every struct, in an array */
void zInit(studentCard *p_db)
{
	int n;
	studentCard *p_card;

	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		p_card = &p_db[n];

		/* set everything to zero */
		p_card->id = 999;
		{
			int r;
			char arr[] = "<slot not in use>";
			if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, arr)) <
			    0) {
				/* error */
				printf("strtcpy error: %d", r);
				exit(EXIT_FAILURE);
			}
		}
		p_card->mark = 0;
	}
}

void processDelete(studentCard *p_db)
{
	int num;

	do {
		/* ask user which entry to delete */
		printf("TO DELETE an entry enter the entry NO or 999 to "
		       "cancel: ");
		FLUSH
		scanf("%d", &num);
		if (num == 999) {
			printf("CANCELLED delete operation\n");
			break;
		} else if (num > 0 && num <= CARDS) {
			printf("DELETING entry %d\n", num);
			/* need to sort by ID in Ascending order
			 * so that entry 7 is indeed 7th */
			orderByIdAsc(p_db);
			deleteEntry(p_db, num - 1);
			break;
		}
	} while (num < 1 || (num < CARDS || num != 999));
}

/* zero fill an entry in the array */
void deleteEntry(studentCard *p_db, int id)
{
	studentCard *p_card = &p_db[id];

	/* reset all fields zero */
	p_card->id = 999;
	{
		int r;
		char arr[] = "<slot not in use>";
		if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, arr)) < 0) {
			/* error */
			printf("strtcpy error: %d", r);
			exit(EXIT_FAILURE);
		}
	}
	p_card->mark = 0;
}

/* func to identify what ID should be given to the next new studentCard entry */
unsigned long int findNextID(studentCard *p_db)
{
	int it;
	unsigned long int nextID = 0;
	studentCard *p_card;

	for (it = 0; it < CARDS; it++) {
		/* point to the next card */
		p_card = &p_db[it];
		if (p_card->id > nextID && p_card->id != 999) {
			nextID = p_card->id;
		}
	}
	++nextID;

	return nextID;
}

void editEntry(studentCard *p_db)
{
	unsigned long int id;
	char name[NAMEMAXLEN + 1] = "";
	char *p_name = name;
	int mark;
	int r;
	studentCard *p_card;

	printf("Please enter which entry to overwrite (between 1 - " XSTR(
	    CARDS) "): ");
	FLUSH;
	scanf("%lu", &id);
	printf("ID is set to: %lu\n", id);

	printf("Please enter the new name (" XSTR(NAMEMAXLEN) ") chars max): ");
	FLUSH;
	scanf("%" XSTR(NAMEMAXLEN) "[^\n]", p_name);
	printf("Name is set to: %s\n", p_name);

	printf("Please enter the mark (between 0-100): ");
	FLUSH;
	scanf("%d", &mark);
	printf("Mark is set to: %d\n", mark);

	/* ***************************************************************** */
	/* TODO add a Y/N button to give the user to review & decide */
	/* point to the chosen slot */

	/* TODO add input validation */
	p_card = &p_db[id - 1];

	if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, p_name)) < 0) {
		/* error */
		printf("strtcpy error: %d", r);
		exit(EXIT_FAILURE);
	}

	p_card->mark = mark;
}

/* ===================================80 chars=============================== */
/* EOF */
