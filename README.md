# NPSI
Network Packet Sniffer and Inspector
## Notes
Runs well on Debian based linux distributions
Requires gcc, make, and libpcap-dev to run

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
 - [ ] Come up with some configuration options
 - [ ] Better plan monitoring of hosts on the intranet
 - [ ] Figure out network placement for wired and wireless networks
 - [ ] Decode specific layer 3 protocols by port number
 - [ ] Set up hexadecimal printing of packet data
 - [ ] Figure out basic rule set up
 - [ ] Reimplement the rule parser
 - [ ] Set up logging
 - [ ] Set up alerting
 - [ ] Figure out the SNMP stuff