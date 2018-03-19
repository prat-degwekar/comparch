#!/usr/bin/perl

open (INPUT,"<$ARGV[0]_freq.rl") or die "Can't open file $ARGV[0]_freq.rl";
open (OUT, ">$ARGV[0].data") or die "Can't open file $ARGV[0].data";

$rulesRow=0;
while(<INPUT>)
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

#my @rulesFile = sort {$b->[6] <=> $a->[6]} @rulesFile;


#$noOfMatchings = 0;
foreach $rulesRow (0..@rulesFile-1)
{
	
		print OUT "$rulesRow \t";
	#foreach $rulesColumn (0..@{$rulesFile[$rulesRow]}-1)
	#{
		#print "Element [$rulesRow][$rulesColumn] = $rulesFile[$rulesRow][$rulesColumn]\n";
		#print "$rulesFile[$rulesRow][6] \t";
		print OUT "$rulesFile[$rulesRow][6]";
		#print OUT " ";
	#}
		#$noOfMatchings = $noOfMatchings + $rulesFile[$rulesRow][6];
	print OUT "\n";
#	print "\n";
}

#print "Number of Rules are    : $rulesCount\n";
#print "Number of Matchings are: $noOfMatchings\n";
