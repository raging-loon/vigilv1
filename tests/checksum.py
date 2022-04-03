

times = [16675675,16678678,16678679,16689030,16690401]
counts = [times[4] - times[3], times[3] - times[2], times[2] - times[1], times[1] - times[0]]
print(counts)
def get_avg(arr):
  avg = 0
  for i in arr:
    avg += i
  return avg / len(arr)

print(get_avg(counts))