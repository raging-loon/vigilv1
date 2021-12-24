# the installation file
apt install libpcap-dev libssl-dev
mkdir /usr/share/npsi
mkdir /usr/share/npsi/rules
cp -r src/rules /usr/share/npsi/rules
mkdir /etc/npsi
cp npsi.conf /etc/npsi/npsi.conf
cp deny.conf /etc/npsi/deny.conf
mkdir /var/log/npsi/
touch /var/log/npsi/siglog.log
touch /etc/npsi/passwd
chmod +x nshadduser
cp nshadduser /bin
touch /var/log/npsi/login.log
touch /var/log/npsi/fail.log