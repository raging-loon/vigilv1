
# Contributing Guidelines

If you wish to contribute, please email me at cxmacolley@gmail.com. Please make the subject CONTRIBUTING.

If you wish to have a feature added, please email me with the same address, but make the subject FEATURE REQUEST.

## Code Style 

Please include only necessary header files. If you see an unnecesary header file, feel free to remove it, but comment that you did so.

Functions are written in lower snake case, constants and macros are written in screaming snake case. 

Functions and control structures must be written as follows:
```C
int xyzfunction(){
  if(somecondition){
    // do stuff
  }

  while(stuff){
    do_other_things();
  }

}
```

## Comments
Functions must be commented with their purpose. Also, the general purpose of a file should also be commented.

Note that this is an ongoing process for pre existing headers/files/functions.

Members of a structure should also be commented on unless the are straightforward or self explanatory. For example:

```C
struct a_structure{
  void(f_ptr*)(); // this handles xyz
  char * ip_addr;
  // ^ this is self explanatory
};

```

## Licenses
Please add the following comment in the beggining of each file(if its not C, use the other languages comments):
```C
/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
```