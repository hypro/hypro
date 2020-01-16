#!/bin/bash
TIMEOUT=20m
INPUTFILE=$1

echo glpk_double.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_double $1 $rep
done

echo glpk_smtrat_double.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_smtrat_double $1 $rep
done

echo glpk_z3_double.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_z3_double $1 $rep
done

echo glpk_mpq.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_mpq $1 $rep
done

echo glpk_smtrat_mpq.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_smtrat_mpq $1 $rep
done

echo glpk_z3_mpq.
for((rep=1;rep<7;rep++))
do
	timeout $TIMEOUT ./hypro_glpk_z3_mpq $1 $rep
done
