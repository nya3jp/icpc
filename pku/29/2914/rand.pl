#!/usr/bin/perl

$n = $ARGV[0];
$m = $ARGV[1];

print "$n $m\n";
for($i = 0; $i < $m; $i++) {
    $a = int(rand()*$n);
    $b = int(rand()*$n);
    $c = int(rand()*1000);
    print "$a $b $c\n";
}
