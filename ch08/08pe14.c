/* 08pe14.c */
/* ===================================80 chars=============================== */

/*
Write a program to create a directory of students with roll numbers. The program
should display the roll number for a specified name and vice-versa.
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
	-Wparentheses -Wformat-zero-length 08pe14.c str5cpy.c -o binary/08pe14
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* str5cpy (safe copy) */
#include "str5.h"

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
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define STRMAXLEN 64
#define NAMEMAXLEN 31
#define CARDS 12
/* repeat table headers after every n entries */
#define HEADER_THRESHOLD 30
/* If a card is not in use, set it's ID to this magic value */
#define VACANT_ID 0000
/* During data entry, user can type in ABORT_CODE to abort program execution */
#define ABORT_CODE 999
#define CFGDEBUG 1

struct studentCard_t {
	unsigned long int rollNo;
	char name[NAMEMAXLEN + 1];
};
typedef struct studentCard_t studentCard;

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void toUpperStr(char *p_str);
void toLowerStr(char *p_str);
int getChoice(void);
void printMainMenu(void);
void mainLoop(studentCard *p_db);
void actionChoice(int choice, studentCard *p_db);
void sampleFillCards(studentCard *p_db);
void displayAllCards(studentCard *p_db);
void printHeader(void);
void zInit(studentCard *p_db);
void deleteEntry(studentCard *p_db, int id);
void processDelete(studentCard *p_db);
void orderByRollNoAsc(studentCard *p_db);
int cardCompareRollNoAsc(const void *v1, const void *v2);
void orderByNameAsc(studentCard *p_db);
int scCompareNameAsc(const void *v1, const void *v2);
void editEntry(studentCard *p_db);
void searchEntryRollNo(studentCard *p_db);
void searchEntryName(studentCard *p_db);

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
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 8

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

void printMainMenu(void)
{
	printf("\n*** MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: LOAD sample data\n"
	       "\t2: ENTER data / EDIT a card\n"
	       "\t3: DELETE an entry (based on rowID)\n"
	       "\t4: VIEW all entries sorted by ROLL NO (asc.)\n"
	       "\t5: VIEW all entries sorted by NAME (asc.)\n"
	       "\t6: SEARCH for an entry with ROLL NO\n"
	       "\t7: SEARCH for an entry with NAME\n"
	       "\t8: EXIT program\n"
	       "Enter your choice: ");
}

void actionChoice(int choice, studentCard *p_db)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: LOAD sample data\n");
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
		orderByRollNoAsc(p_db);
		displayAllCards(p_db);
		break;
	case 5:
		printf("\nACTIONING: VIEW all entries sorted by Name "
		       "asc.\n");
		orderByNameAsc(p_db);
		displayAllCards(p_db);
		break;
	case 6:
		printf("\nACTIONING: SEARCH for an entry with ROLL NO\n");
		searchEntryRollNo(p_db);
		break;
	case 7:
		printf("\nACTIONING: SEARCH for an entry with NAME\n");
		searchEntryName(p_db);
		break;
	case 8:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

/* Fill Student Cards Database:
 * -begin filling in the array from the very first array member
 * -name field: use Manhattan Project Scientists' names
 * -rollNo field: increment sequentially
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
#define SAMPLE_NAME_MAX 256
	int n;
	unsigned long int sampleNameCount = 0;

	/* last entry must be a single dot character */
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
				     "Emilio Secre",
				     "."};

	/* COUNT how many sample names we have */
	for (n = 0; n < SAMPLE_NAME_MAX && n < CARDS; n++) {
		if (sampleNames[n][0] == '.') {
			break;
		}
		sampleNameCount++;
	}
	if (CFGDEBUG) {
		printf("[DEBUG] sampleNameCount detected as: %lu\n",
		       (unsigned long int)sampleNameCount);
	}

	/* ENTER TEST DATA into all Student Cards */
	{
		int nextID = 0;
		int *p_nextID = &nextID;

		for (n = 0; n < (int)sampleNameCount; n++) {
			int r;

			/* point to the next card */
			studentCard *p_card = &p_db[n];

			++*p_nextID;

			/* enter ID NUMBER:	enter the next available no,
						into current card */
			p_card->rollNo = *p_nextID;

			/* enter NAME:	copy the next name from sampleNames
			   array, into the card */
			if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1,
					 sampleNames[n])) < 0) {
				/* error */
				printf("strtcpy error: %d", r);
				exit(EXIT_FAILURE);
			}
		}
	}
	printf("Demo Data has been successfully loaded.\n\n");
}

void printHeader(void) { printf("\nROWID\tROLLNO\tNAME\n"); }

/* Display All Student Cards from the database */
void displayAllCards(studentCard *p_db)
{
	int n;

	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		studentCard *p_card = &p_db[n];
		/* print HEADER upon entry & whenever we need to */
		if (n % HEADER_THRESHOLD == 0) {
			printHeader();
		}
		/* PRINT DATA from CURRENT RECORD */
		printf("%02d\t", n + 1);
		printf("%04lu\t", p_card->rollNo);
		printf("%-24s\n", p_card->name);
	}
}

/* reset fields, in every struct in the array */
void zInit(studentCard *p_db)
{
	int n, r;
	studentCard *p_card;
	/* TODO change this charr arr to const char arr */
	char arr[] = "<slot not in use>";

	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		p_card = &p_db[n];
		p_card->rollNo = VACANT_ID;
		if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, arr)) < 0) {
			/* error */
			printf("strtcpy error: %d", r);
			exit(EXIT_FAILURE);
		}
	}
}

void processDelete(studentCard *p_db)
{
#define ROW_ID_LOWEST 1

	int num;

	do {
		/* ask user which entry to delete */
		printf("TO DELETE an entry enter the ROWID or " XSTR(
		    ABORT_CODE) " to cancel: ");
		FLUSH
		scanf("%d", &num);
		if (num == ABORT_CODE) {
			printf("CANCELLED delete operation\n");
			break;
		} else if (num > 0 && num <= CARDS) {
			printf("DELETING entry %d\n", num);
			deleteEntry(p_db, num - 1);
			break;
		}
	} while (num < ROW_ID_LOWEST || (num > CARDS && num != ABORT_CODE));
}

/* zero fill an entry in the array */
void deleteEntry(studentCard *p_db, int id)
{
	char arr[] = "<slot not in use>";
	int r;
	studentCard *p_card = &p_db[id];

	p_card->rollNo = VACANT_ID;
	if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, arr)) < 0) {
		/* error */
		printf("strtcpy error: %d", r);
		exit(EXIT_FAILURE);
	}
}

void orderByRollNoAsc(studentCard *p_db)
{
	qsort(p_db, CARDS, sizeof(studentCard), cardCompareRollNoAsc);
}

int cardCompareRollNoAsc(const void *v1, const void *v2)
{
	const studentCard *p1 = (studentCard *)v1;
	const studentCard *p2 = (studentCard *)v2;
	if (p1->rollNo < p2->rollNo) {
		return -1;
	} else if (p1->rollNo > p2->rollNo) {
		return +1;
	} else {
		return 0;
	}
}

void orderByNameAsc(studentCard *p_db)
{
	qsort(p_db, CARDS, sizeof(studentCard), scCompareNameAsc);
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

/* ***************************************************************** */
/* TODO add a Y/N button to give the user to review & decide */
/* TODO add input validation */
void editEntry(studentCard *p_db)
{
	unsigned long int id;
	char name[NAMEMAXLEN + 1] = "";
	char *p_name = name;
	unsigned long int rollNo = 0;
	unsigned long int *p_rollNo = &rollNo;
	int r;
	studentCard *p_card;

	printf("Please enter which entry to overwrite (between 1 - " XSTR(
	    CARDS) "): ");
	FLUSH;
	scanf("%lu", &id);
	if (CFGDEBUG) {
		printf("[DEBUG] ID is set to: %lu\n", id);
	}

	/* point to the requested card */
	p_card = &p_db[id - 1];

	printf("Current ROLL NO is: %lu\n", p_card->rollNo);
	printf("Please enter the new ROLL NO or 0 for NO CHANGE: ");
	FLUSH;
	scanf("%lu", p_rollNo);
	if (*p_rollNo == 0) {
		printf("NO CHANGE chosen\n");
	} else {
		printf("ROLL NO is set to: %lu\n", *p_rollNo);
		p_card->rollNo = *p_rollNo;
	}

	printf("Current name is: %s\n", p_card->name);
	printf("Please enter the new name (" XSTR(
	    NAMEMAXLEN) ") chars max) or "
			"a single DOT for NO CHANGE: ");
	FLUSH;
	scanf("%" XSTR(NAMEMAXLEN) "[^\n]", p_name);
	if (*p_name == '.') {
		printf("NO CHANGE chosen\n");
	} else {
		printf("Name is set to: %s\n", p_name);
		if ((r = strtcpy(p_card->name, NAMEMAXLEN + 1, p_name)) < 0) {
			/* error */
			printf("strtcpy error: %d", r);
			exit(EXIT_FAILURE);
		}
	}
}

/* SEARCH for an entry with ROLL NO */
void searchEntryRollNo(studentCard *p_db)
{
	int found = 0;
	int n;
	unsigned long int rollNo;
	studentCard *p_card;

	printf("Please enter ROLL NO to search for or 0 to CANCEL: ");
	FLUSH;
	scanf("%lu", &rollNo);

	if (rollNo == 0) {
		printf("CANCEL requested.");
		return;
	}

	if (CFGDEBUG) {
		printf("[DEBUG] ROLL NO is set to: %lu. Proceeding with the "
		       "search...\n",
		       rollNo);
	}
	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		p_card = &p_db[n];
		if (p_card->rollNo == rollNo) {
			printf("An entry matching the search terms (ROLLNO = "
			       "%lu) has been FOUND! ",
			       rollNo);
			printf("Here is the entry:");
			printHeader();
			/* PRINT DATA from CURRENT RECORD */
			printf("%02d\t", n + 1);
			printf("%04lu\t", p_card->rollNo);
			printf("%-24s\n", p_card->name);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("An entry matching the search terms (ROLLNO = %lu) "
		       "DOESN'T EXIST.",
		       rollNo);
	}
}

/* SEARCH for an entry with NAME */
void searchEntryName(studentCard *p_db)
{
	int found = 0;
	int n;
	char name[NAMEMAXLEN + 1] = "";
	char *p_name = name;
	studentCard *p_card;

	printf("Please enter the name to search for or . to CANCEL (" XSTR(
	    NAMEMAXLEN) ") chars max: ");
	FLUSH;
	scanf("%" XSTR(NAMEMAXLEN) "[^\n]", p_name);

	if (*&p_name[0] == '.') {
		printf("CANCELLING (DOT detected).\n");
		return;
	}

	if (CFGDEBUG) {
		printf("[DEBUG] NAME is set to: %s. Proceeding with the "
		       "search...\n",
		       p_name);
	}
	for (n = 0; n < CARDS; n++) {
		/* point to the next card */
		p_card = &p_db[n];
		if (strcmp(p_name, p_card->name) == 0) {
			printf("An entry matching the search terms (NAME = "
			       "%s) has been FOUND! ",
			       p_name);
			printf("Here is the entry:");
			printHeader();
			/* PRINT DATA from CURRENT RECORD */
			printf("%02d\t", n + 1);
			printf("%04lu\t", p_card->rollNo);
			printf("%-24s\n", p_card->name);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("An entry matching the search terms (NAME = %s) "
		       "DOESN'T EXIST.",
		       p_name);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
