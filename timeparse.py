#
# Parses the output of "time" command and
# spits out user,sys time in missliseconds
#
import sys

REAL = 0
USER = 1
SYS  = 2

times = sys.stdin.read().splitlines()[1:4]
times = [ t.split()[1][:-1] for t in times]
times = [ (int(t.split("m")[0]) * 60000 + float(t.split("m")[1]) * 1000) for t in times]
print "%.2f,%.2f" % (times[USER], times[SYS])
