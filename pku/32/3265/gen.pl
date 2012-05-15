#!/usr/bin/perl

$n = 10000;

print "$n\n";
for($i = 0; $i < $n-1; $i++) {
    $a = 100000-$n+$i+2;
    print "$a\n";
}
$a = 100000-$n+1;
print "$a\n";
