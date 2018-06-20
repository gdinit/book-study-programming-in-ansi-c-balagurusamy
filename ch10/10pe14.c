/* 10pe14.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure called cricket that will describe the following
 * information:
 *
 * -player name
 * -team name
 * -batting average
 *
 * Using cricket, declare an array player with 50 elements and write a program
 * to read the information about all the 50 players and print a team-wise list
 * containing names of players with their batting average.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe14.c -o binary/10pe14
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */
#include <ctype.h> /* tolower() */


/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "PLAYER STRUCT"
#define CFGDEBUG 1
/**************************************/
#define LASTNAME_LENGTH 14 /* Longest surname = "inzamam-ul-haq" = 14 chars */
#define LASTNAME_LENGTH_PLUS_ONE 15
#define INITIALS_LENGTH 7
#define INITIALS_LENGTH_PLUS_ONE 8
#define DB_SIZE 50
#define PAGINATION 25
#define MENU_ENTRY_LOWEST 1
#define MENU_ENTRY_HIGHEST 4

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

struct player_t {
	char la[LASTNAME_LENGTH_PLUS_ONE]; /* lastname */
	char in[INITIALS_LENGTH_PLUS_ONE]; /* initials */
	float ba;			   /* batting average */
	enum CountryNames co;		   /* player's country */
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void printMainMenu(void);
void actionChoice(int choice, struct player_t db[DB_SIZE]);
int getChoice(void);
void zInitAllEntries(struct player_t db[DB_SIZE]);
void mainLoop(struct player_t db[DB_SIZE]);
void fillWithTestData(struct player_t db[DB_SIZE]);
void toUpperStr(char *p_str);
void toUpperFirstCharLowerRest(char *p_str);
void displayOneEntry(const struct player_t db[DB_SIZE], const int id);
/* void displayOneEntry(struct player_t db[DB_SIZE], int id); */
void displayAllEntries(struct player_t db[DB_SIZE]);
void displayOnlyNationN(struct player_t db[DB_SIZE], int cntry);
void displayMsgReqInputCountry(void);
void handleDisplayNationalTeam(struct player_t db[DB_SIZE]);
void displayMsgReqInputLastname(void);
void displayMsgReqInputInitials(void);
void displayMsgReqInputBatAvg(void);
void displayMsgReqInputChooseID(void);
void handleDataInputLastname(struct player_t db[DB_SIZE], int id);
void handleDataInputInitials(struct player_t db[DB_SIZE], int id);
void handleDataInputBatAvg(struct player_t db[DB_SIZE], int id);
void handleDataInputCountry(struct player_t db[DB_SIZE], int id);
int handleChooseEntryToEdit(void);
void handleDataEntry(struct player_t db[DB_SIZE]);
void enforceCapitalisationPolicy(struct player_t db[DB_SIZE]);
void enforceCapitalisationPolicy1(struct player_t db[DB_SIZE], int id);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct player_t db[DB_SIZE];

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
	       "\t1: DISPLAY All Players\n"
	       "\t2: DISPLAY Players of a Nation\n"
	       "\t3: ENTER/UPDATE Data for a Player\n"
	       "\t4: EXIT Program\n"
	       "Enter your choice: ",
	       title);
}

void actionChoice(int choice, struct player_t db[DB_SIZE])
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: DISPLAY All Players\n");
		displayAllEntries(db);
		break;
	case 2:
		printf("\nACTIONING: DISPLAY A National Team's Players\n");
		handleDisplayNationalTeam(db);
		break;
	case 3:
		printf("\nACTIONING: ENTER/UPDATE Data for a Player\n");
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

void zInitAllEntries(struct player_t db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		strcpy(db[n].la, "-");
		strcpy(db[n].in, "-");
		db[n].ba = 0.f;
		db[n].co = 0;
	}
}

void mainLoop(struct player_t db[DB_SIZE])
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

void fillWithTestData(struct player_t db[DB_SIZE])
{
	strcpy(db[0].la, "Bradman");
	strcpy(db[0].in, "D G");
	db[0].ba = 99.94f;
	db[0].co = 1;

	strcpy(db[1].la, "Voges");
	strcpy(db[1].in, "A C");
	db[1].ba = 61.88f;
	db[1].co = 1;

	strcpy(db[2].la, "Smith");
	strcpy(db[2].in, "S P D");
	db[2].ba = 61.38f;
	db[2].co = 1;

	strcpy(db[3].la, "Pollock");
	strcpy(db[3].in, "R G");
	db[3].ba = 60.97;
	db[3].co = 6;

	strcpy(db[4].la, "Headley");
	strcpy(db[4].in, "G A");
	db[4].ba = 60.83f;
	db[4].co = 8;

	strcpy(db[5].la, "Sutcliffe");
	strcpy(db[5].in, "H");
	db[5].ba = 60.73f;
	db[5].co = 2;

	strcpy(db[6].la, "Paynter");
	strcpy(db[6].in, "E");
	db[6].ba = 59.23f;
	db[6].co = 2;

	strcpy(db[7].la, "Barrington");
	strcpy(db[7].in, "K F");
	db[7].ba = 58.67f;
	db[7].co = 2;

	strcpy(db[8].la, "Weekes");
	strcpy(db[8].in, "E D C");
	db[8].ba = 58.62f;
	db[8].co = 8;

	strcpy(db[9].la, "Hammond");
	strcpy(db[9].in, "W R");
	db[9].ba = 58.46f;
	db[9].co = 2;

	strcpy(db[10].la, "Sobers");
	strcpy(db[10].in, "G S A");
	db[10].ba = 57.78f;
	db[10].co = 8;

	strcpy(db[11].la, "Sangakkara");
	strcpy(db[11].in, "K C");
	db[11].ba = 57.41f;
	db[11].co = 7;

	strcpy(db[12].la, "Hobbs");
	strcpy(db[12].in, "J B");
	db[12].ba = 56.95;
	db[12].co = 2;

	strcpy(db[13].la, "Walcott");
	strcpy(db[13].in, "C L");
	db[13].ba = 56.69f;
	db[13].co = 8;

	strcpy(db[14].la, "Hutton");
	strcpy(db[14].in, "L");
	db[14].ba = 56.67f;
	db[14].co = 2;

	strcpy(db[15].la, "Kallis");
	strcpy(db[15].in, "J H");
	db[15].ba = 55.37f;
	db[15].co = 6;

	strcpy(db[16].la, "Tyldesley");
	strcpy(db[16].in, "G E");
	db[16].ba = 55.00f;
	db[16].co = 2;

	strcpy(db[17].la, "Davis");
	strcpy(db[17].in, "C A");
	db[17].ba = 54.21f;
	db[17].co = 8;

	strcpy(db[18].la, "Kambli");
	strcpy(db[18].in, "V G");
	db[18].ba = 54.20f;
	db[18].co = 3;

	strcpy(db[19].la, "Chappell");
	strcpy(db[19].in, "G S");
	db[19].ba = 53.86f;
	db[19].co = 1;

	strcpy(db[20].la, "Nourse");
	strcpy(db[20].in, "A D");
	db[20].ba = 53.82f;
	db[20].co = 6;

	strcpy(db[21].la, "Tendulkar");
	strcpy(db[21].in, "S R");
	db[21].ba = 53.79;
	db[21].co = 3;

	strcpy(db[22].la, "Kohli");
	strcpy(db[22].in, "V");
	db[22].ba = 53.40f;
	db[22].co = 3;

	strcpy(db[23].la, "Lara");
	strcpy(db[23].in, "B C");
	db[23].ba = 52.89f;
	db[23].co = 8;

	strcpy(db[24].la, "Javed");
	strcpy(db[24].in, "M");
	db[24].ba = 52.57f;
	db[24].co = 5;

	strcpy(db[25].la, "Dravid");
	strcpy(db[25].in, "R");
	db[25].ba = 52.31f;
	db[25].co = 3;

	strcpy(db[26].la, "Mohammad");
	strcpy(db[26].in, "Y");
	db[26].ba = 52.29f;
	db[26].co = 5;

	strcpy(db[27].la, "Root");
	strcpy(db[27].in, "J E");
	db[27].ba = 52.28f;
	db[27].co = 2;

	strcpy(db[28].la, "Younis");
	strcpy(db[28].in, "K");
	db[28].ba = 52.06f;
	db[28].co = 5;

	strcpy(db[29].la, "Ponting");
	strcpy(db[29].in, "R T");
	db[29].ba = 51.85f;
	db[29].co = 1;

	strcpy(db[30].la, "Ryder");
	strcpy(db[30].in, "J");
	db[30].ba = 51.63f;
	db[30].co = 1;

	strcpy(db[31].la, "Flower");
	strcpy(db[31].in, "A");
	db[31].ba = 51.55f;
	db[31].co = 9;

	strcpy(db[32].la, "Hussey");
	strcpy(db[32].in, "M E K");
	db[32].ba = 51.53f;
	db[32].co = 1;

	strcpy(db[33].la, "Chanderpaul");
	strcpy(db[33].in, "S");
	db[33].ba = 51.37f;
	db[33].co = 8;

	strcpy(db[34].la, "Gavaskar");
	strcpy(db[34].in, "S M");
	db[34].ba = 51.12f;
	db[34].co = 3;

	strcpy(db[35].la, "Waugh");
	strcpy(db[35].in, "S R");
	db[35].ba = 51.06f;
	db[35].co = 1;

	strcpy(db[36].la, "Hayden");
	strcpy(db[36].in, "M L");
	db[36].ba = 50.74f;
	db[36].co = 1;

	strcpy(db[37].la, "de Villiers");
	strcpy(db[37].in, "A B");
	db[37].ba = 50.66f;
	db[37].co = 6;

	strcpy(db[38].la, "Border");
	strcpy(db[38].in, "A R");
	db[38].ba = 50.56f;
	db[38].co = 1;

	strcpy(db[39].la, "Williamson");
	strcpy(db[39].in, "K S");
	db[39].ba = 50.36f;
	db[39].co = 4;

	strcpy(db[40].la, "Pujara");
	strcpy(db[40].in, "C A");
	db[40].ba = 50.34f;
	db[40].co = 3;

	strcpy(db[41].la, "Richards");
	strcpy(db[41].in, "I V A");
	db[41].ba = 50.24f;
	db[41].co = 8;

	strcpy(db[42].la, "Compton");
	strcpy(db[42].in, "D C S");
	db[42].ba = 50.06f;
	db[42].co = 2;

	strcpy(db[43].la, "Jayawardene");
	strcpy(db[43].in, "D P M D");
	db[43].ba = 49.85f;
	db[43].co = 7;

	strcpy(db[44].la, "Inzamam-ul-Haq");
	strcpy(db[44].in, "-");
	db[44].ba = 49.61f;
	db[44].co = 5;

	strcpy(db[45].la, "Worrell");
	strcpy(db[45].in, "F M M");
	db[45].ba = 49.49f;
	db[45].co = 8;

	strcpy(db[46].la, "Mead");
	strcpy(db[46].in, "C P");
	db[46].ba = 49.38;
	db[46].co = 2;

	strcpy(db[47].la, "Sehwag");
	strcpy(db[47].in, "V");
	db[47].ba = 49.34f;
	db[47].co = 3;

	strcpy(db[48].la, "Clarke");
	strcpy(db[48].in, "M J");
	db[48].ba = 49.11f;
	db[48].co = 1;

	strcpy(db[49].la, "bland");
	strcpy(db[49].in, "k c");
	db[49].ba = 49.09f;
	db[49].co = 6;

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

/* TODO: CONST CORRECT THIS 
void displayOneEntry(const struct player_t db[DB_SIZE], const int id)
*/
void displayOneEntry(const struct player_t db[DB_SIZE], const int id)
/*void displayOneEntry(struct player_t db[DB_SIZE], int id)*/
{
	const static char idn[] = "ID";
	const static char las[] = "LASTNAME";
	const static char ini[] = "INITIALS";
	const static char bat[] = "BATTING AVERAGE";
	const static char cou[] = "COUNTRY";

	static char coun[] = "South Africa"; /* longest country */

	/* ------------------------------ */
	printf("-----------------------------------------------"
	       "-----------------------------------------\n");
	printf("DISPLAYING ONLY ENTRY ID %d\n\n", id + 1);
	/* id number is just a visual cue to assist user when
	 * entering data */
	printf("%-2s", idn);
	/* Longest surname in database is "inzamam-ul-haq"
	 * which is 14 chars to print */
	printf(" | %-14s", las);
	/* Actually only 5 chars needed to print longest initial
	 * however, 8 printable chars needed for 'initials' */
	printf(" | %-8s", ini);
	/* 'BATTING AVERAGE' = 15 chars to print*/
	printf(" | %15s", bat);
	/* Longest country 'South Africa' = 13 chars to print */
	printf(" | %-13s\n", cou);
	/* ------------------------------ */
	printf("%02d | ", id + 1);
	printf("%-14s | ", db[id].la);
	printf("%-8s | ", db[id].in);
	/* 15 chars for 'batting average' phrase + 2 decimals */
	printf("%15.2f | ", db[id].ba);
	/* prepare Country text */
	switch (db[id].co) {
	case 0:
		strcpy(coun, "Not in use");
		break;
	case 1:
		strcpy(coun, "Australia");
		break;
	case 2:
		strcpy(coun, "England");
		break;
	case 3:
		strcpy(coun, "India");
		break;
	case 4:
		strcpy(coun, "New Zealand");
		break;
	case 5:
		strcpy(coun, "Pakistan");
		break;
	case 6:
		strcpy(coun, "South Africa");
		break;
	case 7:
		strcpy(coun, "Sri Lanka");
		break;
	case 8:
		strcpy(coun, "West Indies");
		break;
	case 9:
		strcpy(coun, "Zimbabwe");
		break;
	default:
		strcpy(coun, "CountryError");
	}
	printf("%-13s\n", coun);
	printf("\nDISPLAYED ENTRY ID %d.\n"
	       "-----------------------------------------------"
	       "-----------------------------------------\n", id);
}

void displayAllEntries(struct player_t db[DB_SIZE])
{
	int n;
	static char idn[] = "ID";
	static char las[] = "LASTNAME";
	static char ini[] = "INITIALS";
	static char bat[] = "BATTING AVERAGE";
	static char cou[] = "COUNTRY";

	static char coun[] = "South Africa"; /* longest country */

	for (n = 0; n < DB_SIZE; n++) {
		if (n % PAGINATION == 0) {
			printf("-----------------------------------------------"
			       "-----------------------------------------\n");
			if (0 == n) {
				printf("LISTING ALL PLAYERS\n\n");
			}
			/* id number is just a visual cue to assist user when
			 * entering data */
			printf("%-2s", idn);
			/* Longest surname in database is "inzamam-ul-haq"
			 * which is 14 chars to print */
			printf(" | %-14s", las);
			/* Actually only 5 chars needed to print longest initial
			 * however, 8 printable chars needed for 'initials' */
			printf(" | %-8s", ini);
			/* 'BATTING AVERAGE' = 15 chars to print*/
			printf(" | %15s", bat);
			/* Longest country 'South Africa' = 13 chars to print */
			printf(" | %-13s\n", cou);
		}
		printf("%02d | ", n + 1);
		printf("%-14s | ", db[n].la);
		printf("%-8s | ", db[n].in);
		/* 15 chars for 'batting average' phrase + 2 decimals */
		printf("%15.2f | ", db[n].ba);
		/* prepare Country text */
		switch (db[n].co) {
		case 0:
			strcpy(coun, "Not in use");
			break;
		case 1:
			strcpy(coun, "Australia");
			break;
		case 2:
			strcpy(coun, "England");
			break;
		case 3:
			strcpy(coun, "India");
			break;
		case 4:
			strcpy(coun, "New Zealand");
			break;
		case 5:
			strcpy(coun, "Pakistan");
			break;
		case 6:
			strcpy(coun, "South Africa");
			break;
		case 7:
			strcpy(coun, "Sri Lanka");
			break;
		case 8:
			strcpy(coun, "West Indies");
			break;
		case 9:
			strcpy(coun, "Zimbabwe");
			break;
		default:
			strcpy(coun, "CountryError");
		}
		printf("%-13s\n", coun);
	}
	printf("\nDISPLAYED %d PLAYERS FROM ALL NATIONS.\n"
	       "-----------------------------------------------"
	       "-----------------------------------------\n", n);
}

void displayOnlyNationN(struct player_t db[DB_SIZE], int cntry)
{
	int n, hits = 0;
	static char idn[] = "ID";
	static char las[] = "LASTNAME";
	static char ini[] = "INITIALS";
	static char bat[] = "BATTING AVERAGE";
	static char cou[] = "COUNTRY";

	static char coun[] = "South Africa"; /* Country: longest one */
	static char adje[] = "South African"; /* Adjectival: longest one */

	/* pick country texts */
	/* TODO: put this in a function */
	/* TODO: use safer string copy (str5cpy) */
	switch (cntry) {
	case 0:
		strcpy(coun, "NotInUse");
		strcpy(coun, "NotInUse");
		break;
	case 1:
		strcpy(coun, "Australia");
		strcpy(adje, "Australian");
		break;
	case 2:
		strcpy(coun, "England");
		strcpy(adje, "England");
		break;
	case 3:
		strcpy(coun, "India");
		strcpy(adje, "India");
		break;
	case 4:
		strcpy(coun, "New Zealand");
		strcpy(adje, "New Zealand");
		break;
	case 5:
		strcpy(coun, "Pakistan");
		strcpy(adje, "Pakistan");
		break;
	case 6:
		strcpy(coun, "South Africa");
		strcpy(adje, "South Africa");
		break;
	case 7:
		strcpy(coun, "Sri Lanka");
		strcpy(adje, "Sri Lanka");
		break;
	case 8:
		strcpy(coun, "West Indies");
		strcpy(adje, "West Indies");
		break;
	case 9:
		strcpy(coun, "Zimbabwe");
		strcpy(adje, "Zimbabwe");
		break;
	default:
		strcpy(coun, "CountryError");
		strcpy(adje, "CountryError");
	}

	toUpperStr(coun);
	toUpperStr(adje);

	for (n = 0; n < DB_SIZE; n++) {
		if (db[n].co == cntry) {
			if (n % PAGINATION == 0) {
				printf("---------------------------------------"
				       "---------------------------------------"
				       "----------\n");
				if (0 == n) {
					printf("LISTING ONLY %s PLAYERS:\n\n",
					       adje);
				}
				/* id number is just a visual cue to assist user
				 * when entering data */
				printf("%-2s", idn);
				/* Longest surname in database is
				 * "inzamam-ul-haq" which is 14 chars to print*/
				printf(" | %-14s", las);
				/* Actually only 5 chars needed to print longest
				 * initial however, 8 printable chars needed for
				 * the word 'INITIALS' */
				printf(" | %-8s", ini);
				/* 'BATTING AVERAGE' = 15 chars to print */
				printf(" | %15s", bat);
				/* Longest country 'South Africa' = 13 chars to
				 * print */
				printf(" | %-13s\n", cou);
			}
			printf("%02d | ", n + 1);
			printf("%-14s | ", db[n].la);
			printf("%-8s | ", db[n].in);
			/* 15 chars for 'batting average' phrase + 2 decimals */
			printf("%15.2f | ", db[n].ba);
			printf("%-13s\n", coun);
			hits++; /* do this AFTER pagination above */
		}
	}
	if (0 == hits) {
		printf("SORRY! NO PLAYERS FROM %s!\n", coun);
	} else {
		printf("\nDISPLAYED %d PLAYERS FROM %s.\n"
		       "-----------------------------------------------"
		       "-----------------------------------------\n",
		       hits, coun);
	}
}

void displayMsgReqInputCountry(void)
{
	printf("NATIONS\n"
	       "1: Australia\n"
	       "2: England\n"
	       "3: India\n"
	       "4: New_Zealand\n"
	       "5: Pakistan\n"
	       "6: South_Africa\n"
	       "7: Sri_Lanka\n"
	       "8: West_Indies\n"
	       "9: Zimbabwe\n"
	       "Please choose a nation: ");

}

void handleDisplayNationalTeam(struct player_t db[DB_SIZE])
{
	int cntry;

	displayMsgReqInputCountry();
	FLUSH
	scanf("%d", &cntry); /* TODO convert to a loop & reject bad values */
	displayOnlyNationN(db, cntry);
}

void displayMsgReqInputLastname(void)
{
	printf("Enter player's lastname (" XSTR(LASTNAME_LENGTH) 
	       " chars max): ");
}

void displayMsgReqInputInitials(void)
{
	printf("Enter player's initials (" XSTR(INITIALS_LENGTH) 
	       " chars max): ");
}

void displayMsgReqInputBatAvg(void)
{
	printf("Enter player's batting average  (e.g.: 48.73): ");
}

void displayMsgReqInputChooseID(void)
{
	printf("Enter the record ID to modify (min: 1, max: " XSTR(DB_SIZE)
	       "): ");
}


/* Lastname should be first letter uppercase, rest lowercase e.g.: Johnson
 * Initials should be all uppercase e.g. A G D
 */
void enforceCapitalisationPolicy1(struct player_t db[DB_SIZE], int id)
{
	toUpperFirstCharLowerRest(db[id].la);
	toUpperStr(db[id].in);
}

/* Lastname should be first letter uppercase, rest lowercase e.g.: Johnson
 * Initials should be all uppercase e.g. A G D
 */
void enforceCapitalisationPolicy(struct player_t db[DB_SIZE])
{
	int n;

	for (n = 0; n < DB_SIZE; n++) {
		toUpperFirstCharLowerRest(db[n].la);
		toUpperStr(db[n].in);
	}
}

void handleDataInputLastname(struct player_t db[DB_SIZE], int id)
{
	char s[LASTNAME_LENGTH_PLUS_ONE];

	displayMsgReqInputLastname();
	FLUSH
	scanf("%" XSTR(LASTNAME_LENGTH) "[^\n]", s);
	toUpperFirstCharLowerRest(s);
	strcpy(db[id].la, s); /* TODO: use safer string copy (str5cpy) */
}

void handleDataInputInitials(struct player_t db[DB_SIZE], int id)
{
	char s[INITIALS_LENGTH_PLUS_ONE];

	displayMsgReqInputInitials();
	FLUSH
	scanf("%" XSTR(INITIALS_LENGTH) "[^\n]", s);
	toUpperStr(s);
	strcpy(db[id].in, s); /* TODO: use safer string copy (str5cpy) */
}

void handleDataInputBatAvg(struct player_t db[DB_SIZE], int id)
{
	float f = -1.f;

	do {
		displayMsgReqInputBatAvg();
		FLUSH
		scanf("%f", &f);
		if (f < 0) {
			printf("ERROR: BATTING AVERAGE CANNOT BE NEGATIVE! "
			       "PLEASE TRY AGAIN\n");
		}
	} while (f < 0);
	db[id].ba = f;
}

void handleDataInputCountry(struct player_t db[DB_SIZE], int id)
{
	int n;

	do {
		displayMsgReqInputCountry();
		FLUSH
		scanf("%d", &n);
		if (n < 0 || n >= COUNTRY_COUNT_PLUS_ONE) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 0 || n >= COUNTRY_COUNT_PLUS_ONE);
	db[id].co = n;
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

void handleDataEntry(struct player_t db[DB_SIZE])
{
	int id = -2;
	id = handleChooseEntryToEdit();
	id--; /* array starts with record id 0 */
	handleDataInputLastname(db, id);
	handleDataInputInitials(db, id);
	handleDataInputBatAvg(db, id);
	handleDataInputCountry(db, id);
	enforceCapitalisationPolicy1(db, id);
	printf("Updated record %d as follows:\n", id + 1);
	displayOneEntry(db, id);
}

/* ===================================80 chars=============================== */
/* EOF */
