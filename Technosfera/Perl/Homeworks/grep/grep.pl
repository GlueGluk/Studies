#!/usr/bin/env perl
use Getopt::Long qw(:config no_ignore_case);
use strict;
use v5.16;

my $A; #+
my $B; #+
my $C; #+
my $c; #+
my $i; #+
my $v; #+
my $F; #+
my $n; #+ 

GetOptions('A=s' => \$A, 'B=s' => \$B, 'C=s' => \$C, 'c' => \$c, 'i' => \$i, 'v' => \$v, 'F' => \$F, 'n' => \$n);
my @strings = <STDIN>;
my $pattern = $ARGV[$#ARGV];
my @matching;
my @output;
for my $k (0..$#strings) {
    if($F) {
        if ($i) {
            if ((index(fc($strings[$i]), fc($pattern)) >= 0) xor ($v)) {
                $matching[$k] = $strings[$k];
            }
        }
        else {
            if ((index(fc($strings[$i]), fc($pattern)) >= 0) xor ($v)) {
                $matching[$k] = $strings[$k];
            }
        }
    }
    else {
        if ($i) {
            if (($strings[$k] =~ /$pattern/i) xor ($v)) {
                $matching[$k] = $strings[$k];
            }
        }
        else {
             if (($strings[$k] =~ $pattern) xor ($v)) {
                $matching[$k] = $strings[$k];
            }
        }
    }
}
if (not $c) {
    for my $i (0..$#strings) {
        if($matching[$i] and ($A or $C)) {
            my $lngt = ($A ? ($C ? ($A>$C ? $A : $C) : $A) : $C);
            my $lim = ($lngt > ($#strings - $i) ? $#strings : $i+$lngt);
            for my $j ($i .. $lim) {
                $output[$j] = $strings[$j];
            }
        }
        if($matching[$i] and ($B or $C)) {
            my $lngt = ($B ? ($C ? ($B>$C ? $B : $C) : $B) : $C);
            my $lim = ($lngt > ($i-1) ? 0 : $i-$lngt);
            for my $j ($lim .. $i) {
                $output[$j] = $strings[$j];
            }
        }
    }
}
my $count = 0;
for my $i (0 .. $#strings) {
    if ($output[$i]){
        if ($c) {
            $count += 1;
        }
        else{
            if ($n) {
                print (($i+1).":");
            }
            print $output[$i];
        }
    }
}
if ($c) {
    print $c."\n";
}
