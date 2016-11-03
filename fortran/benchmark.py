#! /usr/bin/env python

import re
import subprocess

f = open('results.csv', 'w')

for i in range(1, 21):
    n = i * 100
    proc = subprocess.Popen(['./matmul', str(n)], stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    (output, err) = proc.communicate()
    time = re.search(r'\d+\.\d+', str(err), re.M|re.I).group()
    pair = str(n) + ', ' + str(time) + '\n'
    f.write(pair)
    print (pair[:-1])
