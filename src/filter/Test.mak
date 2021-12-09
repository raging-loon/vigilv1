all: test clean

rule_parser.o:
	gcc -c parsing/rule_parser.c

test: rule_parser.o
	echo "This is test Makefile for testing the rule parser"
	gcc -o test.exe $^

clean:
	rm *.o