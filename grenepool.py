#!/usr/bin/env python3

'''
Master script to parse, QC clean, and map reads from high throughput sequencing
@author: Moises Exposito-Alonso (moisesexpositoalonso@gmail.com)

'''

##########################################################################################
### Set up
##########################################################################################
import time, datetime, os, sys, pandas,argparse
import numpy as np
# from subprocess import *
import subprocess

##########################################################################################
### Read arguments
##########################################################################################

import argparse
parser = argparse.ArgumentParser(description='grenepool: pipeline to clean and map fastq files')
parser.add_argument("input", help="full path to input fast.gz file -- only the path to forward (R1) read is needed",
                    type=str)
parser.add_argument("--out", help="outpuf folder",
                    type=str,default='out')
parser.add_argument("--clean", help="want to clean large intermediate files?",
                    type=str,default='True',choices=['False','True'])
parser.add_argument("--step", help="want to start in a different step?\n 0 will recognize the file names \n 1 for QC with skewer \n 2 for mapping with bwa mem \n 3 for making sorting and indexing bam file.",
                    type=str,default='-9'	)
parser.add_argument("--force", help="will force start analysis from beginning and will overwrite files",
                    type=str,default='False',choices=['False','True'])
parser.add_argument("--ref", help="reference genome to map to",
                    type=str,default='ref/TAIR10_chr_all.fas')
args = parser.parse_args()

print ('\n......................................................................................\n')
print ('grenepool: pipeline to clean and map fastq files:')
print ('interpreted arguments:')
print ('   input file:',args.input)
print ('   output folder:',args.out)
print ('   clean intermediatefiles:',args.clean)
print ('   step to start analysis:',args.step)
print ('   force start from beginnin:',args.force)
print ('   reference genome file:',args.ref)
print ('\n......................................................................................\n')


##########################################################################################
# Functions
##########################################################################################
## file names

samplename=os.path.basename(args.input)
outsample="".join((args.out,"/",samplename))

read1=args.input
read2=read1.replace('R1', 'R2')
trimmed1="".join((args.out,'/',samplename,'-trimmed-pair1.fastq'))
trimmed2="".join((args.out,'/',samplename,'-trimmed-pair2.fastq'))
samfile="".join((args.out,'/',samplename,'.sam'))
bamfile="".join((args.out,'/',samplename,'.bam'))
bamsortfile="".join((args.out,'/',samplename,'.bam.sorted.bam'))
freqfile="".join((args.out,'/',samplename,'.freq'))

ref=args.ref


def figurestage(args,read1,read2,trimmed1,trimmed2, samfile,bamfile,bamsortfile,freqfile):
    read1bool=os.path.exists(read1)
    read2bool=os.path.exists(read2)
    trim1bool= os.path.exists(trimmed1)
    trim2bool= os.path.exists(trimmed2)
    sambool= os.path.exists(samfile)
    bambool= os.path.exists(bamfile)
    bamsortbool= os.path.exists(bamsortfile)
    freqfile= os.path.exists(freqfile)

    start=0
    if bambool & bamsortbool:
        print('Starting after aligning')
        start=3
    elif sambool:
        print('Starting after mapping')
        start=2
    elif trim1bool & trim2bool:
        print('Starting after QC')
        start=1
    elif read1bool & read2bool:
        print('Starting pipeline')
    else:
        raise Exception("fastq.gz files not found!")
    # exceptions
    if args.step != "-9":
        print('step to start provided')
        start=args.step
    elif args.force=='True':
        print('force pipeline from beginning')
        start=0
    return(start)

def qc(read1,read2,outsample):
    print ('\n......................................................................................\n')
    print("clean: trimming & quality filter... \n")

    cmd='skewer -m pe -t 10 %s %s -o %s' %(read1,read2,outsample)
    try:
        print('running -> %s' %(cmd))
        p=subprocess.run(cmd,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with skewer program call -- manually check!")
    print("...done")
    return p.returncode

def map2reference(ref,trimmed1,trimmed2,samfile):
    print ('\n......................................................................................\n')
    print("map to reference (sam file)...\n")
    cmd= 'bwa mem -t 10  %s %s %s > %s' %(ref,trimmed1,trimmed2,samfile)
    try:
        print('running -> %s' %(cmd))
        p=subprocess.run(cmd,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with bwa mem program call -- manually check!")
    print("...done")
    return p.returncode

def alignindex(samfile,bamfile):
    print ('\n......................................................................................\n')
    print("aligning...\n")
    cmd1='samtools view -S -b  %s >  %s' % (samfile,bamfile)
    cmd2='samtools sort  %s > %s".sorted.bam"'% (bamfile,bamfile)
    cmd3='samtools index %s".sorted.bam"'% (bamfile)
    try:
        print('running -> %s' %(cmd1))
        p1=subprocess.run(cmd1,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with samtools view program call -- manually check!")
    try:
        print('running -> %s' %(cmd2))
        p2=subprocess.run(cmd2,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with samtools sort call -- manually check!")
    try:
        print('running -> %s' %(cmd3))
        p3=subprocess.run(cmd3,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with samtools index call -- manually check!")
    print("...done")
    return p3.returncode

def bamfreq(bamfile,freqfile):
    print ('\n......................................................................................\n')
    print("Counting bases in .bam file... \n")

    #cmd='freq -h -f 0.02 -c 100 %s.sorted.bam > %s' %(bamfile,freqfile)
    cmd='freq -h -f 0.02 -c 20 %s.sorted.bam > %s' %(bamfile,freqfile)
    try:
        print('running -> %s' %(cmd))
        p=subprocess.run(cmd,shell=True)
    except subprocess.CalledProcessError as suberror:
        raise ("Problem with custom freq tool -- manually check!")
    print("...done")
    return p.returncode

def cleanintermediate(args,trimmed1,trimmed2,sam,bam):
    if args.clean :
        print('Cleaning intermediate files ...')
        cm1='rm %s'% (trimmed1)
        cm2='rm %s'% (trimmed2)
        cm3='rm %s'% (sam)
        cm4='rm %s'% (bam)
        print(cm1)
        print(cm2)
        print(cm3)
        # print(cm4)
        subprocess.call(cm1,shell=True)
        subprocess.call(cm2,shell=True)
        subprocess.call(cm3, shell=True)
        # subprocess.call(cm4, shell=True)

success=['NotApply','NotApply','NotApply','NotApply'] # to keep track of successes
def runstep (args,start,read1,read2,outsample,ref,trimmed1,trimmed2,samfile,bamfile,freqfile):
    if start == 0:
        success[start]= qc(read1,read2,outsample)
    elif start == 1:
        success[start]= map2reference(ref,trimmed1,trimmed2,samfile)
    elif start == 2:
        success[start]= alignindex(samfile,bamfile)
    elif start == 3:
        success[start]= bamfreq(bamfile,freqfile)
    else:
        pass
    return 0

##########################################################################################
# define stage to start analysis
start=figurestage(args,read1,read2,trimmed1,trimmed2, samfile,bamfile,bamsortfile,freqfile)
start=int(start)
print("Starting position %s" % start)

# run the different stages
while start < 4:
    runstep(args,start,read1,read2,outsample,ref,trimmed1,trimmed2,samfile,bamfile,freqfile)
    start=start+1

# clean intermediatefiles if successes
cleanintermediate(args,trimmed1,trimmed2,samfile,bamfile)


# print (success)
print ('\n......................................................................................\n')
print ('Summary of pipeline:\n')
print('Trimming and quality filter - exit code = %s' %success[0])
print('Mapping to reference - exit code = %s' %success[0])
print('Aligning and indexing - exit code = %s' %success[0])
print('Counting bases - exit code = %s' %success[0])
print ('END')
print ('\n......................................................................................\n')
