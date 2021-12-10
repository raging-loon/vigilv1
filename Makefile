all: npsi clean

print_utils.o:
	gcc -c src/print_utils.c
main.o:
	gcc -c main.c -l pcap
ip_addr_stat.o:
	gcc -c src/statistics/ip_addr_stat.c -l pthread
igmp_dsct.o:
	gcc -c src/capture/protocols/igmp_dsct.c
icmpdsct.o:
	gcc -c src/capture/icmpdsct.c 
l2pktmgr.o:
	gcc -c src/capture/l2pktmgr.c
l3pktmgr.o:
	gcc -c src/capture/l3pktmgr.c
pktmgr.o:
	gcc -c src/capture/pktmgr.c -l pcap
rule_parser.o:
	gcc -c src/filter/parser/rule_parser.c
utils.o:
	gcc -c src/utils.c
tcpmgr.o:
	gcc -c src/capture/tcpmgr.c
udpmgr.o:
	gcc -c src/capture/udpmgr.c

alerts.o:
	gcc -c src/filter/actions/alerts.c

packet_parser.o:
	gcc -c src/filter/parsing/packet_parser.c
rule_parser.o:
	gcc -c src/filter/packet_parser/rule_parser.c

npsi: main.o pktmgr.o l2pktmgr.o utils.o l3pktmgr.o icmpdsct.o \
			tcpmgr.o udpmgr.o igmp_dsct.o ip_addr_stat.o print_utils.o
	gcc -o npsi.exe $^ -l pcap -l pthread
	strip npsi.exe
clean:
	rm *.o