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
fileUART = open("CruiseControlTest_1.txt", "r")
csvUARTlines = fileUART.readlines()

#Parsing the file: for every line, is the key is not saved create it, else save the new value in that key
for line in csvUARTlines:
    if len(line) > 3 and len(line) < 10:
        try:
            splittedString = line.lstrip().replace(",", "").replace("\n", "").split(' ')
            if splittedString[0] in dataDictionary:
                print splittedString
                dataDictionary[splittedString[0]].append(float(splittedString[1]))
            else:
                dataDictionary[splittedString[0]] = []
                dataDictionary[splittedString[0]].append(float(splittedString[1]))
            # print max(line)
        except:
            pass

#For every dictionary key (except TS) find maximum and minimum value, to size the plot

#Close plots
plt.close('all')

#For every dictionary key, create a plot
index = 1
for key in dataDictionary:
    plt.figure(index)
    fig, ax = plt.subplots()
    plt.plot(np.linspace(0, len(dataDictionary[key]), len(dataDictionary[key])), dataDictionary[key], label=key, marker='o')
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
    plt.xlabel("sampleNumber")
    plt.ylabel(key + "(A)")
    index = index + 1
    #print key

plt.show()