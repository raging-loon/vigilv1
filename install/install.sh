# the installation file for the UTM 
apt install libpcap-dev libssl-dev libsqlite3-dev liblua5.3-dev
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

mkdir /usr/share/vigil/scripts/
cp src/lua/scripts/* /usr/share/vigil/scripts/
cp lscript.conf /etc/vigil/

sqlite3 spi.db < src/database/install_spi.sql
cp spi.db /usr/share/vigil/

mkdir /usr/share/vigil/stats/
mkdir /usr/share/vigil/stats/pps/

# cd ../
make
cp memmap.txt /usr/share/vigil

openssl genrsa -out privkey.pem 2048
openssl rsa -in privkey.pem -pubout -out pubkey.crt
openssl pkcs8 -topk8 -inform PEM -outform PEM -nocrypt -in privkey.pem -out pkcs8.key
mkdir /etc/vigil/keys/
mv privkey.pem pubkey.crt pkcs8.key /etc/vigil/keys