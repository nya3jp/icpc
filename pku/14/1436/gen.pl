#!/usr/bin/perl

$n = 8000;

print "1\n$n\n";

print "0 8000 1\n";
for($i = 2; $i <= $n; $i++) {
    print "0 $i $i\n";
}
