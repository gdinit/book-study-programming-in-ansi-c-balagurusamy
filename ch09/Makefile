DIRS=binary

$(shell mkdir -p $(DIRS))

all:
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 09pe01.c -o binary/09pe01

.PHONY : clean

clean:
