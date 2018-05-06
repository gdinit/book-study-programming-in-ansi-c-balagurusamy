# book-study-programming-in-ansi-c-balagurusamy

My solutions for programming exercises in the book 'Programming in ANSI C Seventh Edition' by E Balagurusamy

## About the Book

This is an excellent beginner's A-to-Z book on the C language. Looks like it's very popular in formal education in India (author's home). I found it via web search and I'm very happy with my choice - strongly recommended to any beginners to C language. Here is the official web site of the book: http://www.mhhe.com/balagurusamy/ansic7e

### Files in this git repo

Here you will see the source code files (01pe01.c) and Borland C++ IDE project files (01pe01.prj) for PEs (Programming Exercises), all organized into subdirectories based on book chapters. If you do not have the excellent book, you can still benefit from the exercises as each exercise is described at the top of source code file.

### Borland C++ 3? In 2018?!

Yes. I know it's outdated, I know it has 25 year old bugs but what can I say, I like it! In fact I love it!

I am not (completely) mad. I don't think Borland C++ 3 is a good choice for any sizeable project in 2018 *however* since my exercises are usually about 50 lines, it's working fine.

Note: Before committing to this git repo, I *also* test each example with a more modern compiler (at the moment: mingw32.i686-6.1.0-release-posix-dwarf-rt_v5-rev0) which caught many issues Borland C++ 3 simply didn't notice or warn me about.

Each example is tested for strict ANSI C compatibility as follows:
```
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
```

## Contributing

Any pull requests (bugfix, improvement) are more than welcome!

## Authors

* **gdinit** - *Programming Exercise Solutions* - [gdinit](https://github.com/gdinit)
* **Eric Sanchis** - *str5 functions* - [web](http://aral.iut-rodez.fr/en/sanchis/miscellaneous/str5/str5.html)

## License

* All **Programming Examples** belong to book's author E. Balagurusamy.
* All **Solutions** are my own attempt and is licensed under the GNU GPL v2 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
* Hat tip to anyone who's code was used (mentioned in source code files)

