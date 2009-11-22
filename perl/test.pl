#!/usr/bin/perl

use strict;
use warnings;

use FindBin;
use lib $FindBin::RealBin;

use RandomVariable;

my $g0 = RandomVariable->newFromGaussian(2.0, 3.0);
my $g1 = RandomVariable->newFromGaussian(5.0, 4.0);
my $g2 = $g0 + $g1;
print $g2->get_id(), ".\n";
