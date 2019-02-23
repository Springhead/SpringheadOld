#!/usr/bin/perl
BEGIN { push(@INC, 'bin'); }
# ==============================================================================
#  File:
#	mydiff.pl
#
#  Description:
#	Visual Studio 10.0 (devenv) ���o�͂����r���h���O���r���ċ��ʂ���s��
#	��菜��. �����̓��W���[���P�ʂɍs�Ȃ�.
#
#  Version:
#	Ver 1.0  2013/02/06 F.Kanehori	Windows �ڐA���� (�S�ʉ���)
#	Ver 1.1  2018/07/03 F.Kanehori	�R�����g�C��.
#	Ver 1.11 2019/01/04 F.Kanehori	Bug fixed.
# ==============================================================================
#use strict;
use warnings;
use Getopt::Long;
use feature ':5.10';
use IO::Handle;
use base_lib;
use dailybuild_lib;

# �萔
#
my $mark_ins = ">";
my $mark_del = "<";
my $mark_chg = "!";
#my $mark_ins_c = "+";
#my $mark_del_c = "-";
#my $mark_chg_c = "!";
my $mark_spc = " ";
my $empty_mark = "_EMPTY_MARK_";
my %cmnd_tab = (
    $mark_ins	=> "a",
    $mark_del	=> "d",
    $mark_chg	=> "c"
);

# �ϐ�
#
my $script = leafname($0);
my $outfile = "-";		# output file

# �I�v�V�����̒�`
#
my $cdiff = 0;
my $patt_id = 0;
my $help = 0;
my $verbose = 0;
my $debug = 0;
my %options = (
    'context'	=> \$cdiff,
    'outfile=s'	=> \$outfile,
    'patt_id=i'	=> \$patt_id,
    'help'	=> \$help,
    'verbose'	=> \$verbose,
    'Debug=i'	=> \$debug
);

# �R�}���h�����̏���
#
GetOptions(%options);
usage() if $help;
verbose_set($verbose);
debug_push($debug);
if ($#ARGV != 1) { usage() };
my $infile1 = shift || usage();
my $infile2 = shift || usage();

my $outfilename = $outfile eq "-" ? "STDOUT" : $outfile;
if ($verbose) {
    printf STDERR "infile1: %s\n", $infile1;
    printf STDERR "infile2: %s\n", $infile2;
    printf STDERR "outfile: %s\n", $outfilename;
}
show_options() if $debug > 0;

# �t�@�C����ǂݍ���
#	%modhash: ���W���[�������L�[�Ƃ��� %threads ���
#	%threads: �X���b�h�ԍ����L�[�Ƃ������̓f�[�^�s
#	@modname: ���W���[�����̔z�� (�o����)
#	@lines:   ���̓f�[�^�s
#
my($modhash1, $modname1, $lines1) = read_log($infile1, $script, $patt_id);
if (!defined($modhash1) || !defined($modname1) || !defined($lines1)) {
    exit -1;
}
my($modhash2, $modname2, $lines2) = read_log($infile2, $script, $patt_id);
if (!defined($modhash2) || !defined($modname2) || !defined($lines2)) {
    exit -1;
}
my %modules1= %{$modhash1};
my @modules1= @{$modname1};
my @lines1= @{$lines1};
my %modules2= %{$modhash2};
my @modules2= @{$modname2};
my @lines2= @{$lines2};

STDOUT->autoflush(1);

# �t�@�C��1 ���ƃt�@�C��2 ���̃��W���[�����̑Ή����Ƃ�.
#	�������W���[������ @module1 �� @module2 �̓����v�f�ʒu�ɗ���悤�ɍĔz�u����.
#	@module1 �� @module2 �̋󂢂��v�f�i�����̃��W���[�������葤�ɂȂ����́j�ɂ�
#	    �g�폜�}�[�N�h(@module1��) �܂��́g�}���}�[�N�h(@module2��)
#	���L�^���Ă���.
#
my($new_mod1, $new_mod2) = associate_modules(\@modules1, \@modules2, $script, $verbose, $debug);
@modules1 = @{$new_mod1};
@modules2 = @{$new_mod2};

# �o�̓t�@�C�����I�[�v������
#
verbose("opening file \"%s\" for output.", $outfile);
my $rc = open(FH, '>'.$outfile);
if (!defined($rc)) {
    error($script, "can't open file \"$outfile\" for output.");
    exit -1;
}

# �������Ƃ�
#	�����̓��W���[���P�ʂōs�Ȃ�
#
verbose("diff process started.");
my $lineno1 = 1;
my $lineno2 = 1;

for (my $i = 0; $i < @modules1; $i++) {
    debug(1, "START AT (%d,%d)\n", $lineno1, $lineno2);
    my $module1 = $modules1[$i];
    my $module2 = $modules2[$i];

    # �ǂ��炩����̃t�@�C���ɂ����Ȃ����W���[���̏ꍇ
    #
    if ($module1 eq mod_ins()) {
	verbose("inserted  [%s]", $module2);
	output_module_name($module2);
	my $buff = gather_lines(\%modules2, $module2);
	printf FH "%da%d,%d\n", $lineno1, $lineno2, $lineno2 + @{$buff} - 1;
	output(*FH, $buff, $mark_ins);
	$lineno2 += @{$buff};
    }
    elsif ($module2 eq mod_del()) {
	verbose("deleted   [%s]", $module1);
	output_module_name($module1);
	my $buff = gather_lines(\%modules1, $module1);
	printf FH "%d,%dd%d\n", $lineno1, $lineno1 + @{$buff} - 1, $lineno2;
	output(*FH, $buff, $mark_del);
	$lineno1 += @{$buff};
    }
    # �����̃t�@�C���ɂ��郂�W���[���̏ꍇ
    #
    else {
	verbose("take diff [%s]", $module1);
	assert($module1 eq $module2);
	output_module_name($module1);
	my($count1, $count2)
	    = diff(*FH, \%modules1, $module1, $lineno1, \%modules2, $module2, $lineno2);
	debug(1, "--> processed (%d,%d) lines\n", $count1, $count2);
	$lineno1 += $count1;
	$lineno2 += $count2;
    }
} 

# �o�̓t�@�C�����N���[�Y����
#
close FH;

verbose("done.");
exit 0;

# ------------------------------------------------------------------------------
#  Subroutine:
#	($count1, $count2)
#	= diff($fh, \%modules1, $module1, $base1, \%modules2, $module2, $base2);
#
#	%modulesN	���W���[�����Ɠ��͍s��Ή��t�����n�b�V���e�[�u��
#	$moduleN	�����Ώۂ̃��W���[����
#	$baseN		�擪�s�̍s�ԍ�
#
#	$countN		%modulesN �ɂ��ď������ς񂾍s��
# ------------------------------------------------------------------------------
sub diff
{
    my $fh	 = shift || assert(0, "argument missing [\$fh]");
    my $modules1 = shift || assert(0, "argument missing [\%modules1]");
    my $module1	 = shift || assert(0, "argument missing [\$module1]");
    my $base1	 = shift || assert(0, "argument missing [\$base1]");
    my $modules2 = shift || assert(0, "argument missing [\%modules2]");
    my $module2	 = shift || assert(0, "argument missing [\$module2]");
    my $base2	 = shift || assert(0, "argument missing [\$base2]");

    my $buff1 = gather_lines(\%modules1, $module1);
    my $buff2 = gather_lines(\%modules2, $module2);
    my @buff1 = @{$buff1};
    my @buff2 = @{$buff2};
    my $count1 = 0;
    my $count2 = 0;
    my @del_buff = ();		# $del_buff[$i] = \($lineno1, $lineno2, $line);
    my @ins_buff = ();		# $ins_buff[$i] = \($lineno1, $lineno2, $line);
    my $need_flush = 0;
    object_dump(2, \@buff1, "buff1");
    object_dump(2, \@buff2, "buff2");

    my $line1 = shift @buff1;
    my $line2 = shift @buff2;
    while (defined($line1) || defined($line2)) {
	debug(3, "--------\n");
	debug(3, "Line1: [%s]\n", $line1) if defined($line1);
	debug(3, "Line2: [%s]\n", $line2) if defined($line2);

	if (!defined($line1)) {
	    # @buff2 �����ɍs������]�}�����ꂽ�s
	    my $ins_buff = eat_up(\@buff2, $mark_ins, $base1+$count1, $base2+$count2);
	    $count2 += @{$ins_buff};
	    my $size1 = 0;
	    my $size2 = @{$ins_buff} + 0;
	    debug(1, "*1_I2* (%3d) [%d lines inserted]\n", $base2+$count2, $#{$ins_buff}+1);
	    flush($fh, $mark_ins, $size1, $size2, $dummy_buff, $ins_buff);
	    $need_flush = 0;
	    last;
	}
	elsif (!defined($line2)) {
	    # @buff1 �����ɍs������]�폜���ꂽ�s
	    my $del_buff = eat_up(\@buff1, $mark_del, $base1+$count1, $base2+$count2);
	    $count1 += @{$del_buff};
	    my $size1 = @{$del_buff} + 0;
	    my $size2 = 0;
	    debug(1, "*1D_2* (%3d) [%d lines deleted]\n", $base1+$count1, $#{$del_buff}+1);
	    flush($fh, $mark_del, $size1, $size2, $del_buff, $dummy_buff);
	    $need_flush = 0;
	    last;
	}
	elsif ($line1 eq $line2) {
	    # �����s
	    my $size1 = @del_buff + 0;
	    my $size2 = @ins_buff + 0;
	    debug(1, "*same* (%3d) %s [%s]\n", $base1+$count1, $mark_spc, $line1);
	    if ($size1 >0 || $size2 > 0) {
		debug(2, "need flush: #(del_buff,ins_buff) = (%d,%d)\n", $size1, $size2);
	    }
	    flush($fh, $mark_chg, $size1, $size2, \@del_buff, \@ins_buff) if $need_flush;
	    $need_flush = 0;
	    $count1++;
	    $count2++;
	    $line1 = shift @buff1;
	    $line2 = shift @buff2;
	    @del_buff = ();
	    @ins_buff = ();
	}
	else {
	    my $line1_in_buff2 = is_in_buff(\@buff2, $line1);
	    my $line2_in_buff1 = is_in_buff(\@buff1, $line2);
	    debug(1, "line1 in buff2: [%s] [%s]\n", $line1_in_buff2 ? "Y" : "N", $line1);
	    debug(1, "line2 in buff1: [%s] [%s]\n", $line2_in_buff1 ? "Y" : "N", $line2);

	    if (!$line1_in_buff2 && $line2_in_buff1) {
		# $line1 �� @buff2 �ɂȂ�, ���� $line2 �� @buff1 �ɂ��� �| �폜���ꂽ�s
		while (defined($line1) && ($line1 ne $line2)) {
		    push @del_buff, triplet($base1+$count1, $base2+$count2, $line1);
		    debug(1, "*1d_2* (%3d) %s [%s]\n", $base1+$count1, $mark_del, $line1);
		    $count1++;
		    $line1 = shift @buff1;
		}
		$need_flush = 1;
	    }
	    elsif ($line1_in_buff2 && !$line2_in_buff1) {
		# $line1 �� @buff2 �ɂ���, ���� $line2 �� @buff1 �ɂȂ� �| �}�����ꂽ�s
		while (defined($line2) && ($line2 ne $line1)) {
		    push @ins_buff, triplet($base1+$count1, $base2+$count2, $line2);
		    debug(1, "*1_i2* (%3d) %s [%s]\n", $base2+$count2, $mark_ins, $line2);
		    $count2++;
		    $line2 = shift @buff2;
		}
		$need_flush = 1;
	    }
	    else {
		# $line1 �͍폜���ꂽ�s�ŁA$line2 �͑}�����ꂽ�s
		push @del_buff, triplet($base1+$count1, $base2+$count2, $line1);
		push @ins_buff, triplet($base1+$count1, $base2+$count2, $line2);
		debug(1, "*1d__* (%3d) %s [%s]\n", $base1+$count1, $mark_del, $line1);
		debug(1, "*__i2* (%3d) %s [%s]\n", $base2+$count2, $mark_ins, $line2);
		$count1++;
		$count2++;
		$line1 = shift @buff1;
		$line2 = shift @buff2;
		$need_flush = 1;
	    }
	}
	#sleep(1);
    }
    my $size1 = @del_buff + 0;
    my $size2 = @ins_buff + 0;
    flush($fh, $mark_ins, $size1, $size2, \@del_buff, \@ins_buff);

    return ($count1, $count2);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	\@outbuff = eat_up(\@inbuff, $mark, $base1, $base2);
#
#	@inbuff		���̓f�[�^�̔z��
#	$mark		$mark_del �� $mark_ins �̂����ꂩ
#	$base1		�t�@�C��1 ���ɑΉ�����擪�s�ԍ�
#	$base2		�t�@�C��2 ���ɑΉ�����擪�s�ԍ�
#
#	@outbuff	���������O�g�݂̔z��
# ------------------------------------------------------------------------------
sub eat_up
{
    my $inbuff	= shift || assert(0, "argument missing [\@inbuff]");
    my $mark	= shift || assert(0, "argument missing [\$mark]");
    my $base1	= shift || assert(0, "argument missing [\$base1]");
    my $base2	= shift || assert(0, "argument missing [\$base2]");
    my @inbuff = @{$inbuff};

    my @outbuff = ();
    my $count = 0;
    my $line = shift @inbuff;
    while (defined($line)) {
	if ($mark eq $mark_del) {
	    push @outbuff, triplet($base1+$count, $base2, $line);
	    debug(1, "eat_up: DEL(%d) [%s]\n", $base1+$count, $line);
	}
	else {
	    push @outbuff, triplet($base1, $base2+$count, $line);
	    debug(1, "eat_up: INS(%d) [%s]\n", $base2+$count, $line);
	}
	$count++;
	$line = shift @inbuff;
    }
    return \@outbuff;
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	\@array3 = triplet($lineno1, $lineno2, $line);
#
#	$lineno1	�t�@�C��1 ���ɑΉ�����s�ԍ�
#	$lineno2	�t�@�C��2 ���ɑΉ�����s�ԍ�
#	$line		�s�f�[�^
#
#	@array3		\($lineno1, $lineno2, $line)
# ------------------------------------------------------------------------------
sub triplet
{
    my $lineno1	= shift || assert(0, "argument missing [\$lineno1]");
    my $lineno2	= shift || assert(0, "argument missing [\$lineno2]");
    my $line	= shift || $empty_mark;		# undef �Ƃ��Ȃ�����

    my @array3 = ();
    push @array3, $lineno1;
    push @array3, $lineno2;
    push @array3, $line;

    return \@array3;
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	flush($fh, $mark, $size1, $size2, \@buff1, \@buff2);
#
#	$fh		�o�̓t�@�C���n���h��
#	$mark		�s�ҏW�R�}���h�e�[�u���̃L�[
#	$sizeN		@buffN �̗v�f��
#	@buffN		�o�͍s�f�[�^�̔z��
# ------------------------------------------------------------------------------
sub flush
{
    my $fh    = shift || assert(0, "argument missing [\*fh]");
    my $mark  = shift || assert(0, "argument missing [\$mark]");
    my $size1 = shift || 0;
    my $size2 = shift || 0;
    my $buff1 = shift;
    my $buff2 = shift;

    my @tmp1 = @{$buff1} if $buff1;
    my @tmp2 = @{$buff2} if $buff2;
    assert(($size1 == @tmp1), sprintf "buff1 size differ (%d)-(%d).", $size1, @tmp1+0);
    assert(($size2 == @tmp2), sprintf "buff2 size differ (%d)-(%d).", $size2, @tmp2+0);

    if ($size1 == 0 || $size2 == 0) {
	return if $size1 == 0 && $size2 == 0;
	flush1($fh, $mark_del, $buff1) unless $size1 == 0;
	flush1($fh, $mark_ins, $buff2) unless $size2 == 0;
	return;
    }
    my($min11, $max11, $min21, $max21, $lines1) = min_max($buff1);
    my($min12, $max12, $min22, $max22, $lines2) = min_max($buff2);
    printf $fh edit_command($min11, $max11, $min22, $max22, $cmnd_tab{$mark});
    my @lines1 = @{$lines1};
    my @lines2 = @{$lines2};
    output($fh, \@lines1, $mark_del);
    printf $fh "--\n";
    output($fh, \@lines2, $mark_ins);
    debug(1, "flush: DEL (%3d,%3d)-(%3d,%3d), INS (%3d,%3d)-(%3d,%3d)\n",
	    $min11, $max11, $min21, $max21, $min12, $max12, $min22, $max22);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	flush1($fh, $mark, \@buff);
#
#	$fh		�o�̓t�@�C���n���h��
#	$mark		�s�ҏW�R�}���h
#	@line		�o�͍s�f�[�^�̔z��
# ------------------------------------------------------------------------------
sub flush1
{
    my $fh   = shift || assert(0, "argument missing [\*fh]");
    my $mark = shift || assert(0, "argument missing [\$mark]");
    my $buff = shift || assert(0, "argument missing [\$buff]");
    return if @{$buff} == 0;

    my($min1, $max1, $min2, $max2, $lines) = min_max($buff);
    printf $fh edit_command($min1, $max1, $min2, $max2, $cmnd_tab{$mark});
    my @lines = @{$lines};
    output($fh, \@lines, $mark);
    debug(1, "flush: (%3d,%3d) - (%3d,%3d)\n", $min1, $max1, $min2, $max2);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	($min1, $max1, $min2, $max2, \@lines) = min_max(\@buff);
#
#	@buff		�O�g�݃f�[�^�̔z��
#
#	$min1,$max1	�t�@�C��1 �ɑΉ�����s�ԍ��̍ŏ��l�ƍő�l
#	$min2,$max2	�t�@�C��2 �ɑΉ�����s�ԍ��̍ŏ��l�ƍő�l
#	@lines		�o�͍s�f�[�^�̔z��
# ------------------------------------------------------------------------------
sub min_max
{
    my $buff = shift || assert(0, "argument missing [\$buff]");
    my @buff = @{$buff};

    my $min1 = 9999;
    my $max1 = 0;
    my $min2 = 9999;
    my $max2 = 0;
    my @lines = ();
    for (my $i = 0; $i < @buff; $i++) {
	my $element = $buff[$i];
	my($lineno1, $lineno2, $line) = @{$element};
	$min1 = $lineno1 if $lineno1 < $min1;
	$max1 = $lineno1 if $lineno1 > $max1;
	$min2 = $lineno2 if $lineno2 < $min2;
	$max2 = $lineno2 if $lineno2 > $max2;
	push @lines, $line;
    }

    return ($min1, $max1, $min2, $max2, \@lines);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	$str = edit_command($min1, $max1, $min2, $max2, $cmnd);
#
#	$min1,$max1	�t�@�C��1 �ɑΉ�����s�ԍ��̍ŏ��l�ƍő�l
#	$min2,$max2	�t�@�C��2 �ɑΉ�����s�ԍ��̍ŏ��l�ƍő�l
#	$cmnd		�ҏW�R�}���h
#
#	$str		�ҏW�R�}���h�i�s�ԍ��w����܂ށj
# ------------------------------------------------------------------------------
sub edit_command
{
    my $min1 = shift || assert(0, "argument missing [\$min1]");
    my $max1 = shift || assert(0, "argument missing [\$max1]");
    my $min2 = shift || assert(0, "argument missing [\$min2]");
    my $max2 = shift || assert(0, "argument missing [\$max2]");
    my $cmnd = shift || assert(0, "argument missing [\$cmnd]");

    my $fmt1 = ($min1 == $max1) ? "%d" : "%d,%d";
    my $fmt2 = ($min2 == $max2) ? "%d" : "%d,%d";
    my $str1 = sprintf $fmt1, $min1, $max1;
    my $str2 = sprintf $fmt2, $min2, $max2;

    return $str1.$cmnd.$str2."\n";
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	output_module_name($fh, $module);
#
#	$fh		�o�̓t�@�C���n���h��
#	$module		���W���[����
# ------------------------------------------------------------------------------
sub output_module_name
{
    my $module = shift || assert(0, "argument missing [\$module]");

    return if $module eq "_top_level_";
    printf FH "\n[ $module ]\n";
    STDOUT->autoflush(1);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	output($fh, \@buff, $mark);
#
#	$fh		�o�̓t�@�C���n���h��
#	@buff		�o�͍s�f�[�^
#	$mark		�}���E�폜�E�u���\������
# ------------------------------------------------------------------------------
sub output
{
    my $fh   = shift || assert(0, "argument missing [\*fh]");
    my $buff = shift || assert(0, "argument missing [\$buff]");
    my $mark = shift || assert(0, "argument missing [\$mark]");
    my @buff = @{$buff};

    for (my $i = 0; $i < @buff; $i++) {
	$buff[$i] = "" if $buff[$i] eq $empty_mark;
	printf $fh "%s %s\n", $mark, $buff[$i];
    }
    STDOUT->autoflush(1);
}

# ----------------------
#  �w��I�v�V�����̕\��
# ----------------------
sub show_options
{
    debug(1, "ARGV: %d\n", $#ARGV+1);
    debug(1, "options:\n");
    debug(1, "  -c: $cdiff\n"),
    debug(1, "  -o: $outfilename\n");
    debug(1, "  -v: $verbose;\n");
    debug(1, "  -D: $debug;\n");
}

# ----------------------
#  �g�p���@�̕\��
# ----------------------
sub usage
{
    my $cmnd = "perl $script [options] infile-1 infile-2";
    my @args = ();
    my @opts = (
	{ "-o outfile"	=> "output file name (default is stdout)" },
	{ "-c"		=> "output like context diff(*NOT IMPLEMENTED*)" },
	{ "-p patt_id"	=> "module identifying pattern number" },
	{ "-h"		=> "show usage" },
    	{ "-v"		=> "set verbose mode" },
	{ "-D level"	=> "debug level"}
    );
    show_usage($cmnd, \@args, \@opts);
    exit -1;
}
 
# end: mydiff.pl
