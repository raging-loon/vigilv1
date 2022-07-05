# Setup

## Installation
The installation is simple: run the ```install.sh``` script in the install directory.

The required packages are listed below(they are installed in the install script):
- libssl-dev
- libsqlite3-dev
- liblua5.3-dev
- gcc
- make
- sqlite3

## Configuration
All of the configuration files are located in ```/etc/vigil/```. 
File | Purpose
-----|--------
vigil.conf | Main config file. Most things can be configure here 
domainm.conf | Malicious Domain Configuration
deny.cony | Explicit Deny Configuration

## Main Configuration

### Rule Configuration

Rule files must start with a '$' otherwise they will not be parsed. Typically, rule files with have a .rule extension, however, this is not required.

The Global Alert Method(GAM) must be set before any of the rules are parsed, otherwise, there will be chaos.
Please set the ```global_alert_method``` variable according to your organizations needs.

### GAM Configuration
GAM can be one of five things: STDOUT, log, IPC, Lua Scripts, or SOL.

STDOUT is the default when you first install, it will simply print the alerts to the screen.

Log will save the alerts to a log file located in ```/var/log/vigil/```

Inter Process Communication(IPC) GAM involves the installation of another program called the IPC-Router. This will handle alerts in other customizable ways as well as allow for remote configuration and monitoring.

A Lua Script written can be run when there is an alert. See the Lua Script Guide for more details.

Shared Object Loading allows you to write and compile programs in C(NOT C++) and have them loaded at runtime. This is usually much faster that Lua, but takes more time to write