ipv6addr = "fe80:0:0:0:218:aff:fe87:2ca5"

#
# Rules
# 1. remove leading zeroes
# 2. for 1 group of zeroes, replace with '::'
# 

def groupzeros(addr):
  realaddr = ""
  addr_groupings = ["",""]
  x = 0
  groups = 0
  for i in range(0,len(addr)):
    if(addr[i] == '0' and (addr[i + 1] == '0' or addr[i + 1] == ':')):
      x = 1
      addr_groupings[groups + 1] 


addr = groupzeros("fe80:0:0:0:218:0:0:2ca5")
print(addr)
