# GrENE-net pool seq pipeline

This repository contains the code necessary to run the genome-wide allele 
frequency estimation from the data produced by grene-net.org consortium.

### Pipeline steps

| SOFTWARE | TASK |
| --- | --- |
| skewer | Trimming & quality filter |
| fastqc | Visualize quality measurements |
| Bwa mem | Mapping to reference |
| Samtools | Alignment |
| IGV |  Visualize alignment |
| bamfreq | Extract base counts per position  |
| pool | Read two or more base count files and generate a fvcf |

All steps up until pool are wrapped in the script grenepool.py which is 
awared of output files and, if the run failed, would start from
the last keystone intermediate file unless forced.

### Get the code
```bash
git clone https://github.com/MoisesExpositoAlonso/grenepool
cd grenepool
make

# to prompt help from the two main programs
./grenepool
./pool

```

### To run analyses

```bash
./grenepool.py <yourfile.fastq.gz> 
./pool <outputname> <file1.freq> <file2.freq> ...

```


#### TO DO!
Probabilistic model to get frequency and estimate changes in time. Two 
previous softares  options might be CLEAR or PoPoolation.

