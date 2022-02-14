# the installation file for the UTM 
# the installation for the NSHclient is located in src/nshclient/
apt install libpcap-dev libssl-dev
mkdir /usr/share/noraa
mkdir /usr/share/noraa/rules
cp -r src/rules /usr/share/noraa/rules
mkdir /etc/noraa
cp noraa.conf /etc/noraa/noraa.conf
cp deny.conf /etc/noraa/deny.conf
cp domainm.conf /etc/noraa/
touch /etc/noraa/hosts.conf
mkdir /var/log/noraa/
touch /var/log/noraa/siglog.log
touch /etc/noraa/passwd
touch /usr/share/nspi/arpcache.csv
chmod +x nshadduser
cp nshadduser /bin
touch /var/log/noraa/login.log
touch /var/log/noraa/fail.log
