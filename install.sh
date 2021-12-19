# the installation file
mkdir /usr/share/npsi
mkdir /usr/share/npsi/rules
cp src/rules /usr/share/npsi/rules
mkdir /etc/npsi
cp npsi.conf /etc/npsi/npsi.conf
mkdir /var/log/npsi/
touch /var/log/npsi/siglog.log