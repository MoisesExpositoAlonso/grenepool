# GrENE-net pool seq pipeline

This repository contains the code necessary to run the genome-wide allele 
frequency estimation from the data produced by grene-net.org consortium.

### Pilot experiment

Particularly, Illumina HiSeq data from pooled samples of Arabidopsis thaliana 
collected in 2016 in three experimental plots at MPI-Tuebingen.

In total there are 451 accessions that have been sown in 2014. The progeny (2nd generation) has been harvested in 2016 (pools of flower heads of ca 50-200 individuals from each plot). 
Description of the samples with IDs is available in Table_IDseq.

We start with a series of fastq files that we want to proceed for mapping to the reference, filtering bad quality, SNP calling and SNP filtering.

### Pipeline steps

| SOFTWARE | TASK |
| --- | --- |
| skewer | Trimming & quality filter |
| fastqc | Visualize quality measurements |
| Bwa mem | Mapping to reference |
| Samtools | Alignment |
| IGV |  Visualize alignment |
| bamfreq | Extract base counts per position  |

Probabilistic model to get frequency and estimate changes in time. The options might be CLEAR or PoPoolation.


### TO DO!
Dedicated software to build reproducible pipelines

http://slowkow.com/notes/snakemake-tutorial/
http://snakemake.bitbucket.org/snakemake-tutorial.html

### Get the code
git clone https://github.com/MoisesExpositoAlonso/grenepool

