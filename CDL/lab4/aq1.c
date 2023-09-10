/* aq1=same as q1 just need to add strcut in keywords[]
Write a getNextToken ( ) to generate tokens for the perl script given below.
#! /usr/bin/perl
#get total number of arguments passed.
$n = scalar (@_);
$sum = 0;
foreach $item(@_) {
$sum += $item;
}
$average = $sum + $n;
#! Represents path which has to be ignored by getNextToken().
# followed by any character other than ! represents comments.
$n followed by any identifier should be treated as a single token.
Scalar, foeach are considered as keywords.
@_, += are treated as single tokens.
Remaining symbols are tokenized accordingly.*/

