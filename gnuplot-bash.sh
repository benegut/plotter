#!/usr/bin/gnuplot -persist
plot "data.csv" every ::0::80000 using 1:2 with lines

