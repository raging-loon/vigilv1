# VIGIL Documentation

## Directory Mapping
| Directory | Description|
| --------- | ---------- |
| /install  | install files|
| /ipcmon   | IPC listener
| /python-vigil| submodule for vigil API|
| /src       | main IDS |
| /tests     | random tests |
| /tools     | various tools such as memory mapping |
| /web       | web interface files

## Director Mapping: /src
| Directory | Description |
| --------- | ----------- |
| /backtrace| backtracing functions used in crashes|
| /capture  | capture engine and PDU decoding |
| /database | SQLite database handling |
| /filter   | rule parsing and application functions |
| /ips      | IPS functions(in dev) |
| /lua      | Lua Scripting Enigine |
| /monitoring | various monitoring metrics |
| /netif    | tools for detecting, verifiying, and search for NICs |
| /packets  | PDU Header structs |
| /rules    | built in rules |
| /scripts  | Some random scripts |
| /ssh      | Needs to be deleted |
| /statistics | various statistics, will probably be replaced with functions in /monitoring |
| /tasks    | Tasks, in dev |
| /vrmc     | Vigil Remote Monitoring and Configuration Server |