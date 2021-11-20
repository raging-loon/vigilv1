all: npsi clean

pktmgr.o:
	gcc -c src/capture/pktmgr.c -l pcap

main.o:
	gcc -c main.c -l pcap
npsi: main.o pktmgr.o
	gcc -o npsi $^ -l pcap

clean:
	rm *.o