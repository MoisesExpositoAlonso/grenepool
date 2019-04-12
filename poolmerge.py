#!/usr/bin/env python3

'''
Script to merge multiple frequency files
@author: Moises Exposito-Alonso (moisesexpositoalonso@gmail.com)

'''

import os, sys, pandas,argparse

# Get all frequency files in the directory
# folder='../grenezero/outtoy'
folder='../grenezero/out'


ff=[]
for file in os.listdir(folder):
    if file.endswith(".freq"):
        ff.append(os.path.join(folder, file))
print(ff)

# Read and merge them
file0=ff[0]
ffr0=open(file0,'r')
ffrt0=pandas.read_table(ffr0,header=0)[['Seq','Pos']]

del ff[0]
for file in ff:
    ffr=open(file,'r')
    ffrt=pandas.read_table(ffr,header=0	)[['Seq','Pos']]
    ffrt0 = pandas.merge(ffrt0, ffrt)

print(ffrt0)
ffrt0.to_csv("../grenezero/data-raw/poolfreq.tsv",sep="\t",index=False)

for row in ffrt0:


awk 'NR==FNR{a[$1$2];next}($1$2) in a {print "toy1", $0}' data-raw/poolfreq.tsv outtoy/toy1.freq
