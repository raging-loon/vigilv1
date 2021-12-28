# NPSI
Network Packet Sniffer and Inspector
## Notes
Runs well on Debian based linux distributions
Requires gcc, make, and libpcap-dev to run

## Features
 - Packet capturing using the libpcap library
 - Basic rules for signature based attack identification
 - Logging 
 - Remote login shell
 - Statistics
## Plans
 - [x] Add monitoring for total amount of packets sent and recieved
 - [x] Add monitoring for some layer 3 protocols for IPv4
 - [ ] Add the above for IPv6
 - [ ] Add traffic size monitoring
 - [ ] Add a background logging function[s]
 - [x] Come up with some configuration options
 - [ ] Better plan monitoring of hosts on the intranet
 - [x] Set up hexadecimal printing of packet data
 - [x] Figure out basic rule set up
 - [x] Reimplement the rule parser
 - [x] Add support for more than one rule per rule file
 - [x] Add support for protocol matching in rules
 - [x] Set up logging
 - [x] Set up alerting
 - [ ] Figure out the SNMP stuff
 - [ ] Figure out email alerts
 - [ ] Add everything from the ip_stats struct to the watchlist_member struct
 - [ ] Figure out the brute force stuff
 - [ ] Add arp cache and monitoring for it
 - [ ] Add internal and external mode