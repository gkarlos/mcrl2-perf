import sys, os
import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt
import pprint
from matplotlib import rcParams
rcParams.update({'figure.autolayout': True})

results_dir = sys.argv[1]

FLAGS=0
MIN=0
MAX=1
MEAN=2
SD=3

data = {}
memory={}

def print_data():
    pp = pprint.PrettyPrinter(depth=3, width=120)
    pp.pprint(data)

def read_data():
    for filename in os.listdir(results_dir):
        if filename.endswith('.memory.csv'):
            with open(results_dir + "/" + filename, "r") as f:
                memory[filename.split('.')[0]] = map(float, f.read().strip().splitlines())
            continue
        elif not filename.endswith('.summary.csv'):
            continue

        name = filename.split('.')[0]
        data[name] = {}

        with open(results_dir + "/" + filename, "r") as f:
            lines = f.readlines();
            flag = ''
            for i in range(1, len(lines)):
                line = lines[i].split(',')
                if len(line[0]) != 0:
                    flag = line[0]
                    data[name][flag] = {}
                data[name][flag][line[1]] = map(float, line[2:])
                f.close()



read_data()

objects = tuple(data.keys())
y_pos  = np.arange(len(objects))

flags = data[data.keys()[0]].keys()

x = -0.3
fig, ax = plt.subplots(1, 1)
error_config = {'ecolor': '0.3', 'fillstyle':'full', 'capsize':5}
for flag in flags:
    means = [ data[k][flag]['User+Sys'][MEAN] / 1000 for k in data.keys()]
    sd    = [ data[k][flag]['User+Sys'][SD] / 1000 for k in data.keys()]
    ax.bar(y_pos + x, means, width=0.3, align='center', label=flag, yerr=sd, error_kw=error_config)
    x = x + 0.3

ax2 = ax.twinx()
x = -0.3
for i in range(len(flags)):
    mem = [ memory[k][i] / 1000000 for k in memory.keys()]
    if i == 0:
        ax2.plot(y_pos + x, mem, '_',mew=2, ms=15, color='red', label="Memory")
    else:
        ax2.plot(y_pos + x, mem, '_',mew=2, ms=15, color='red')
    x = x + 0.3

plt.title('lps2lts / %s' % results_dir.split('/')[1])
ax.set_ylabel('Time, user+sys (sec)')
ax2.set_ylabel('Max Heap Usage (MB)')
ax.grid(zorder=1, linestyle='dotted')
plt.xticks(y_pos, objects)
ax2.set_axisbelow(True)
ax.set_axisbelow(True)

ax.legend(prop={'size': 8})
ax2.legend(prop={'size': 8})
plt.savefig(results_dir + "/%s" % results_dir.split('/')[1])
