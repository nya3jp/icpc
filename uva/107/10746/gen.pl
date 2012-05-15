$n = 10;
print "$n $n\n";
for($i = 0; $i < $n; $i++) {
    for($j = 0; $j < $n; $j++) {
        $x = rand();
        print "$x ";
    }
    print "\n";
}
print "0 0\n";
