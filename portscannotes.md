# Notes for portscan detection
Open does port 80 and closed does port 81
## nmap -sV 45.33.32.156
lhost\[syn\] ----> rhost  < this repeats about 30 times <br />
rhost\[rst\] ----> lhost < this reapets about 30 times <br />
<hr>

## zmap -p 80 45.33.32.156
### Open
lhost ----> rhost    SYN <br />
rhost  ----> lhost   SYN, ACK <br />
lhost ----> rhost    RST <br />
### Closed
lhost ----> rhost     SYN <br /> 
rhost ----> lhost     RST, ACK <br />

<hr>

## masscan -p 80 --range 45.33.32.156
### Open
lhost --> rhost   SYN   <br />
rhost --> lhost   SYN, ACK  <br />
lhost --> rhost   RST <br />
lhost --> rhost   RST<br />
### Closed
lhost --> rhost   SYN<br />
rhost --> lhost   RST, ACK <br />
lhost --> rhost   RST<br />

<hr>

## nmap -sM 45.33.32.156 -p 80 (Maimon Scan)
### Open
lhost --> rhost     ICMP echo <br />
lhost --> rhost     TCP SYN <br />
lhost --> rhost     TCP ACK <br />
lhost --> rhost     ICMP timstamp req <br />
rhost --> lhost     ICMP echo reply <br />
rhost --> lhost     RST <br />
rhost --> lhost     RST, ACK <br />
lhost --> rhost     FIN, ACK <br />
lhost --> rhost     FIN, ACK <br />
### Closed
Same as open

<hr>


## nmap -sW 45.33.32.156 -p 80

