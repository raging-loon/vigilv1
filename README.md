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
 - [ ] Add more decoding for layer three protocols
    - [ ] STP
    - [ ] CDP
    - [ ] LLDP
 - [ ] Add a background logging function[s]
 - [x] Come up with some configuration options
 - [ ] Better plan monitoring of hosts on the intranet
 - [ ] Figure out network placement for wired and wireless networks
 - [ ] Decode specific layer 3 protocols by port number
 - [x] Set up hexadecimal printing of packet data
 - [x] Figure out basic rule set up
 - [x] Reimplement the rule parser
 - [x] Set up logging
 - [x] Set up alerting
 - [ ] Figure out the SNMP stuff