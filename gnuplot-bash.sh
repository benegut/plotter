#!/usr/bin/gnuplot -persist
plot "raw_data_col_0,1.csv" every ::0::80000 using 0:1 with lines

