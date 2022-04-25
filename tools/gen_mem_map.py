# Copyright 2021-2022 Conner Macolley
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#        http://www.apache.org/licenses/LICENSE-2.0
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
# 
# Generate Memory Map to be used by the crash handler in the main program
#


import re

# matches to something like "Disassembly of section .gnu.version:"
DISM_SECTION = "Disassembly of section.*"
x = "Disassembly of section .gnu.version:\n"
print(re.match(DISM_SECTION,x))
