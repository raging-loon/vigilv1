ipv6addr = "fe80:0000:0000:0000:0218:0aff:fe87:2ca5"

#
# Rules
# 1. remove leading zeroes
# 2. for 1 group of zeroes, replace with '::'
# 


def rm_lead_zero(addr):
  shortenedipv6 = ""
  hextexts_comp = 0;
  for i in addr.split(":"):
    num_zeroes = 0;
    for zero in i:
      if(zero == '0'):
        num_zeroes += 1;
      else:
        break
    if(num_zeroes == 4):
      shortenedipv6 += '0'
    else:
      shortenedipv6 += i[num_zeroes:]
    if hextexts_comp != 7:
      shortenedipv6 +=":"
    hextexts_comp += 1
  return shortenedipv6

def groupzeros(addr):
  realaddr = ""
  groups_zeros = 0;
  hextexts_comp = 0
  for i in addr.split(":"):
    if i != '0':
      realaddr += i
    else:
      pass



addr = rm_lead_zero(ipv6addr)
realaddr = groupzeros(addr)
print(realaddr)
