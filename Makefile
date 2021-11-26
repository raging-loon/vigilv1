all: npsi clean

icmpdsct.o:
	gcc -c src/capture/icmpdsct.c 
l2pktmgr.o:
	gcc -c src/capture/l2pktmgr.c
l3pktmgr.o:
	gcc -c src/capture/l3pktmgr.c
pktmgr.o:
	gcc -c src/capture/pktmgr.c -l pcap
main.o:
	gcc -c main.c -l pcap
utils.o:
	gcc -c src/utils.c
npsi: main.o pktmgr.o l2pktmgr.o utils.o l3pktmgr.o icmpdsct.o
	gcc -o npsi.exe $^ -l pcap

clean:
	rm *.o