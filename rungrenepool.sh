#!/bin/bash

# example
# bash grenepool "francoisfield_S1_L005_R1_001.fastq.gz" ../data out

# all
#qsub ./clustergrenepool.sh ../data/DNAfromseeds8.R1.RUN0102.L3.fastq.gz

# all in burrito
# while read p; do
#   nice -n 19 ./grenepool $p out > out/$(basename $p)".log" &
# done <samples.tsv

# all in burrito with counter
counter=0
for p in $(cat samples.tsv);
do
  echo "Job counter is $counter"
  remainder=$(( counter % 5 ))
  if [ "$remainder" -eq 0 ]; then
    echo 'continue to next process ...'
    nice -n 19 ./grenepool $p out > out/$(basename $p)".log" &
  else
    echo 'wait for some processes to finish ...'
    nice -n 19 ./grenepool $p out > out/$(basename $p)".log"
    wait
  fi
  counter=$((counter+1))
done
