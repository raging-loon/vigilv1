<!--[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/raging-loon/vigil.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/raging-loon/vigil/context:cpp) -->
# Vigil
Vigil IDS
## Requirements
Runs well on Debian based linux distributions
Requires the following to run:
  - gcc 
  - make 
  - libpcap-dev
  - sqlite3
  - libsqlite3-dev
  - liblua-5.3
  - libcurl-dev

Recommened stats for machine running:
 - Recommended 8GB RAM, minimum of 4GB
 - Fast CPU, as many cores as possible
 - Preferably a fast network connection
 - Large hard drive for logs if they are not outsourced

## Features
 - Packet capturing using the libpcap library
 - Basic rules for signature based attack identification
 - Logging 
 - Remote login shell
 - Statistics
## Installation
You just need to run install.sh and make
Note that if you are not planning on using the web interface and not using a sqlite database, then you need to mark "use_sqlite" in the config file as "NO".
Please note that the database comes preconfigured and empty with the package. It is in the file "/vigil.db".

## Plans
 - [x] Add monitoring for total amount of packets sent and recieved
 - [x] Add monitoring for some layer 3 protocols for IPv4
 - [ ] Add the above for IPv6
 - [ ] Add traffic size monitoring
 - [x] Add a background logging function[s]
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
 - [x] Add everything from the ip_stats struct to the watchlist_member struct
 - [ ] Figure out the brute force stuff
 - [ ] Add IP/IP6/TCP/UDP Checksum Algorithms
 - [x] Add arp cache and monitoring for it
 - [x] Add internal and external mode

## Todo
- [ ] Add ports for rules
- [ ] Add networks for rules
- [ ] IPv6 shortener
- [ ] DNS Response
- [ ] SPI for RST
- [ ] SPI for UDP
- [ ] SNMP 
- [ ] Testing with NAGIOS and Rsyslog


## Copyright
See the LICENSE file for more information about Copyright<br>
VIGIL Logo designed by Andrew Heishman