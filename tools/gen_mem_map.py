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
import argparse

argument_parser = argparse.ArgumentParser()
argument_parser.add_argument("-f","--file",type=str,help="path of executable")
args = argument_parser.parse_args()

###### CONSTANTS ######
# matches to something like "Disassembly of section .gnu.version:"
DISM_SECTION = "Disassembly of section.*"
DISM_FUNC = ".* <.*>:"
SECTION_PLT_FUNC = 0x01
SECTOIN_TEXT_FUNC = 0x02

class fn_loc:

  def __init__(self,name,start, end):
    self.name = name
    # V should be numbers
    self.start = start
    self.end = end
  def write_to_file(self,filename):
    filename.write("%s %s %s"%(self.name,self.start,self.end))

# should only be full of fn_loc
fn_mem_map = []


def main():
  parse_section = None
  fn_mem_locs = 0
  
  for i in open(args.file,"r"):
    print(i)



