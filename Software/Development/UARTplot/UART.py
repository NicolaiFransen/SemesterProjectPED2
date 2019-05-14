'''
UART plot

This script plots the .txt file specified in line 27.

fileUART = open("abc2dqTestingSerialCom6.txt", "r")

The file opens the file structured as follows:

TS 536,
PhaseA 39,
PhaseB 13,
PhaseC 98,
D 0,

And creates an array with all the values for every different tag (TS, PhaseA,...)
Finally plots all the points for a different tag in a single window.

'''

import pip

def install(package):
    if hasattr(pip, 'main'):
        pip.main(['install', package])
    else:
        pip._internal.main(['install', package])

try:
    from matplotlib import pyplot as plt
except:
    install('matplotlib')
try:
    import numpy as np
except:
    install('numpy')

dataDictionary = {}

#opening the file
fileUART = open("vdRef_startupTest3.txt", "r")
csvUARTlines = fileUART.readlines()

#Parsing the file: for every line, is the key is not saved create it, else save the new value in that key
for line in csvUARTlines:
    splittedString = line.replace(",", "").replace("\n", "").split(' ')
    if splittedString[0] in dataDictionary:
        dataDictionary[splittedString[0]].append(float(splittedString[1]))
    else:
        dataDictionary[splittedString[0]] = []
        dataDictionary[splittedString[0]].append(float(splittedString[1]))
    #print max(line)

#For every dictionary key (except TS) find maximum and minimum value, to size the plot

#Close plots
plt.close('all')

#For every dictionary key, create a plot
index = 1
for key in dataDictionary:
    plt.figure(index)
    fig, ax = plt.subplots()
    plt.plot(dataDictionary["TS"], dataDictionary[key], label=key)
    plt.legend()
    start, end = ax.get_xlim()
    starty = min(dataDictionary[key])
    endy = max(dataDictionary[key])
    xAxisList = np.arange(start, end, (end - start)*0.1)
    ax.xaxis.set_ticks(sorted(xAxisList))
    try:
        ax.yaxis.set_ticks((sorted(np.arange(starty, endy, (endy - starty)*0.1))))
    except:
        ax.yaxis.set_ticks([-1, 0, 1])
    plt.xlabel("timestamp")
    plt.ylabel(key)
    index = index + 1
    #print key

plt.show()
