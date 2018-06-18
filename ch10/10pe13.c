/* 10pe13.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure that can describe a hotel. It should have members that
 * include the name, address, grade, average room charge, and number of rooms.
 *
 * Write functions to perform the following operations:
 * -To print out hotels of a given grade in order of charges
 * -To print out hotels with room charges less than a given value
 */

/*
 * KNOWN ISSUES
 * -pound (GBP) sign does not appear correctly in Dosbox->Borland C++ 3
 *
 * IMPROVEMENT IDEAS
 * -get rid of unsafe strcpy()
 * -use only single DB_SIZE macro in int(), for the rest, use counting
 */ 

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe13.c -o binary/10pe13
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
#define TITLE "HOTEL STRUCT"
#define CFGDEBUG 1
#define NAME_LENGTH 20
#define NAME_LENGTH_PLUS_ONE 21
#define ADDRESS_LENGTH 32
#define ADDRESS_LENGTH_PLUS_ONE 33
#define DB_SIZE 5
#define PAGINATION 10
#define MENU_ENTRY_LOWEST 0
#define MENU_ENTRY_HIGHEST 8

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

struct hotel_t {
	char name[NAME_LENGTH_PLUS_ONE];
	char address[ADDRESS_LENGTH_PLUS_ONE];
	int grade;
	int price; /* average */
	int rooms;
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void fillWithTestData(struct hotel_t db[DB_SIZE]);
void zInitAllEntries(struct hotel_t db[DB_SIZE]);
void displayAllHotels(struct hotel_t db[DB_SIZE]);
void displayMsgReqInputName(void);
void displayMsgReqInputAddress(void);
void displayMsgReqInputGrade(void);
void displayMsgReqInputPrice(void);
void displayMsgReqInputRooms(void);
void handleDataInputName(struct hotel_t db[DB_SIZE], int id);
void handleDataInputAddress(struct hotel_t db[DB_SIZE], int id);
void handleDataInputGrade(struct hotel_t db[DB_SIZE], int id);
void handleDataInputPrice(struct hotel_t db[DB_SIZE], int id);
void handleDataInputRooms(struct hotel_t db[DB_SIZE], int id);
void handleDataEntry(struct hotel_t db[DB_SIZE], int id);
void listOnlyGradeX(struct hotel_t db[DB_SIZE], int grade);
void listOnlyPriceN(struct hotel_t db[DB_SIZE], int limit);
void displayMsgReqInputFilterGrade(void);
void displayMsgReqInputFilterPrice(void);
void handleListOnlyGradeX(struct hotel_t db[DB_SIZE]);
void handleListOnlyPriceLessN(struct hotel_t db[DB_SIZE]);
void actionChoice(int choice, struct hotel_t db[DB_SIZE]);
void printMainMenu(void);
int getChoice(void);
void mainLoop(struct hotel_t db[DB_SIZE]);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct hotel_t db[DB_SIZE];

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
void fillWithTestData(struct hotel_t db[DB_SIZE])
{
	strcpy(db[0].name, "Holiday Inn Finchley");
	strcpy(db[0].address, "17 Pelican Road London FN4 3GA");
	db[0].grade = 4;
	db[0].price = 95;
	db[0].rooms = 102;

	strcpy(db[1].name, "Morning Star");
	strcpy(db[1].address, "7 Beleuve Road London W1C XK1");
	db[1].grade = 2;
	db[1].price = 55;
	db[1].rooms = 28;

	strcpy(db[2].name, "Marriott Hampstead");
	strcpy(db[2].address, "1 Heath London HE7 0CJ");
	db[2].grade = 5;
	db[2].price = 165;
	db[2].rooms = 136;

	strcpy(db[3].name, "Big Ed's B&B");
	strcpy(db[3].address, "38 Food Street London CA8 3FD");
	db[3].grade = 3;
	db[3].price = 85;
	db[3].rooms = 48;

	strcpy(db[4].name, "Four Seasons");
	strcpy(db[4].address, "1128 Clapham Road London CL1 JN8");
	db[4].grade = 4;
	db[4].price = 110;
	db[4].rooms = 168;
}

void zInitAllEntries(struct hotel_t db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		strcpy(db[n].name, "not-in-use");
		strcpy(db[n].address, "not-in-use");
		db[n].grade = 0;
		db[n].price = 0;
		db[n].rooms = 0;
	}
}

void displayAllHotels(struct hotel_t db[DB_SIZE])
{
	int n;
	static char nam[] = "NAME";
	static char adr[] = "ADDRESS";
	static char gra[] = "GRADE";
	static char pri[] = "PRICE";
	static char roo[] = "ROOMS";
	for (n = 0; n < DB_SIZE; n++) {
		if (n % PAGINATION == 0) {
			printf("-----------------------------------------------"
			       "-----------------------------------------\n");
			printf("%-21s", nam);
			printf(" | %-32s", adr);
			printf(" | %6s", gra);
			printf(" | %6s (£)", pri);
			printf(" | %6s\n", roo);
		}
		printf("%-21s | ", db[n].name);
		printf("%-32s | ", db[n].address);
		printf("%6d | ", db[n].grade);
		printf("%10.2f | ", (float)db[n].price);
		printf("%6d\n", db[n].rooms);
	}
}

void displayMsgReqInputName(void)
{
	printf("Enter hotel name (" XSTR(NAME_LENGTH) " chars max): ");
}

void displayMsgReqInputAddress(void)
{
	printf("Enter hotel address (" XSTR(ADDRESS_LENGTH) " chars max): ");
}

void displayMsgReqInputGrade(void)
{
	printf("Enter hotel's star grade  (min: 1, max: 5): ");
}

void displayMsgReqInputPrice(void)
{
	printf("Enter nightly average rate in GBP (do not enter pence. eg.: "
	       "120): £");
}

void displayMsgReqInputRooms(void)
{
	printf("Enter total number of hotel rooms: ");
}

void handleDataInputName(struct hotel_t db[DB_SIZE], int id)
{
	char s[NAME_LENGTH_PLUS_ONE];

	displayMsgReqInputName();
	FLUSH
	scanf("%" XSTR(NAME_LENGTH) "[^\n]", s);
	strcpy(db[id].name, s); /* TODO switch to secure string copy here */
}

void handleDataInputAddress(struct hotel_t db[DB_SIZE], int id)
{
	char s[ADDRESS_LENGTH_PLUS_ONE];

	displayMsgReqInputAddress();
	FLUSH
	scanf("%" XSTR(ADDRESS_LENGTH) "[^\n]", s);
	strcpy(db[id].address, s); /* TODO switch to secure string copy here */
}

void handleDataInputGrade(struct hotel_t db[DB_SIZE], int id)
{
	int n;

	displayMsgReqInputGrade();
	scanf("%d", &n); /* TODO convert this to a loop reject all but 1..5 */
	db[id].grade = n;
}

void handleDataInputPrice(struct hotel_t db[DB_SIZE], int id)
{
	int n;

	displayMsgReqInputPrice();
	scanf("%d", &n);
	db[id].price = n;
}

void handleDataInputRooms(struct hotel_t db[DB_SIZE], int id)
{
	int n;

	displayMsgReqInputRooms();
	scanf("%d", &n);
	db[id].rooms = n;
}

void handleDataEntry(struct hotel_t db[DB_SIZE], int id)
{
	handleDataInputName(db, id);
	handleDataInputAddress(db, id);
	handleDataInputGrade(db, id);
	handleDataInputPrice(db, id);
	handleDataInputRooms(db, id);
}

void listOnlyGradeX(struct hotel_t db[DB_SIZE], int grade)
{
	int n, hits = 0;
	static char nam[] = "NAME";
	static char adr[] = "ADDRESS";
	static char gra[] = "GRADE";
	static char pri[] = "PRICE";
	static char roo[] = "ROOMS";

	printf("SEARCHING FOR %d STAR HOTELS...\n", grade);
	for (n = 0; n < DB_SIZE; n++) {
		if (db[n].grade == grade) {
			/* TODO move this to: displaySingleHotel(db, n, hit);*/
			if (hits % PAGINATION == 0) {
				printf("---------------------------------------"
				       "---------------------------------------"
				       "----------\n");
				printf("%-21s", nam);
				printf(" | %-32s", adr);
				printf(" | %6s", gra);
				printf(" | %6s (£)", pri);
				printf(" | %6s\n", roo);
			}
			printf("%-21s | ", db[n].name);
			printf("%-32s | ", db[n].address);
			printf("%6d | ", db[n].grade);
			printf("%10.2f | ", (float)db[n].price);
			printf("%6d\n", db[n].rooms);
			hits++; /* do this AFTER pagination above */
		}
	}
	if (0 == hits) {
		printf("SORRY! NO HOTELS MATCH SEARCH CRITERIA: GRADE = %d!\n",
		       grade);
	}
}

void listOnlyPriceN(struct hotel_t db[DB_SIZE], int limit)
{
	int n, hits = 0;
	static char nam[] = "NAME";
	static char adr[] = "ADDRESS";
	static char gra[] = "GRADE";
	static char pri[] = "PRICE";
	static char roo[] = "ROOMS";

	printf("SEARCHING FOR HOTELS THAT COST LESS THAN £%4.2f...\n",
	       (float)limit);
	for (n = 0; n < DB_SIZE; n++) {
		if (db[n].price < limit) {
			/* TODO move this to: displaySingleHotel(db, n, hit);*/
			if (hits % PAGINATION == 0) {
				printf("---------------------------------------"
				       "---------------------------------------"
				       "----------\n");
				printf("%-21s", nam);
				printf(" | %-32s", adr);
				printf(" | %6s", gra);
				printf(" | %6s (£)", pri);
				printf(" | %6s\n", roo);
			}
			printf("%-21s | ", db[n].name);
			printf("%-32s | ", db[n].address);
			printf("%6d | ", db[n].grade);
			printf("%10.2f | ", (float)db[n].price);
			printf("%6d\n", db[n].rooms);
			hits++; /* do this AFTER pagination above */
		}
	}
	if (0 == hits) {
		printf("SORRY! NO HOTELS MATCH SEARCH CRITERIA: PRICE LESS THAN"
		       " £%4.2f!\n",
		       (float)limit);
	}
}

void displayMsgReqInputFilterGrade(void)
{
	printf("Enter star grade to list (min: 1, max: 5): ");
}

void displayMsgReqInputFilterPrice(void)
{
	printf("Enter max price to list (in GBP, without pence e.g. \"80\"): ");
}

void handleListOnlyGradeX(struct hotel_t db[DB_SIZE])
{
	int n;

	displayMsgReqInputFilterGrade();
	FLUSH
	scanf("%d", &n); /* TODO convert this to a loop reject all but 1..5 */
	listOnlyGradeX(db, n);
}

void handleListOnlyPriceLessN(struct hotel_t db[DB_SIZE])
{
	int n;

	displayMsgReqInputFilterPrice();
	FLUSH
	scanf("%d", &n); /* TODO convert this to a loop reject insane values  */
	listOnlyPriceN(db, n);
}

void actionChoice(int choice, struct hotel_t db[DB_SIZE])
{
	switch (choice) {
	case 0:
		printf("\nACTIONING: DISPLAY all hotels\n");
		displayAllHotels(db);
		break;
	case 1:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #1\n");
		handleDataEntry(db, 0);
		break;
	case 2:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #2\n");
		handleDataEntry(db, 1);
		break;
	case 3:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #3\n");
		handleDataEntry(db, 2);
		break;
	case 4:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #4\n");
		handleDataEntry(db, 3);
		break;
	case 5:
		printf("\nACTIONING: ENTER/UPDATE data for city slot #5\n");
		handleDataEntry(db, 4);
		break;
	case 6:
		printf("\nACTIONING: LIST only Grade X Hotels\n");
		handleListOnlyGradeX(db);
		break;
	case 7:
		printf("\nACTIONING: LIST only Hotels that cost less than N\n");
		handleListOnlyPriceLessN(db);
		break;
	case 8:
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
	       "\t0: DISPLAY All Hotels\n"
	       "\t1: ENTER/UPDATE data for city slot #1\n"
	       "\t2: ENTER/UPDATE data for city slot #2\n"
	       "\t3: ENTER/UPDATE data for city slot #3\n"
	       "\t4: ENTER/UPDATE data for city slot #4\n"
	       "\t5: ENTER/UPDATE data for city slot #5\n"
	       "\t6: LIST only Grade X Hotels\n"
	       "\t7: LIST only Hotels that cost less than N\n"
	       "\t8: EXIT program\n"
	       "Enter your choice: ",
	       title);
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

void mainLoop(struct hotel_t db[DB_SIZE])
{
	int firstRun = 1;
	int choice;

	while (1) {
		if (firstRun) {
			choice = 0; /* show all hotels on initial run */
		} else {
			choice = getChoice();
		}
		actionChoice(choice, db);
		if (firstRun) {
			firstRun = 0;
		}
	}
}

/* ===================================80 chars=============================== */
/* EOF */
