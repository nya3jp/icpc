#!/usr/bin/perl

for($i = 2; $i <= 20; $i++) {
    for($j = 2; $j <= 20; $j++) {
        open(IN, ">king.in") or die;
        print IN "$i $j\n";
        close(IN);
        system("./a.out");
        (-e "king.out") or die;
        print "($i,$j): ";
        system("./king-verify");
    }
}

