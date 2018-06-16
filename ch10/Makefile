DIRS=binary

$(shell mkdir -p $(DIRS))

all:
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 10pe01.c -o binary/10pe01
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 10pe02.c -o binary/10pe02
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 10pe03.c -o binary/10pe03
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 10pe04.c -o binary/10pe04
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment -Wparentheses -Wformat-zero-length 10pe05.c -o binary/10pe05

.PHONY : clean

clean:
