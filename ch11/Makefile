DIRS=binary

$(shell mkdir -p $(DIRS))

all:
ifeq ($(OS),Windows_NT)
# MS-Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe01.c -o binary/11pe01.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe03.c -o binary/11pe03.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe04.c -o binary/11pe04.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe06.c -o binary/11pe06.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe08.c -o binary/11pe08.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe09.c -o binary/11pe09.exe
else
# non-MS-Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe01.c -o binary/11pe01
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe03.c -o binary/11pe03
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe04.c -o binary/11pe04
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe06.c -o binary/11pe06
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe08.c -o binary/11pe08
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 11pe09.c -o binary/11pe09
endif

.PHONY : clean

clean:
