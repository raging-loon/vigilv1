# the installation file for the UTM 
# the installation for the NSHclient is located in src/nshclient/
apt install libpcap-dev libssl-dev
mkdir /usr/share/vigil
mkdir /usr/share/vigil/rules
cp src/rules/* /usr/share/vigil/rules/
mkdir /etc/vigil
cp vigil.conf /etc/vigil/vigil.conf
cp deny.conf /etc/vigil/deny.conf
cp domainm.conf /etc/vigil/
touch /etc/vigil/hosts.conf
mkdir /var/log/vigil/
touch /var/log/vigil/siglog.log
touch /etc/vigil/passwd
touch /usr/share/vigil/arpcache.csv
chmod +x src/scripts/nsh*
cp src/scripts/nsh* /bin
touch /var/log/vigil/login.log
touch /var/log/vigil/fail.log
