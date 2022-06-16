<!--[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/raging-loon/vigil.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/raging-loon/vigil/context:cpp) -->
# Vigil
Vigil IDS
## Requirements
Runs well on Debian based linux distributions
Requires the following to run:
  - gcc 
  - make 
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
 - Packet capturing using the raw sockets
 - Basic rules for signature based attack identification
 - Logging 
 
## Installation
You just need to run install.sh and make
Nlease note that the database comes preconfigured and empty with the package. It is in the file "/vigil.db".

## Copyright
See the LICENSE file for more information about Copyright<br>
VIGIL Logo designed by Andrew Heishman
