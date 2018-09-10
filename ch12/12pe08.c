/* 12pe08.c */
/* ===================================80 chars=============================== */

/*
 * Write a program to create a sequential file that could store details about
 * five products. Details include product code, cost and number of items
 * available and are provided through keyboard.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe08.c -o binary/12pe08
 */

/**
 * KNOWN ISSUES
 * -valgrind reports memory leaks in renumber_entries() (see improvement ideas)
 *	"definitely lost: 4,256 bytes in 9 blocks"
 *  	"ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)""
 *
 * TODO list
 * -add "enter 0 as price to go back"
 *
 * IMPROVEMENT IDEAS
 * -remove all dynamic memory usage
 * -Ask for each commit:	'Y' to commit 'N' (or ENTER) to cancel
 * -Combine 2 functions into one (which record do you wish to 'edit'/'delete'?)
 * -All "TODO"s documented in this file
 **/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort(), atoi()) */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "STORE PRODUCT MANAGEMENT"
#define CFGDEBUG 1
#define MAIN_DATABASE_FILENAME "db_main.bin"
#define TEMP_DATABASE_FILENAME "db_temp.bin"
#define LINE_DATA_MAX_SIZE 1024
#define FIELD_DATA_MAX_SIZE 32
#define MAX_LINES 4096
#define MENU_ENTRY_LOWEST 1
#define MENU_ENTRY_HIGHEST 5
#define CLS_MINI_SIZE 5 /* used in display_main_menu() to push up text  */

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

struct storage_t {
	char id[FIELD_DATA_MAX_SIZE]; /* id */
	char pc[FIELD_DATA_MAX_SIZE]; /* product_code */
	char pd[FIELD_DATA_MAX_SIZE]; /* product_desc */
	char pr[FIELD_DATA_MAX_SIZE]; /* price */
	char pl[LINE_DATA_MAX_SIZE]; /* pl */
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
int count_lines_in_file(const char *db_main_file);
void req_input_ID_to_edit(int lines);
void req_input_ID_to_delete(int lines);
int handle_choose_entry_to_edit(int lines);
int handle_choose_entry_to_delete(int lines);
void enforce_title_case(char *p_str);
void enforce_all_caps(char *p_str);
void display_msg_req_product_code(void);
void handle_data_input_product_code(char data_slot[FIELD_DATA_MAX_SIZE + 1]);
void display_msg_req_product_desc(void);
void handle_data_input_product_desc(char data_slot[FIELD_DATA_MAX_SIZE + 1]);
void display_msg_req_price(void);
void handle_data_input_price(char data_slot[FIELD_DATA_MAX_SIZE + 1]);
void copy_tempdb_to_maindb(const char *db_main_file, const char *db_temp_file);
void modify_existing_product(const char *db_main_file);
void add_new_product(const char *db_main_file);
void renumber_entries(const char *db_main_file);
void delete_product(const char *db_main_file);
void display_all_products(const char *db_main_file);
void display_main_menu(void);
void actionChoice(int choice, const char *db_main_file);
int getChoice(void);
void mainLoop(const char *db_main_file);
int add_product_to_db(const char *id, const char *product_code,
		      const char *product_desc, const char *price,
		      const char *db_main_file);
int create_default_db(const char *db_main_file);
int test_main_db(const char *db_main_file);

/* PROGRAM ENTRY POINT */
int main(void)
{
	const char db_main_file[] = MAIN_DATABASE_FILENAME;
	int lines = 0;
	int ret = -1;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\n");
	ret = test_main_db(db_main_file);
	if (0 ==
	    ret) { /* main DB exists & can be opened for read-write access*/
		printf("MainDB exists & can be accessed in read-write mode. Not"
		       " creating the default database\n");
	} else {
		printf("MainDB does not exist or cannot be accessed in read-"
		       "write mode. Re-creating the default database\n");
		create_default_db(db_main_file);
	}
	lines = count_lines_in_file(db_main_file);
	lines++;
	mainLoop(db_main_file);

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
int count_lines_in_file(const char *db_main_file)
{
	FILE *fp_maindb;
	int count = 0;
	char buf[LINE_DATA_MAX_SIZE];

	if (CFGDEBUG) {
		printf("Opening file %s with r (read-only) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		return 1;
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	while (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		count++;
	}
	fclose(fp_maindb);
	printf("Found %d products in the database...\n", count);
	if (CFGDEBUG) {
		printf("Closed file %s\n", db_main_file);
	}
	return count;
}

void req_input_ID_to_edit(int lines)
{
	printf("\nEnter the record ID to modify (min: 1, max: %d) or 0 to go "
	       "back: ",
	       lines);
}

int handle_choose_entry_to_edit(int lines)
{
	static char temp;
	int n = -1;
	do {
		req_input_ID_to_edit(lines);
		FLUSH
		n = -1;
		/***************************************************************
		 * When ` char is entered as ID, clang starts flooding the
		 * screen with "error invalid entry!" error message.
		 * As a workaround using the hack below!
		 *
		 * A temp statement to clear buffer - used only for Clang.
		 * Without this hack, Clang (the version listed below) skips
		 * over data-input phase!
		 * 	clang version 6.0.0 (tags/RELEASE_600/final)
		 *	Target: i686-pc-windows-msvc
		 **************************************************************/
		temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
		scanf("%c", &temp);
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif
		/**************************************/
		scanf("%d", &n);
		if (n < 0 || n > lines) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 0 || n > lines);
	return n;
}

void req_input_ID_to_delete(int lines)
{
	printf("\nEnter the record ID to delete (min: 1, max: %d) or 0 to go "
	       "back: ",
	       lines);
}

int handle_choose_entry_to_delete(int lines)
{
	static char temp;
	int n = -1;
	do {
		req_input_ID_to_delete(lines);
		FLUSH
		n = -1;
		/***************************************************************
		 * When ` char is entered as ID, clang starts flooding the
		 * screen with "error invalid entry!" error message.
		 * As a workaround using the hack below!
		 *
		 * A temp statement to clear buffer - used only for Clang.
		 * Without this hack, Clang (the version listed below) skips
		 * over data-input phase!
		 * 	clang version 6.0.0 (tags/RELEASE_600/final)
		 *	Target: i686-pc-windows-msvc
		 **************************************************************/
		temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
		scanf("%c", &temp);
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif
		/**************************************/
		scanf("%d", &n);
		if (n < 0 || n > lines) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 0 || n > lines);
	return n;
}

void enforce_title_case(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);
	for (n = 0; n < len; n++) {
		/* the very first char should be capitalized */
		if (0 == n) {
			p_str[0] = toupper(p_str[0]);
			/* for 2nd char onward, upper case the char ONLY IF the
			 * previous char is a space */
		} else if ((n > 0) && (' ' == p_str[n - 1])) {
			p_str[n] = toupper(p_str[n]);
		} else { /* all other chars should be lower case */
			p_str[n] = tolower(p_str[n]);
		}
	}
}

void enforce_all_caps(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);
	for (n = 0; n < len; n++) {
		p_str[n] = toupper(p_str[n]);
	}
}

void display_msg_req_product_code(void)
{
	printf("\nEnter product code (" XSTR(FIELD_DATA_MAX_SIZE) " chars max) or 0 to "
							 "go back: ");
}

void handle_data_input_product_code(char data_slot[FIELD_DATA_MAX_SIZE + 1])
{
	static char temp;
	display_msg_req_product_code();
	FLUSH
	/***************************************************************
	 * When ` char is entered, clang starts flooding the screen with "error
	 * invalid entry!" error message. As a workaround using the hack below!
	 *
	 * A temp statement to clear buffer - used only for Clang.
	 * Without this hack, Clang (the version listed below) skips
	 * over data-input phase!
	 * 	clang version 6.0.0 (tags/RELEASE_600/final)
	 *	Target: i686-pc-windows-msvc
	 **************************************************************/
	temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
	scanf("%c", &temp);
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif
	/**************************************/
	scanf("%" XSTR(FIELD_DATA_MAX_SIZE) "[^\n]", data_slot);
	enforce_all_caps(data_slot);
}

void display_msg_req_product_desc(void)
{
	printf("Enter product description (" XSTR(FIELD_DATA_MAX_SIZE) " chars max) or 0"
							      " to go back: ");
}

void handle_data_input_product_desc(char data_slot[FIELD_DATA_MAX_SIZE + 1])
{
	static char temp;
	display_msg_req_product_desc();
	FLUSH
	/**************************************/
	/*
	 * A temp statement to clear buffer - this is used only for Clang.
	 * Without this hack, Clang (the version listed below) skips over
	 * data-input phase!
	 * 	clang version 6.0.0 (tags/RELEASE_600/final)
	 *	Target: i686-pc-windows-msvc
	 */
	temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
	scanf("%c", &temp);
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif
	/**************************************/
	scanf("%" XSTR(FIELD_DATA_MAX_SIZE) "[^\n]", data_slot);
	enforce_title_case(data_slot);
}

void display_msg_req_price(void)
{
	printf("Enter price (" XSTR(FIELD_DATA_MAX_SIZE) " chars max): ");
}

void handle_data_input_price(char data_slot[FIELD_DATA_MAX_SIZE + 1])
{
	static char temp;
	display_msg_req_price();
	FLUSH
	/**************************************/
	/*
	 * A temp statement to clear buffer - this is used only for Clang.
	 * Without this hack, Clang (the version listed below) skips over
	 * data-input phase!
	 * 	clang version 6.0.0 (tags/RELEASE_600/final)
	 *	Target: i686-pc-windows-msvc
	 */
	temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
	scanf("%c", &temp);
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif
	/**************************************/
	scanf("%" XSTR(FIELD_DATA_MAX_SIZE) "[^\n]", data_slot);
	/* TODO: add "check isdigit?" step here to prevent incorrect entries */
}

void copy_tempdb_to_maindb(const char *db_main_file, const char *db_temp_file)
{
	FILE *fp_maindb;
	FILE *fp_tempdb;
	char ch;

	/* open source */
	if ((fp_tempdb = fopen(db_temp_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_temp_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("\tSuccessfully opened file %s\n", db_temp_file);
		}
	}
	/* open destination */
	if ((fp_maindb = fopen(db_main_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}
	/* copy freshly-updated temp-db's full content on to main-db */
	if (CFGDEBUG) {
		printf("Copying contents of tempdb over to the main db...\n");
	}
	while ((ch = getc(fp_tempdb)) != EOF) {
		putc(ch, fp_maindb);
	}
	if (CFGDEBUG) {
		printf("File copy completed!\n");
	}
	fclose(fp_tempdb);
	fclose(fp_maindb);
}

void modify_existing_product(const char *db_main_file)
{
	const char db_temp_file[] = TEMP_DATABASE_FILENAME;
	FILE *fp_maindb;
	FILE *fp_tempdb;
	int id = -2;
	int lines = count_lines_in_file(db_main_file);
	char ch;
	int current_line = 1;
	char buf[LINE_DATA_MAX_SIZE];
	struct storage_t s;

	/* initialize struct */
	strcpy(s.id, "");
	strcpy(s.pc, "");
	strcpy(s.pd, "");
	strcpy(s.pr, "");
	strcpy(s.pl, "");

	id = handle_choose_entry_to_edit(lines);
	if (0 == id) {
		printf("Going back to Main Menu\n");
		return;
	}

	/* open file for read-write access */
	if (CFGDEBUG) {
		printf("Opening file %s with r+ (read-write) access mode..."
		       "\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r+")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	/* find entry to edit */
	do {
		ch = getc(fp_maindb);
		if (ch == '\n') {
			current_line++;
			if (CFGDEBUG) {
				printf("current_line is now:\t%d\n",
				       current_line);
			}
		}
	} while ((ch != EOF) && (current_line < id));
	if (1 == id) { /* without this, 1st entry's ID is not displayed */
		fseek(fp_maindb, -1, 1);
	}
	if (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		printf("\nHere is the chosen record:\t");
		printf("%s", buf);
	}

	sprintf(s.id, "%d", id);
	printf("Product ID number (%s) will stay the same.\n", s.id);

	/* ask for fields */
	handle_data_input_product_code(s.pc);
	if ('0' == s.pc[0]) { /* did the user request a go-back-to-main-menu? */
		printf("Going back to Main Menu\n");
		return;
	} else {
		printf("Product Code has been read as: %s\n\n", s.pc);
	}

	handle_data_input_product_desc(s.pd);
	if ('0' == s.pd[0]) { /* did the user request a go-back-to-main-menu? */
		printf("Going back to Main Menu\n");
		return;
	} else {
		printf("Product Description has been read as: %s\n\n", s.pd);
	}

	handle_data_input_price(s.pr);
	printf("Price has been read as: %s\n", s.pr);

	/* combine fields to form a product-entry-line */
	strcat(s.pl, s.id);
	strcat(s.pl, "|");
	strcat(s.pl, s.pc);
	strcat(s.pl, "|");
	strcat(s.pl, s.pd);
	strcat(s.pl, "|");
	strcat(s.pl, s.pr);
	strcat(s.pl, "\n");
	printf("\nNew Product Line is:\t\t\t%s", s.pl);

	/* create a temp new db file - if it exists, wipe the existing file */
	if (CFGDEBUG) {
		printf("\tCreating/Overwriting file %s with w (overwrite) "
		       "access mode...\n",
		       db_temp_file);
	}
	if ((fp_tempdb = fopen(db_temp_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_temp_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_temp_file);
		}
	}

	/* copy over all entries UP UNTIL this one to the new db file */
	rewind(fp_maindb); /* start from beginning of file */
	current_line = 1;
	/* loop: read a line, write a line, until we reach record to modify */
	while (current_line != id) {
		/* read a line into buffer & write it in to new db file */
		if (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
			if (CFGDEBUG) {
				printf("Here is the line in buffer now:\t");
				printf("%s", buf);
			}
			fputs(buf, fp_tempdb);
			if (CFGDEBUG) {
				printf("Wrote the line to fp_tempdb\n");
			}
			current_line++;
			if (CFGDEBUG) {
				printf("\ncurrent_line is now:\t%d\n",
				       current_line);
			}
		} else {
			printf("ERROR: fgets error!\n");
			exit(EXIT_FAILURE);
		}
	}

	fputs(s.pl, fp_tempdb); /* write the updated line to temp db */

	/* copy over entries AFTER the modified entry to the new db file but
	 * first seek the next line as the modified line should not be copied
	 * over */
	do {
		ch = getc(fp_maindb);
	} while ((ch != EOF) && (ch != '\n'));

	/* loop: read a line, write a line, until we reach EOF */
	while (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		if (CFGDEBUG) {
			printf("Here is the line in buffer now:\t");
			printf("%s", buf);
		}
		/* TODO: there is no error checking here! */
		fputs(buf, fp_tempdb);
		if (CFGDEBUG) {
			printf("Wrote the line to fp_tempdb\n");
		}
		current_line++;
		if (CFGDEBUG) {
			printf("\ncurrent_line is now:\t%d\n", current_line);
		}
	}
	fclose(fp_tempdb);
	fclose(fp_maindb);
	copy_tempdb_to_maindb(db_main_file, db_temp_file);
}

void add_new_product(const char *db_main_file)
{
	int lines = count_lines_in_file(db_main_file);
	int new_id = lines + 1;
	FILE *fp_maindb;
	struct storage_t s;

	/* initialize struct */
	strcpy(s.id, "");
	strcpy(s.pc, "");
	strcpy(s.pd, "");
	strcpy(s.pr, "");
	strcpy(s.pl, "");

	/* set new product id automatically */
	printf("New product ID has been automatically set to: %d\n", new_id);
	sprintf(s.id, "%d", new_id);

	/* prompt & obtain fields from user */
	handle_data_input_product_code(s.pc);
	if ('0' == s.pc[0]) { /* did the user request a go-back-to-main-menu? */
		printf("Going back to Main Menu\n");
		return;
	} else {
		printf("Product Code has been read as: %s\n\n", s.pc);
	}

	handle_data_input_product_desc(s.pd);
	if ('0' == s.pd[0]) { /* did the user request a go-back-to-main-menu? */
		printf("Going back to Main Menu\n");
		return;
	} else {
		printf("Product Description has been read as: %s\n\n", s.pd);
	}

	handle_data_input_price(s.pr);
	printf("Price has been read as: %s\n", s.pr);

	/* combine fields to form a product-entry-line */
	strcat(s.pl, s.id);
	strcat(s.pl, "|");
	strcat(s.pl, s.pc);
	strcat(s.pl, "|");
	strcat(s.pl, s.pd);
	strcat(s.pl, "|");
	strcat(s.pl, s.pr);
	strcat(s.pl, "\n");
	printf("\nNew Product Line is:\t\t\t%s", s.pl);

	/* fopen main db and append as last line */
	if ((fp_maindb = fopen(db_main_file, "a")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("\tSuccessfully opened file %s\n", db_main_file);
		}
	}
	fputs(s.pl, fp_maindb); /* write updated line into main db */
	fclose(fp_maindb);
}

void renumber_entries(const char *db_main_file)
{
	const char db_temp_file[] = TEMP_DATABASE_FILENAME;
	FILE *fp_maindb;
	FILE *fp_tempdb;
	int current_line;
	char buf[LINE_DATA_MAX_SIZE];
	int id;
	struct storage_t s;

	id = -1;

	/* open file for read-only access */
	if (CFGDEBUG) {
		printf("Opening file %s with r (read-only) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	/* create a temp new db file - if it exists, wipe the existing file */
	if (CFGDEBUG) {
		printf("\tCreating/Overwriting file %s with w (overwrite) "
		       "access mode...\n",
		       db_temp_file);
	}
	if ((fp_tempdb = fopen(db_temp_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_temp_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("\tSuccessfully opened file %s\n", db_temp_file);
		}
	}

	/* copy over all entries to the new db file BUT renumber first */
	rewind(fp_maindb); /* start from beginning of file */
	current_line = 0;
	/* loop: read a line, write a line, until we reach record to modify */
	while (fgets(buf, sizeof(buf), fp_maindb) != NULL) {
		/* empty initialize struct fields */
		strcpy(s.id, "");
		strcpy(s.pc, "");
		strcpy(s.pd, "");
		strcpy(s.pr, "");
		strcpy(s.pl, "");
		/* read a line into buffer & break apart to tokens */
		/*
		1	|WG01	|Water Glass	|499	<-- a DB line
		%[^|]	|%[^|]	|%[^|]		|%[^|]	<-- sscanf format
		%[^|]|%[^|]|%[^|]|%[^|]			<-- sscanf merged
		*/
		sscanf(buf, "%d|%31[^|]|%31[^|]|%31[^|]", &id, s.pc, s.pd, s.pr);
		id = current_line + 1;
		sprintf(s.id, "%d", id); /* convert numeric to string */
		if (CFGDEBUG) {
			printf("-----------------------------------------------"
			       "---------------------------------\n");
			printf("%s\n", s.id);
			printf("%s\n", s.pc);
			printf("%s\n", s.pd);
			printf("%s\n", s.pr);
		}
		/* combine fields to form a product-entry-line */
		strcat(s.pl, s.id);
		strcat(s.pl, "|");
		strcat(s.pl, s.pc);
		strcat(s.pl, "|");
		strcat(s.pl, s.pd);
		strcat(s.pl, "|");
		strcat(s.pl, s.pr);
		/*strcat(s.pl, "\n");*/
		if (CFGDEBUG) {
			printf("\nNew Product Line is:\t\t\t|%s|\n", s.pl);
		}
		/* write the updated line into temp db */
		fputs(s.pl, fp_tempdb);
		current_line++;
	}
	fclose(fp_tempdb);
	fclose(fp_maindb);
	copy_tempdb_to_maindb(db_main_file, db_temp_file);
	if (remove(db_temp_file) == 0) {
		if (CFGDEBUG) {
			printf("File %s has been DELETED.\n", db_temp_file);
		}
	} else {
		fprintf(stderr, "Error deleting the file %s.\n", db_temp_file);
	}
}

void delete_product(const char *db_main_file)
{
	const char db_temp_file[] = TEMP_DATABASE_FILENAME;
	FILE *fp_maindb;
	FILE *fp_tempdb;
	int id = -2;
	int lines = count_lines_in_file(db_main_file);
	char ch;
	int current_line = 1;
	char buf[LINE_DATA_MAX_SIZE];
	/*id = handle_choose_entry_to_edit(lines);*/
	id = handle_choose_entry_to_delete(lines);
	if (0 == id) {
		printf("Going back to Main Menu\n");
		return;
	}

	/* open file for read-write access */
	if (CFGDEBUG) {
		printf("Opening file %s with r+ (read-write) access mode..."
		       "\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r+")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	/* find entry to edit */
	do {
		ch = getc(fp_maindb);
		if (ch == '\n') {
			current_line++;
			if (CFGDEBUG) {
				printf("current_line is now:\t%d\n",
				       current_line);
			}
		}
	} while ((ch != EOF) && (current_line < id));
	if (1 == id) { /* without this, 1st entry's ID is not displayed */
		fseek(fp_maindb, -1, 1);
	}
	if (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		printf("\nHere is the record you wish to delete:\t\t\t");
		printf("%s", buf);
	}
	printf("Proceeding with product deletion...\n"); /* TODO add 'Y/N?'' */

	/* create a temp new db file - if it exists, wipe the existing file */
	if (CFGDEBUG) {
		printf("\tCreating/Overwriting file %s with w (overwrite) "
		       "access mode...\n",
		       db_temp_file);
	}
	if ((fp_tempdb = fopen(db_temp_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_temp_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("\tSuccessfully opened file %s\n", db_temp_file);
		}
	}

	/* copy over all entries UP UNTIL this one to the new db file */
	rewind(fp_maindb); /* start from beginning of file */
	current_line = 1;
	/* loop: read a line, write a line, until we reach record to modify */
	while (current_line != id) {
		/* read a line into buffer & write it in to new db file */
		if (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
			if (CFGDEBUG) {
				printf("Here is the line in buffer now:\t");
				printf("%s", buf);
			}
			fputs(buf, fp_tempdb);
			if (CFGDEBUG) {
				printf("Wrote the line to fp_tempdb\n");
			}
			current_line++;
			if (CFGDEBUG) {
				printf("\ncurrent_line is now:\t%d\n",
				       current_line);
			}
		} else {
			printf("ERROR: fgets error!\n");
			exit(EXIT_FAILURE);
		}
	}

	/* copy over entries AFTER the modified entry to the new db file */
	/* seek the next line as the to-be-deleted line shouldn't be copied */
	do {
		ch = getc(fp_maindb);
	} while ((ch != EOF) && (ch != '\n'));

	/* loop: read a line, write a line, until we reach EOF */
	while (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		if (CFGDEBUG) {
			printf("Here is the line in buffer now:\t");
			printf("%s", buf);
		}
		/* TODO: there is no error checking here! */
		fputs(buf, fp_tempdb);
		if (CFGDEBUG) {
			printf("Wrote the line to fp_tempdb\n");
		}
		current_line++;
		if (CFGDEBUG) {
			printf("\ncurrent_line is now:\t%d\n", current_line);
		}
	}
	fclose(fp_tempdb);
	fclose(fp_maindb);
	copy_tempdb_to_maindb(db_main_file, db_temp_file);
	if (remove(db_temp_file) == 0) {
		if (CFGDEBUG) {
			printf("File %s has been DELETED.\n", db_temp_file);
		}
	} else {
		fprintf(stderr, "Error deleting the file %s.\n", db_temp_file);
	}
	renumber_entries(db_main_file);
	printf("Product has been DELETED.\n");
}

void display_all_products(const char *db_main_file)
{
	FILE *fp_maindb;
	char buf[LINE_DATA_MAX_SIZE] = "";
	int count = 0;

	if (CFGDEBUG) {
		printf("Opening file %s with r (read-only) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
		printf("\n********** All Products **********\n");
	}
	while (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		count++;
		printf("%s", buf);
	}
	printf("**********************************\n");
	fclose(fp_maindb);
	if (CFGDEBUG) {
		printf("Closed file %s\n", db_main_file);
	}
}

void display_main_menu(void)
{
	/* without this ugly hack double quotes do get printed :( */
	char title[] = XSTR(TITLE);
	unsigned int len = strlen(title);
	title[0] = ' ';       /* first double quote */
	title[len - 1] = ' '; /* second double quote */
	{
		int n;
		for (n = 0; n < CLS_MINI_SIZE; n++) {
			printf("\n");
		}
	}
	printf("***************************************************************"
	       "*************\n"
	       "***%s- MAIN MENU ***\n"
	       "\nValid Choices:\n"
	       "\t1: DISPLAY All Products Ordered by ID (Asc.)\n"
	       "\t2: ADD a New Product\n"
	       "\t3: DELETE a Product\n"
	       "\t4: MODIFY an Existing Product\n"
	       "\t5: EXIT Program\n"
	       "***************************************************************"
	       "*************\n"
	       "Enter your choice: ",
	       title);
}

void actionChoice(int choice, const char *db_main_file)
{
	static int this_is_initial_run; /* static so the initial value is '0' */
	switch (choice) {
	case 1:
		/* show this once to push up initial text on screen */
		if (0 == this_is_initial_run) {
			this_is_initial_run++;
			printf("\n\n\n\n\n\n\n\n\n\n\n");
		}
		printf("*** DISPLAYING All Products Ordered by ID (Asc.) "
		       "***\n");
		display_all_products(db_main_file);
		break;
	case 2:
		printf("\n*** ADDING a New Product ***\n");
		add_new_product(db_main_file);
		break;
	case 3:
		printf("\n*** DELETING a Product ***\n");
		delete_product(db_main_file);
		break;
	case 4:
		printf("\n*** MODIFYING an Existing Product ***\n");
		modify_existing_product(db_main_file);
		break;
	case 5:
		printf("\n*** EXITING Program ***\nGoodbye!\n");
		exit(EXIT_SUCCESS);
	default:
		printf("ERROR: hit the 'default' entry in switch?!\n");
		exit(EXIT_FAILURE);
	}
}

int getChoice(void)
{
	static char temp;
	int n = -1;
	do {
		display_main_menu();
		FLUSH
		n = -1;
		/***************************************************************
		 * When ` char is entered as ID, clang starts flooding the
		 * screen with "error invalid entry!" error message.
		 * As a workaround using the hack below!
		 *
		 * A temp statement to clear buffer - used only for Clang.
		 * Without this hack, Clang (the version listed below) skips
		 * over data-input phase!
		 * 	clang version 6.0.0 (tags/RELEASE_600/final)
		 *	Target: i686-pc-windows-msvc
		 **************************************************************/

		/*
		 * Another issue is that the first char could be a legit menu
		 * choice therefore we must test and if necessary use it
		 **************************************************************/
		temp += 0; /* just to avoid unused var warning */
#if defined(__clang__) && (__clang_major__ == 6)
		scanf("%c", &temp);
		if (isdigit(temp) != 0) {
			/* it's a digit, don't take input again. jump over. */
			n = temp - '0';
			goto PROCESS_INPUT;
		}
#elif defined(__GNUC__) || defined(__GNUG__)
/*....*/
#elif defined(_MSC_VER)
/*....*/
#endif

		/**
		 * Due to the above hack, non-clang-6.x compilers might complain
		 * "Label is defined but not used! -Werror=unused-label"
		 * this useless check has been added to prevent a complaint.
		 **/
		if (1 > 2) {
			goto PROCESS_INPUT;
		}
		/**************************************************************/
		scanf("%d", &n);
	PROCESS_INPUT:
		if (n < 1 || n > MENU_ENTRY_HIGHEST) {
			printf("ERROR: INVALID ENTRY! PLEASE TRY AGAIN\n");
		}
	} while (n < 1 || n > MENU_ENTRY_HIGHEST);
	return n;
}

void mainLoop(const char *db_main_file)
{
	int firstRun = 1;
	int choice;

	while (1) {
		if (firstRun) {
			choice = 1; /* show entries on initial run */
		} else {
			choice = getChoice();
		}
		printf("\n");
		actionChoice(choice, db_main_file);
		if (firstRun) {
			firstRun = 0;
		}
	}
}

int add_product_to_db(const char *id, const char *product_code,
		      const char *product_desc, const char *price,
		      const char *db_main_file)
{
	FILE *fp_maindb;
	int id_int = 0;
	char product_line[FIELD_DATA_MAX_SIZE];

	/* only when adding the very first entry, wipe the db file */
	id_int = atoi(id);
	if (CFGDEBUG) {
		printf("id_int is: %d\t", id_int);
	}
	if (1 == id_int) {
		if (CFGDEBUG) {
			printf("\tCreating/Overwriting file %s with w"
			       "(overwrite) access mode...\n",
			       db_main_file);
		}
		if ((fp_maindb = fopen(db_main_file, "w")) == NULL) {
			printf("ERROR: Cannot open file %s!\n", db_main_file);
			return 1;
		} else {
			if (CFGDEBUG) {
				printf("\tSuccessfully opened file %s\n",
				       db_main_file);
			}
		}
	} else {
		if (CFGDEBUG) {
			printf("\tAppending to file %s with a (append) access "
			       "mode...\n",
			       db_main_file);
		}
		if ((fp_maindb = fopen(db_main_file, "a")) == NULL) {
			printf("ERROR: Cannot open file %s!\n", db_main_file);
			return 1;
		} else {
			if (CFGDEBUG) {
				printf("\tSuccessfully opened file %s\n",
				       db_main_file);
			}
		}
	}
	product_line[0] = '\0';
	strcat(product_line, id);
	strcat(product_line, "|");
	strcat(product_line, product_code);
	strcat(product_line, "|");
	strcat(product_line, product_desc);
	strcat(product_line, "|");
	strcat(product_line, price);
	strcat(product_line, "\n");

	if (CFGDEBUG) {
		printf("Product line is:\t%s", product_line);
	}
	fputs(product_line, fp_maindb);
	fclose(fp_maindb);
	if (CFGDEBUG) {
		printf("\tClosed file %s\n", db_main_file);
	}
	
	return 0;
}

int create_default_db(const char *db_main_file)
{
	/**
	 * DATABASE FORMAT & DEFAULT DATABASE CONTENT
	 * Product ID	| Product Code	| Product description	| Price
	 * 1		| WG01		| Water Glass		| 4.99
	 * 2		| WG02		| Wine Glass		| 9.99
	 * 3		| EC01		| Espresso Cup		| 6.99
	 * 4		| CG01		| Cocktail Glass	| 8.99
	 * 5		| TM01		| Tea Mug		| 5.99
	 **/
	FILE *fp_maindb;
	char default_products[] =	"1|WG01|Water Glass|4.99\n"
					"2|WG02|Wine Glass|9.99\n"
					"3|EC01|Espresso Cup|6.99\n"
					"4|CG01|Cocktail Glass|8.99\n"
					"5|TM01|Tea Mug|5.99\n";

	if (CFGDEBUG) {
		printf("\tCreating/Overwriting file %s with w"
		       "(overwrite) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		return 1;
	} else {
		if (CFGDEBUG) {
			printf("\tSuccessfully opened file %s\n",
			       db_main_file);
		}
	}

	fputs(default_products, fp_maindb);
	fclose(fp_maindb);
	if (CFGDEBUG) {
		printf("\tClosed file %s\n", db_main_file);
	}
	return 0;
}

/**
 * RETURN CODES
 *
 *  0 = main DB exists & can be opened for read-write access
 * -1 = main DB either does not exist or read-write access cannot be obtained
 **/
int test_main_db(const char *db_main_file)
{
	FILE *fp_maindb;

	/* attempt opening file for read-write access */
	if (CFGDEBUG) {
		printf("Opening file %s with r+ (read-write) access mode..."
		       "\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r+")) == NULL) {
		if (CFGDEBUG) {
			printf("ERROR: Cannot open file %s!\n", db_main_file);
		}
		return -1;
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
		fclose(fp_maindb);
		if (CFGDEBUG) {
			printf("Closed file %s\n\n", db_main_file);
		}
		return 0;
	}
}

/* ===================================80 chars=============================== */
/* EOF */
