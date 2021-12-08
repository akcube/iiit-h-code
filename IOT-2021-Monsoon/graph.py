# Uncomment the "y.append" line in each for loop, and comment the other when the circuit is up and running
# Node_ 1 => Motion detection
# Node_ 2 => Trap Activation detection
# Node_ 3 => Ultrasonic distance detection 
from datetime import datetime
import matplotlib.pyplot as plt
import json
import requests
import numpy as np
  
y = []

ae = "Rat_trap"
cnt1 = "Node_1"  
cnt2 = "Node_2"
cnt3 = "Node_3"
 
headers = {
    'X-M2M-Origin': 'admin:admin',
    'Content-type': 'application/json'
}

# Motion Data
uri = f"http://127.0.0.1:8080/~/in-cse/in-name/{ae}/{cnt1}/?rcn=4"
response = requests.get(uri, headers=headers);
retVal = json.loads(response.text)

for item in retVal['m2m:cnt']['m2m:cin']:
    plot_time = datetime.strptime(item['ct'], '%Y%m%dT%H%M%S')
    hour = (int(datetime.strftime(plot_time, '%H')))
    y.append(hour)

numbers=[x for x in range(0,24)]
labels=map(lambda x: str(x), numbers)
plt.xticks(numbers, labels)
plt.xlim(0,24)
plt.hist(y)
plt.show()
