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
# Generate graphs based on logs

import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime
import numpy

xpoints = numpy.array([])
ypoints = numpy.array([])
for i in open("/usr/share/vigil/stats/pps/pps.log.1.txt"):
  
  str_arr = i.split(",")
  # arr = numpy.append(arr,[int(str_arr[0]),int(str_arr[1])])
  xpoints = numpy.append(xpoints,datetime.fromtimestamp(int(str_arr[0])))
  ypoints = numpy.append(ypoints,int(str_arr[1]))

  


plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%H:%M:%S'))
plt.gca().xaxis.set_major_locator(mdates.DayLocator())
plt.gca().set_xticks(xpoints)
plt.plot(xpoints,ypoints)
plt.show()