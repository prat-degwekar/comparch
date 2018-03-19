#!/usr/bin/perl

open (RULEIN,"<$ARGV[0]_final.rl") or die "Can't open file $ARGV[0]_final.rl";
open (INPUT,"<$ARGV[1].trace") or die "Can't open file $ARGV[1].trace";

open (OUT, ">$ARGV[0]_freq.rl") or die "Can't open file $ARGV[0]_freq.rl";
open (OUT1, ">$ARGV[0]_trace1") or die "Can't open file $ARGV[0]_trace1";

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
#print "Read the Rule Successfully\n";

#foreach $rulesRow (0..@rulesFile-1)
#{
#	foreach $rulesColumn (0..@{$rulesFile[$rulesRow]}-1)
#	{
#		print "Element [$rulesRow][$rulesColumn] = $rulesFile[$rulesRow][$rulesColumn]\n";
		#print OUT "$rulesFile[$rulesRow][$rulesColumn]";
		#print OUT " ";
#	}
#	print OUT "\n";
#	print "\n";
#}

@ins =0;

#while(<INPUT>)
#{	
#	$ins = $ins + 1;
#}

#print "$ins \n";

$successCount= 0;
while(<INPUT>)
{
	chomp;
	@inputLines = split /\ /;
	#print "@inputLines \t";
	$sInPkt = dec2bin($inputLines[0]);
	#print "$sInPkt\t";
	$dInPkt = dec2bin($inputLines[1]);
	#print "$dInPkt\t";
	$sPort = $inputLines[2];
	#print "$sPort \t";
	$dPort = $inputLines[4];
	#print "$dPort \n";
#	print "Read the All the Traces\n";

	$rulesRow=0;
	foreach $rulesRow (0..@rulesFile-1)
	{
		
		$sLenth = length($rulesFile[$rulesRow][0]);
		#print "$sLenth \t";
		$sIp = substr($sInPkt, 0, $sLenth);		
		#print "$sIp \t";
		#print "$rulesFile[$rulesRow][0] \t";
		
	#	print "Comparing Each Rule with Incoming Trace\n";


		if ($sIp eq $rulesFile[$rulesRow][0])
		{

		#	print "I am in Comparison LOOP\n";

			$dLenth = length($rulesFile[$rulesRow][1]);
		#	print "$dLenth \t";
			$dIp = substr($dInPkt, 0, $dLenth);		
		#	print "$dIp \t";
		#	print "$rulesFile[$rulesRow][1] \t";	
		
			if($dIp eq $rulesFile[$rulesRow][1])
			{
				if($sPort ge $rulesFile[$rulesRow][2])
				{
					if($sPort le $rulesFile[$rulesRow][3])
					{
						if($dPort ge $rulesFile[$rulesRow][4])
						{
							if($dPort le $rulesFile[$rulesRow][5])
							{
								$rulesFile[$rulesRow][6] = $rulesFile[$rulesRow][6] + 1;
								$successCount = $successCount + 1;
								print "SUCCESS: All Fileds are  Matching: $successCount \n ";
								last;
								#print OUT1 "@inputLines";
								#print OUT1 " ";
								#print OUT1 "1\n";

								#$inCount = $inCount + 1;
							}
						}
					}
				}
			}
		}
	#	print "\n";

		#print OUT1 "@inputLines";
		#print OUT1 " ";
		#print OUT1 "0\n";
	}
	
}

foreach $rulesRow (0..@rulesFile-1)
{
	foreach $rulesColumn (0..@{$rulesFile[$rulesRow]}-1)
	{
		#print "Element [$rulesRow][$rulesColumn] = $rulesFile[$rulesRow][$rulesColumn]\n";
		print OUT "$rulesFile[$rulesRow][$rulesColumn]";
		print OUT " ";
	}
	print OUT "\n";
#	print "\n";
}
