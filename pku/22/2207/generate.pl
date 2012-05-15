#!/usr/bin/perl


print "1 2\n";
for($i = 3; $i <= 100; $i++) {
    printf("%d %d\n", $i-1, $i);
    printf("%d %d\n", $i-2, $i);
}

