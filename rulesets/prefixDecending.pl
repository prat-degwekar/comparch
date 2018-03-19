#!/usr/bin/perl

open (RULEIN,"<$ARGV[0]_bin.rl") or die "Can't open file $ARGV[0]_bin.rl";

open (OUT, ">$ARGV[0]_final.rl") or die "Can't open file $ARGV[0]_final.rl";

sub dec2bin {
    my $str = unpack("B32", pack("N", shift));
    #$str =~ s/^0+(?=\d)//;   # otherwise you'll get leading zeros
    return $str;
}

sub bin2dec {
    return unpack("N", pack("B32", substr("0" x 32 . shift, -32)));
}

$rulesRow=0;
while(<RULEIN>)
{
	chomp;
	@rulesLines = split /\ /;
	#print "@rulesLines \n";
	foreach $rulesColumn (@rulesLines)
	{
		push @{$rulesFile[$rulesRow]}, $rulesColumn;
	}
	$rulesRow++;
}


$rulesCount = $rulesRow;

my @rulesFile = sort {$b->[7] <=> $a->[7]} @rulesFile;


$noOfMatchings = 0;
foreach $rulesRow (0..@rulesFile-1)
{
	foreach $rulesColumn (0..@{$rulesFile[$rulesRow]}-2)
	{
		#print "Element [$rulesRow][$rulesColumn] = $rulesFile[$rulesRow][$rulesColumn]\n";
		#print "$rulesFile[$rulesRow][6] \t";
		print OUT "$rulesFile[$rulesRow][$rulesColumn]";
		print OUT " ";
	}
		$noOfMatchings = $noOfMatchings + $rulesFile[$rulesRow][6];
	print OUT "\n";
#	print "\n";
}

