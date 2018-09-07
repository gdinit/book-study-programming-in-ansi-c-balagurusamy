DIRS=binary

$(shell mkdir -p $(DIRS))

all:
ifeq ($(OS),Windows_NT)
# Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe01.c -o binary/12pe01.exe
else
# non-Windows
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 12pe01.c -o binary/12pe01
endif

.PHONY : clean

clean:
