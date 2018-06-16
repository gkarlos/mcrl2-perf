import sys
import os
import math

#
def mean(l):
    return sum(l) / len(l)

def sd(l):
    m = mean(l)
    var = sum([(e - m) ** 2 for e in l]) / len(l)
    return math.sqrt(var)

if len(sys.argv) != 3:
    print "Usage:"
    print "  python summary.py <input_csv> <output_csv>"

try:
    data = open(sys.argv[1], "r")
except:
    print "Error reading data from %s" % sys.argv[1]
    sys.exit(0)

FLAGS=0
TIMES=2
USER=0
SYS=1
with open( "%s/%s" % ( os.getcwd(), sys.argv[2]), "w+") as csv_out:
    csv_out.write("Flags, #, Min, Max, Mean, Sd\n")

    for d in [dat.strip() for dat in data.read().strip().split("=")]:
        if len(d) == 0:
            continue
        d     = d.splitlines()
        flags = d[FLAGS]
        times = d[TIMES:]

        try:
            usertimes  = map(float, [t.split(",")[USER].strip() for t in times])
            systimes   = map(float, [t.split(",")[SYS].strip() for t in times])
            totaltimes = map(float, [ u + s for u, s in zip(usertimes, systimes)])
        except:
            print "Malformed Data"
            sys.exit(0)

        csv_out.write("%s,User,%f,%f,%f,%f\n" % ( flags, \
            min(usertimes), max(usertimes), mean(usertimes), sd(usertimes)) )
        csv_out.write(",Sys,%f,%f,%f,%f\n" %
            ( min(systimes), max(systimes), mean(systimes), sd(usertimes)) )
        csv_out.write(",User+Sys,%f,%f,%f,%f\n" %
            ( min(totaltimes), max(totaltimes), mean(totaltimes), sd(totaltimes)) )
