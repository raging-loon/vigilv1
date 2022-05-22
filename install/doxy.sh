declare origin=$(pwd)
declare $temppath=$(echo "${origin%install}")
doxygen Doxyfile
cd /docs
sh run.sh
cd $temppath