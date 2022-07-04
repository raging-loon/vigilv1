instances=$(ps aux | grep vigil | grep -v "grep\|startvigil" | wc -l )
if [ "$instances" != "0" ]; then
  echo "Vigil already running";
  exit
fi
/bin/vigil -i lo -q 