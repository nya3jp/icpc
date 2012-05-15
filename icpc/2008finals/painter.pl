#!/usr/bin/perl

$cases = 100000;
$n = 4;
$w = 10;

while($cases-- > 0) {
    print "$n\n";
    for($i=0;$i<$n;$i++) {
        for(;;) {
            @z=();
	        for($j=0;$j<6;$j++) {
                push(@z,int(rand()*$w));
            }
            $ax=$z[2]-$z[0];
            $ay=$z[3]-$z[1];
            $bx=$z[4]-$z[0];
            $by=$z[5]-$z[1];
            $op=$ax*$by-$ay*$bx;
            if ($op == 0) {
                redo;
            }
	        for($j=0;$j<6;$j++) {
                print "$z[$j] ";
            }
            print "\n";
            last;
        }
    }
    print "\n";
}

print "-1\n";
