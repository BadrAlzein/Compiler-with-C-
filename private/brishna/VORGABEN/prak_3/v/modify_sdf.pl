#!/usr/bin/perl
########################################################################################
# !@file        : modify_sdf.pl
# !@brief       : this script will dublicate some delay information
# ! this is required to read the sdf file in modelsim
#
# !@author      : Tobias Koal (TK)
#  last modification by tkoal(TK)# 
#  Wed Feb  9 12:46:50 CET 2011 
########################################################################################
use strict;             ## use strict style only

use vars qw/ %opt /;
use Getopt::Std;
my $opt_string = 'hdf:';
## get arguments or print help if wrong arguments were set
getopts( "$opt_string", \%opt ) or help();
## print help if -h 
help() if $opt{h};
help() if !$opt{f};

########################################################################################
## GLOBALS                                                                            ##
########################################################################################
# set DEBUG to specified command line argument
my $DEBUG = $opt{d};


########################################################################################
## SUBS                                                                               ##
########################################################################################

########################################################################################
## MAIN                                                                               ##
########################################################################################
open(SDF_FILE,$opt{f}) or error("cannot open file $opt{f}");

my $new_sdf_file = "";
while(<SDF_FILE>) {
	$_ =~s/::([-]*[0-9]\.[0-9][0-9][0-9])/$1:$1:$1/ig;
	$new_sdf_file.=$_;
}

close SDF_FILE;

print $new_sdf_file;

########################################################################################
## ESSENTIAL SUBS                                                                     ##
########################################################################################

## sub trims a string at begin and end
sub trim($) {
	my $exp = $_[0];
	$exp =~s/^\s+//i;
	$exp =~s/\s+$//i;
	return $exp;
}

## sub prints debug messages if command line argument -d was set
sub debug ($) {
	my $message = $_[0];
	if ($DEBUG == 1) {
		print STDERR "\nDEBUG_MESSAGE : $message \n";
	}
}

## sub terminates script and print error message
sub error ($) {
	my $error = $_[0];
	print STDERR "\n\nERROR : $error !\n\n";
	die "";
}

## prints help and usage for script
sub help() {

print STDERR << "EOF";

This program duplicates some delay information in a given SDF file!

usage: $0 [-h] -f sdf_file

	-h        : this (help) message
	-f file   : file containing usersnames, one per line

        example: $0 -f sdf_file

EOF
exit;

}


