ipv6addr = "fe80:0000:0000:0000:0218:0aff:fe87:2ca5"

#
# Rules
# 1. remove leading zeroes
# 2. for 1 group of zeroes, replace with '::'
# 

def groupzeros(addr):
  realaddr = ""
  groups_zeros = 0;
  grst = grend = 0;
  hextexts_comp = 0;
  for i in addr.split(":"):
    if i != '0':
      realaddr += i
    else:
      



realaddr = groupzeros("fe80:0:0:0:218:0:0:2ca5")
print(realaddr)
