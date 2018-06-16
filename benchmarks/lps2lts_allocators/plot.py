import sys, os
import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt
import pprint
from matplotlib import rcParams
rcParams.update({'figure.autolayout': True})
rcParams.update({'figure.figsize': (10, 7)})

resultsdir = sys.argv[1]

CSV_FLAG=0
CSV_TIME=1
CSV_MIN=2
CSV_MAX=3
CSV_MEAN=4
CSV_SD=5
CSV_USER=0
CSV_SYS=1
CSV_USERSYS=2
T_MIN=0
T_MAX=1
T_MEAN=2
T_SD=3

ALLOCATOR=-3

allocators = ['default', 'jemalloc', 'tcmalloc']
flags      = ['-default', '-rjittyc', '-rjittyc --cached --prune']
tests      = [d.split('.')[0] for d in os.listdir(resultsdir)]

data = {}
size = resultsdir.split('-')[1]

def print_data():
    pp = pprint.PrettyPrinter(depth=5, width=120)
    pp.pprint(data)


for allocator in allocators:
    data[allocator] = {}

# read data
for testdir in os.listdir(resultsdir):
    testname = testdir.split('.')[0]
    for filename in os.listdir("%s/%s" % (resultsdir, testdir)):
        if filename.endswith("summary.csv"): # we only read the summaries
            allocator = filename.split('.')[0]
            filenameabs = "%s/%s/%s" % (resultsdir, testdir, filename)
            with open(filenameabs, "r") as f:
                data[allocator][testname] = {}
                flines = f.readlines()
                for i in range(1, len(flines), 3):
                    data[allocator][testname][flines[i].split(',')[CSV_FLAG]] = {
                        "usr" : map(float, flines[i].split(',')[CSV_MIN:]),
                        "sys" : map(float, flines[i + 1].split(',')[CSV_MIN:]),
                        "usr+sys": map(float, flines[i + 2].split(',')[CSV_MIN:])
                    }

#plot data
y_pos        = np.arange(len(tests))
barspertest  = len(allocators) * len(flags)
w = 0.11
flag_colors = { flags[0] : 'gray', flags[1] : 'green', flags[2] : 'orange' }

colors = {
  allocators[0] : {
    flags[0] : '#4c9900',
    flags[1] : '#66cc00',
    flags[2] : '#80FF00'
  },

  allocators[1] : {
    flags[0] : '#009999',
    flags[1] : '#00CCCC',
    flags[2] : '#00FFFF'
  },

  allocators[2] : {
    flags[0] : '#CCCC00',
    flags[1] : '#FFFF00',
    flags[2] : '#FFFF99'
  }
}
allocator_colors = { allocators[0] : [], allocators[1] : [], allocators[2] : []}
hatches= { flags[0] : '', flags[1] : 'x', flags[2] : 'o'}
offset = -( w * ( barspertest / 2))
error_config = {'ecolor': '0.1', 'fillstyle':'full', 'capsize':5}
fig, ax = plt.subplots(1, 1)

for allocator in allocators:
    for flag in flags:
        means = [ data[allocator][test][flag]['usr+sys'][T_MEAN] / 1000 for test in tests ]
        sds   = [ data[allocator][test][flag]['usr+sys'][T_SD]   / 1000 for test in tests ]
        ax.bar(y_pos + offset, means, width= w - (w / barspertest), align='edge', \
            color=colors[allocator][flag], label="%s || %s" % \
            ( "libc_malloc" if allocator == "default" else allocator, flag), yerr=sds, \
            error_kw=error_config, linewidth=0.2, edgecolor="black")

        offset = offset + w

# mat = np.random.random((10,10))
# plt.imshow(mat, origin="lower", interpolation='nearest')
# plt.colorbar()
plt.title('lps2lts / %s' % size)
ax.set_ylabel('Time, user+sys (sec)')
ax.grid(zorder=1, linestyle='dotted')
plt.xticks(y_pos, tuple(tests + tests + tests))
ax.set_axisbelow(True)
ax.legend(prop={'size': 8})
plt.savefig(resultsdir)

    #
    # flags = data[data.keys()[0]].keys()
    #
    # x = -0.3
    # fig, ax = plt.subplots(1, 1)
    #
    # for flag in flags:
    #     means = [ data[k][flag]['User+Sys'][MEAN] / 1000 for k in data.keys()]
    #     sd    = [ data[k][flag]['User+Sys'][SD] / 1000 for k in data.keys()]
    #
    #     x = x + 0.3
#

#
# ax2 = ax.twinx()
# x = -0.3
# for i in range(len(flags)):
#     mem = [ memory[k][i] / 1000000 for k in memory.keys()]
#     if i == 0:
#         ax2.plot(y_pos + x, mem, '_',mew=2, ms=15, color='red', label="Memory")
#     else:
#         ax2.plot(y_pos + x, mem, '_',mew=2, ms=15, color='red')
#     x = x + 0.3
#
