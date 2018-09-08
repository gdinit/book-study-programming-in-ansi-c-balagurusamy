DIRS=binary

$(shell mkdir -p $(DIRS))

all:
ifeq ($(OS),Windows_NT)
# MS-Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe01.c -o binary/12pe01.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe02.c bubble_sort.c -o binary/12pe02.exe
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe03.c -o binary/12pe03.exe
else
# non-MS-Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe01.c -o binary/12pe01
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe02.c bubble_sort.c -o binary/12pe02
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe03.c -o binary/12pe03
endif

.PHONY : clean

clean:
