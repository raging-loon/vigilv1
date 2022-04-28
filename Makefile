CC = gcc 
CFLAGS = -Wdiscarded-qualifiers
all: vigil clean

print_utils.o:
	$(CC) $(CFLAGS) -c src/print_utils.c 
globals.o:
	$(CC) $(CFLAGS) -c globals.c 
main.o:
	$(CC) $(CFLAGS) -c main.c 
ip_addr_stat.o:
	$(CC) $(CFLAGS) -c src/statistics/ip_addr_stat.c  
tcp_chksum.o:
	$(CC) $(CFLAGS) -c src/engine/checksum/tcp_chksum.c

igmp_dsct.o:
	$(CC) $(CFLAGS) -c src/capture/protocols/igmp_dsct.c 
icmpdsct.o:
	$(CC) $(CFLAGS) -c src/capture/icmpdsct.c 
l2pktmgr.o:
	$(CC) $(CFLAGS) -c src/capture/l2pktmgr.c 
l3pktmgr.o:
	$(CC) $(CFLAGS) -c src/capture/l3pktmgr.c 
pktmgr.o:
	$(CC) $(CFLAGS) -c src/capture/pktmgr.c 
rule_parser.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/rule_parser.c 
utils.o:
	$(CC) $(CFLAGS) -c src/utils.c 
tcpmgr.o:
	$(CC) $(CFLAGS) -c src/capture/tcpmgr.c 
udpmgr.o: 
	$(CC) $(CFLAGS) -c src/capture/udpmgr.c  

http_disect.o:
	$(CC) $(CFLAGS) -c src/capture/protocols/http_disect.c 

dns_disect.o:
	$(CC) $(CFLAGS) -c src/capture/protocols/dns_disect.c 

alerts.o:
	$(CC) $(CFLAGS) -c src/filter/actions/alerts.c 

packet_parser.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/packet_parser.c 
#rule_parser.o:
#	$(CC) $(CFLAGS) -c src/filter/parsing/rule_parser.c
rule.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/rule.c 
nsh_server.o:
	$(CC) $(CFLAGS) -c src/rpc/nsh_server.c 

watchlist.o:
	$(CC) $(CFLAGS) -c src/statistics/watchlist.c 
wclean.o:
	$(CC) $(CFLAGS) -c src/statistics/wclean.c 

arpcache.o:
	$(CC) $(CFLAGS) -c src/statistics/arpcache.c 

update_db.o:
	$(CC) $(CFLAGS) -c src/database/update_db.c 

ftp-disect.o:
	$(CC) $(CFLAGS) -c src/capture/protocols/ftp-disect.c 
spi.o:
	$(CC) $(CFLAGS) -c src/engine/spi.c 

debug.o:
	$(CC) $(CFLAGS) -c src/debug.c 

forward.o:
	$(CC) $(CFLAGS) -c src/engine/firewall/forward.c 

logging.o:
	$(CC) $(CFLAGS) -c src/logging.c 

line_parser.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/line_parser.c 

rule_init.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/rule_init.c 

dp_size.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/dp_size.c 
homenet.o:
	$(CC) $(CFLAGS) -c src/filter/parsing/homenet.c 

lua_engine.o:
	$(CC) $(CFLAGS) -c src/lua/lua_engine.c
ip6decode.o:
	$(CC) $(CFLAGS) -c src/capture/ip6decode.c
backtrace.o:
	$(CC) $(CFLAGS) -c src/backtrace/backtrace.c
load_fn_map.o:
	$(CC) $(CFLAGS) -c src/backtrace/load_fn_map.c


vigil: globals.o pktmgr.o l2pktmgr.o utils.o l3pktmgr.o icmpdsct.o\
			tcpmgr.o udpmgr.o igmp_dsct.o ip_addr_stat.o print_utils.o\
			alerts.o packet_parser.o rule_parser.o rule.o main.o nsh_server.o\
			watchlist.o wclean.o arpcache.o \
			update_db.o http_disect.o dns_disect.o ftp-disect.o  debug.o\
			forward.o spi.o logging.o line_parser.o rule_init.o dp_size.o \
			homenet.o tcp_chksum.o lua_engine.o ip6decode.o backtrace.o \
			load_fn_map.o

			
	$(CC) -g -o vigil.exe $^ -l pcap -l pthread -l ssl -l crypto -l sqlite3 -l lua5.3
	objdump -D vigil.exe -M intel > objdump.txt
	python tools/gen_mem_map.py -f objdump.txt
	cp memmap.txt /usr/share/vigil/memmap.txt
	# strip vigil.exe

clean:
	rm *.o
