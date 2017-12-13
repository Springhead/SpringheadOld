#!/usr/bin/perl
BEGIN { push(@INC, 'bin'); }
# ==============================================================================
#  File:
#	order.pl
#
#  Description:
#	Visual Studio 10.0 (devenv) ���o�͂������O��, ���W���[���P�ʂ���
#	�X���b�h���ɕ��ג���.
#
#  Version:
#	Ver 1.0  2013/02/06 F.Kanehori	Windows �ڐA���� (�S�ʉ���)
# ==============================================================================
use strict;
use warnings;
use Getopt::Long;
use base_lib;
use dailybuild_lib;

# �ϐ�
#
my $script = leafname($0);
my $logfile = "-";		# input file
my $outfile = "-";		# output file

# �I�v�V�����̒�`
#
my $patt_id = 0;
my $help = 0;
my $verbose = 0;
my $debug = 0;
my %options = (
    'help'	=> \$help,
    'outfile=s'	=> \$outfile,
    'patt_id=i'	=> \$patt_id,
    'verbose'	=> \$verbose,
    'Debug=i'	=> \$debug
);

# �R�}���h�����̏���
#
GetOptions(%options);
usage() if $help;
verbose_set($verbose);
debug_push($debug);
if ($#ARGV == 0) { $logfile = $ARGV[0] };
if ($#ARGV >  0) { usage() };

my $logfilename = $logfile eq "-" ? "STDIN"  : $logfile;
my $outfilename = $outfile eq "-" ? "STDOUT" : $outfile;
verbose("logfile: %s", $logfilename);
verbose("outfile: %s", $outfilename);
show_options() if $debug > 0;

# �t�@�C����ǂݍ���
#	%modules: ���W���[�������L�[�Ƃ��� %threads ���
#	%threads: �X���b�h�ԍ����L�[�Ƃ������̓f�[�^�s
#	@modules: ���W���[�����̔z�� (�o����)
#	@lines:   ���̓f�[�^�s
#
my ($modhash, $modname, $lines) = read_log($logfile, $script, $patt_id);
if (!defined($modhash) || !defined($modname) || !defined($lines)) {
    exit -1;
}
my %modules = %{$modhash};
my @modules = @{$modname};
my @lines = @{$lines};

# �t�@�C���ɏ����o��
#
debug(1, "opening file \"%s\" for output\n", $outfile);
my $rc = open(OFH, '>'.$outfile);
if (!defined($rc)) {
    error($script, "Can't Open file \"$outfile\" for output");
    exit -1;
}

STDOUT->autoflush(1);

for (my $i = 0; $i < @modules; $i++) {
    my $m = $modules[$i];
    my %threads = %{$modules{$m}};
    foreach my $t (sort { $a <=> $b } keys %threads) {
	my @data = @{$threads{$t}};
	for (my $j = 0; $j < @data; $j++) {
	    printf OFH "%s\n", $data[$j];
	}
    }
}
close OFH;

exit 0;

# ======================
#  �w��I�v�V�����̕\��
# ======================
sub show_options
{
    debug(1, "ARGV: %d\n", $#ARGV+1);
    debug(1, "options:\n");
    debug(1, "  -o: $outfilename\n");
    debug(1, "  -p: $patt_id\n");
    debug(1, "  -v: $verbose\n");
    debug(1, "  -D: $debug\n");
}

# ======================
#  �g�p���@�̕\��
# ======================
sub usage
{
    my $cmnd = "perl $script [options] [infile]";
    my @args = (
	{ "infile"	=> "input file name (default is stdin)" }
    );
    my @opts = (
	{ "-o outfile"	=> "output file name (default is stdout)" },
	{ "-p patt_id"	=> "module identifying pattern number" },
	{ "-h"		=> "show usage" },
	{ "-v"		=> "set verbose mode" },
	{ "-D level"	=> "debug level" }
    );
    show_usage($cmnd, \@args, \@opts);
    exit -1;
}
 
# end: order.pl
