#!/usr/bin/python3

import sys, os

l_output = ['overrun', 'underrun', 'uaf']
l_outdir = ['out', 'out-asan']
if 'CC' in os.environ:
    cc_bin = os.environ['CC']
else:
    cc_bin = 'gcc'

try:
    for od in l_outdir:
        os.mkdir(od)
except:
    pass

cmds = ['#!/bin/bash']
for o in l_output:
    cmds.append('{} -g -o {}/{} {}.c'.format(cc_bin, l_outdir[0], o, o))
    cmds.append('{} -fsanitize=address -g -o {}/{} {}.c'.format(cc_bin, l_outdir[1], o, o))
with open('tmp.sh', 'w') as f:
    f.write('\n'.join(cmds))

os.system('bash tmp.sh')
