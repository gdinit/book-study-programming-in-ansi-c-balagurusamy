DIRS=binary

$(shell mkdir -p $(DIRS))

all:
ifeq ($(OS),Windows_NT)
# MS-Windows
#	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13pe01.c -o binary/13pe01.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop01.c -o binary/13wop01.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop02.c -o binary/13wop02.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop03.c -o binary/13wop03.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop04.c -o binary/13wop04.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop05.c -o binary/13wop05.exe
else
# non-MS-Windows
#	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13pe01.c -o binary/13pe01
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop01.c -o binary/13wop01
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop02.c -o binary/13wop02
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop03.c -o binary/13wop03
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop04.c -o binary/13wop04
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 13wop05.c -o binary/13wop05
endif

.PHONY : clean

clean:
