# GrENE-net pool seq pipeline

This repository contains the code necessary to run the genome-wide allele 
frequency estimation from the data produced by grene-net.org consortium

### Pipeline steps

| software | task |
| --- | --- |
| skewer | Trimming & quality filter |
| fastqc | Visualize quality |
| Bwa mem | Mappint to reference |
| Samtools | Alignment |
| IGV |  Visualize alignment |
| --- from here one probably customized --- |
| GATK |  SNP calling |
| Bedtools |  Get coverage |


### TODOS
Dedicated software to build reproducible pipelines

http://slowkow.com/notes/snakemake-tutorial/
http://snakemake.bitbucket.org/snakemake-tutorial.html

