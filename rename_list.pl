#!/usr/bin/perl

use strict;
use warnings;
use File::Copy qw(move);
use Sort::Key::Natural qw( natsort );

my @options = qw!-l -h!;
my $filename = __FILE__;
$filename =~ s/\.\///;
my ($file,$pattern) = ("","");
our (@old_names, $fh, $row);

opendir(DIR,".");

if(@ARGV) {
	my @m = @ARGV;
	foreach(@ARGV) {
		if($_ eq '-p') {
			shift(@m);
			$pattern = shift(@m);
			@old_names = natsort grep(/\.$pattern/,readdir(DIR));
			foreach (@old_names) {
				print "$_\n";
			}
		}
		if($_ eq '-l') {
			shift(@m);
			$file=shift(@m);
			open($fh, '<:encoding(UTF-8)', $file)
				or die "Could not open list '$file' from options $!";		
			while($row = <$fh>){
				chomp $row;
				for(my $i; $i<$#{ @old_names };$i++){
					move $old_names[$i], $row;
				}
			}
		}
		if($_ eq '-h') {
			&usage();
		}
	}
}

closedir(DIR);

sub usage {
	print "<Usage>: " . $filename . " <Options> [-l|-h]\n
	\t Options:
	\t -l: \t The list for replacing
	\t -h: \t Show this page\n";
}
#foreach (@options) {
#	print "$_\n";
#} 
