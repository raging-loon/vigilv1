     
#  This file is part of Vigil.
#  Vigil is free software: you can redistribute it and/or modify it under the terms of the 
#  GNU General Public License as published by the Free Software Foundation, either version 3 
#  of the License, or (at your option) any later version.
#  
#	 Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
#  without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
#  
#	 See the GNU General Public License for more details.
#  You should have received a copy of the GNU General Public License along with Vigil. 
#  If not, see <https://www.gnu.org/licenses/>. 


CC = gcc
CFLAGS = -Wall
all: vigil clean


gets:
	$(CC) $(CFLAGS) -c $$(find ./ -name "*.c" -print | grep -v test)

vigil: gets
	set environment MALLOC_CHECK_ 2
	$(CC) -g -o nsense *.o -l pthread -l ssl -l crypto -l sqlite3  -l lua5.3

	objdump -D vigil.exe -M intel > objdump.txt
	python ../tools/gen_mem_map.py -f objdump.txt
	mv memmap.txt /usr/share/vigil/memmap.txt
	# rm objdump.txt 
	# strip vigil.exe

clean:
	rm *.o
