#!/bin/sh
#prefix=`seq $1`
list=`ls ./data/$1*`
gpfile="gp.movie"
echo "set zrange [0:1.5]" > $gpfile
for i in $list
do
#  echo "Step $i"
  echo "splot \"$i\"" >> $gpfile
  echo "pause 1"             >> $gpfile
done

gnuplot $gpfile
