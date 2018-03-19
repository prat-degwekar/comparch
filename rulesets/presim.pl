#!/usr/bin/perl
#
# USAGE: perl presim.pl rule_fileName_WithoutExtension
# this will dump ruleFilename_final.rl
#
open (INPUT,"<$ARGV[0].rl") or die "Can't open file $ARGV[0].rl";
open (OUT, ">$ARGV[0]_bin.rl") or die "Can't open file $ARGV[0]_bin.rl";

sub dec2bin {
    my $str = unpack("B32", pack("N", shift));
	$str = reverse($str);
	chop($str); 	chop($str);	chop($str);	chop($str);	chop($str);	chop($str);
	chop($str); 	chop($str);	chop($str);	chop($str);	chop($str);	chop($str);
	chop($str); 	chop($str);	chop($str);	chop($str);	chop($str);	chop($str);
	chop($str); 	chop($str);	chop($str);	chop($str);	chop($str);	chop($str);
	$str = reverse($str);
    #$str =~ s/^0+(?=\d)//;   # otherwise you'll get leading zeros
    return $str;
}

sub bin2dec {
    return unpack("N", pack("B32", substr("0" x 32 . shift, -32)));
}


$rulesRow=0;
while(<INPUT>)
{
	chomp;
	@rulesLines = split /\ /;
	#print "$rulesLines[0] \n";

	# Source IP processing
	$sstr = reverse "$rulesLines[0]";
	chop($sstr);
	#print $str;
	$rulesLines[0] = reverse "$sstr";	
	#print "$rulesLines[0] \t";
	@srcVal = split(/\//, $rulesLines[0]);
	@srcIp = split(/\./, $srcVal[0]);	
	#print "@srcIp \t";
	$sip1=dec2bin($srcIp[0]);
	#print "$ip1 \t";
	$sip2=dec2bin($srcIp[1]);
	#print "$ip2 \t";
	$sip3=dec2bin($srcIp[2]);
	#print "$ip3 \t";
	$sip4=dec2bin($srcIp[3]);
	#print "$ip4 \n";
	my $srcPktIp = "$sip1$sip2$sip3$sip4";
	#print "$srcPktIp \t";
	#print "$srcVal[1] \t";
	if($srcVal[1] eq '0')
	{
		#print "Yes 0\n";
		$srcVal[1] = 1;
	}

	$sIp = substr($srcPktIp, 0, $srcVal[1]);
	print OUT $sIp;
	print OUT " ";
	
	$prefixLength =0;
	
	# Destination IP Processing
	#print "$rulesLines[1] \t";
	@dstVal = split(/\//, $rulesLines[1]);
	#print "@dstVal \t";
	@dstIp = split(/\./, $dstVal[0]);
	#print "@dstIp \t";	
	$dip1=dec2bin($dstIp[0]);
	#print "$ip1 \t";
	$dip2=dec2bin($dstIp[1]);
	#print "$ip2 \t";
	$dip3=dec2bin($dstIp[2]);
	#print "$ip3 \t";
	$dip4=dec2bin($dstIp[3]);
	#print "$ip4 \t";
	my $dstPktIp = "$dip1$dip2$dip3$dip4";
	#print "$dstPktIp \t";
	#print "$dstVal[1] \t";

	if($dstVal[1] eq '0')
	{
		#print "Yes 0\n";
		$dstVal[1] = 1;
	}

	$prefixLength = $srcVal[1] + $dstVal[1];
	#print "$prefixLength \n";	

	$dIp = substr($dstPktIp, 0, $dstVal[1]);
	#print "$dIp\n";
	print OUT $dIp;
	print OUT " ";

	$iportL = $rulesLines[2];
	print OUT $iportL;
	print OUT " ";
	$iportU = $rulesLines[4];
		print OUT $iportU;
		print OUT " ";
	
	$oportL = $rulesLines[5];
	print OUT $oportL;
	print OUT " ";
	$oportU = $rulesLines[7];
		print OUT $oportU;
		print OUT " ";
		print OUT "0";
		print OUT " ";
		print OUT $prefixLength;
		print OUT "\n";
}
#print "Read the Rule Successfully\n";

