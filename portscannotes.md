# Notes for portscan detection
## Open Ports Found

### nmap -sV 45.33.32.156
lhost\[syn\] ----> rhost  < this repeats about 30 times
rhost\[rst\] ----> lhost < this reapets about 30 times
<hr>

### zmap -p 80 45.33.32.156
lhost ----> rhost    SYN
rhost  ----> lhost   SYN, ACK
lhost ----> rhost    RST
<hr>

### masscan -p 80 --range 45.33.32.156

lhost --> rhost   SYN
rhost --> lhost   SYN, ACK
lhost --> rhost   RST
lhost --> rhost   RST

### nmap -sM 45.33.32.156 -p 80 (Maimon Scan)

lhost --> rhost     ICMP echo
lhost --> rhost     TCP SYN
lhost --> rhost     TCP ACK
lhost --> rhost     ICMP timstamp req
rhost --> lhost     ICMP echo reply
rhost --> lhost     RST
rhost --> lhost     RST, ACK
lhost --> rhost     FIN, ACK
lhost --> rhost     FIN, ACK

### nmap -sW 45.33.32.156 -p 80

