

awk 'NR==FNR{a[$1$2];next}($1$2) in a {print "toy1", $0}' data-raw/poolfreq.tsv outtoy/toy1.freq
