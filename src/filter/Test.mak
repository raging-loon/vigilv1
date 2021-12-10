all: test clean

rule_parser.o:
	gcc -c parsing/rule_parser.c

# test: rule_parser.o
# 	echo "This is test Makefile for testing the rule parser"
# 	gcc -o test.exe $^

alerts.o:
	gcc -c actions/alerts.c

packet_parser.o:
	gcc -c parsing/packet_parser.c

test_main.o:
	gcc -c test_main.c

test: rule_parser.o alerts.o packet_parser.o test_main.o 
	gcc -o test.exe $^
clean:
	rm *.o