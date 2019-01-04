package dailybuild_lib;
# ==============================================================================
#  File:
#	dailybuild_lib.pm
#
#  Description:
#	Daily build ���ʂ̉�͂ɋ��ʂ�����Ƃ��s�Ȃ��T�u���[�`���̃��C�u����.
#
#  Version:
#	Ver 1.0  2013/02/01 F.Kanehori	����
#	Ver 1.1  2013/03/11 F.Kanehori	read_log: ���W���[�����p�^�[���C��
#	Ver 1.11 2018/07/12 F.Kanehori	�R�����g�C��
#	Ver 1.2  2019/01/04 F.Kanehori	add: is_in_buff()
# ==============================================================================
use base 'Exporter';
@EXPORT = qw(read_log associate_modules mod_ins mod_del
	     gather_lines is_in_buff);
@EXPORT_OK = qw(outside_threads_before outside_threads_after);
use base_lib;

# ------------------------------------------------------------------------------
#  Subroutine:
#	(\%modules, \@modules, \@lines) = read_log($logfile, $script [, $patt_id]);
#
#	$logfile	���O�t�@�C����
#	$script		�Ăяo�����X�N���v�g�� (�G���[�\���p)
#	$patt_id	���W���[���J�n�p�^�[�� ID
#	%modules	�L�[: ���W���[����, �l: \%threads
#				%threads: �L�[ = �X���b�h�ԍ�, �l = �s�f�[�^
#	@modules	�v�f = ���W���[���� (�o����)
#	@lines		�v�f = �s�f�[�^
# ------------------------------------------------------------------------------
sub read_log
{
    my $logfile = shift || assert(0, "argument missing [\$logfile]");
    my $script  = shift || assert(0, "argument missing [\$script]");
    my $patt_id = shift || 0;

    # ���W���[���J�n�p�^�[���̒�`
    #	   id 0:	Build.log and Run.log �p
    #	   id 1:	StubBuild.log �p
    #	   id 2:	filter.pl �p
    #
    my @pattern = (
	"^\\*\\*\\* ([0-9A-Za-z][0-9A-Za-z :\\/]+) \\*\\*\\*",
	"^[0-9]+>[ \t]+\\*\\*\\* ([0-9A-Za-z][0-9A-Za-z :\\/]+) \\*\\*\\*",
	"^\\[ ([0-9A-Za-z][0-9A-Za-z :\\/]+) \\]"
    );

    # �ϐ��̒�`
    #
    my %modules = ();
    my @modules = ();
    my @lines = ();

    # �t�@�C����ǂݍ���
    #
    verbose("opening file \"%s\" for input", $logfile);
    my $rc = open(FH, '<'.$logfile);
    if (!defined($rc)) {
	error($script, "can't open file \"$logfile\" for input.");
	return undef;
    }

    my $module = '_top_level_';
    push @modules, $module;
    my $outside_threads = outside_threads_before();

    while (<FH>) {
	chomp;
	push(@lines, $_);
	if (/$pattern[$patt_id]/) {
	    # �V�������W���[���̎n�܂�
	    #
	    $module = $1;
	    $outside_threads = outside_threads_before();
	    push @modules, $module;
	    verbose("found module: %s", $_);
	}
	my $thread = $outside_threads;
	if (/^([0-9]+)>/) {
	    # �X���b�h���o�͂������
	    #
	    $thread = $1;
	    $outside_threads = outside_threads_after();
	}

	# ���W���[����, �X���b�h��, �o�����ɐ�������
	# ���̃f�[�^�� @lines �Ɋi�[����Ă���
	#
	my %threads;
	if (!defined($modules{$module})) {
	    %threads = ();
	    $modules{$module} = \%threads;
	}
	else {
	    %threads = %{$modules{$module}};
	}
	my @data;
	if (!defined($threads{$thread})) {
	    @data = ();
	    $threads{$thread} = \@data;
	}
	else {
	    @data = @{$threads{$thread}};
	}
	push @data, $_;
	$threads{$thread} = \@data;
	$modules{$module} = \%threads;
	debug(1, "[%s] (%d) %s\n", $module, $thread, $_);
    }
    close FH;

    return (\%modules, \@modules, \@lines);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	$thread_number_before = outside_threads_before();
#	$thread_number_after  = outside_threads_after();
#
#	$thread_number_before	�X���b�h�����O�̕����ɑ΂���X���b�h�ԍ�
#	$thread_number_after	�X���b�h������̕����ɑ΂���X���b�h�ԍ�
# ------------------------------------------------------------------------------
sub outside_threads_before { return -1; }
sub outside_threads_after { return 999; }
 
# ------------------------------------------------------------------------------
#   Subroutine:
#	(\@modules1, \@modules2)
#		= associate_modules(\@modules1, \@modules2, $script);
#
#		    input			        output
#	    +-------+   +-------+		+-------+   +-------+
#	    |   1   |	|   1   |	��	|   1   |   |   1   |
#	    +-------+   +-------+		+-------+   +-------+
#	    |   2   |	|   X   |	��	| _ins_ |   |   X   |
#	    +-------+   +-------+		+-------+   +-------+
#	    |   3   |	|   2   |	��	|   2   |   |   2   |
#	    +-------+   +-------+		+-------+   +-------+
#	    |   4   |	|   3   |	��	|   3   |   |   3   |
#	    +-------+   +-------+		+-------+   +-------+
#	    |   5   |	|   5   |	��	|   4   |   | _del_ |
#	    +-------+   +-------+		+-------+   +-------+
#	    modules1     modules2		|   5   |   |   5   |
#						+-------+   +-------+
#						modules1     modules2
# ------------------------------------------------------------------------------
sub associate_modules
{
    my $modules1 = shift || assert(0, "argument missing [\@modules1]");
    my $modules2 = shift || assert(0, "argument missing [\@modules2]");
    my $script	 = shift || assert(0, "argument missing [\$script]");
    my @old_mod1 = @{$modules1};
    my @old_mod2 = @{$modules2};

    debug(1, "OLD1: %s\n", join ' ', @old_mod1);
    debug(1, "OLD2: %s\n", join ' ', @old_mod2);
    my @new_mod1 = ();
    my @new_mod2 = ();
    my $module1 = shift @old_mod1;
    my $module2 = shift @old_mod2;
    while (defined($module1) || defined($module2)) {
	debug(1, "try [%-16s]-[%-16s]\n", $module1, $module2);

	if (!defined($module1)) {
	    push @new_mod1, mod_ins();
	    push @new_mod2, $module2;
	    debug(2, "1--[%s]--[%s]--\n", mod_ins(), $module2);
	    $module2 = shift @old_mod2;
	}
	elsif (!defined($module2)) {
	    push @new_mod1, $module1;
	    push @new_mod2, mod_del();
	    debug(2, "2--[%s]--[%s]--\n", $module1, mod_del());
	    $module1 = shift @old_mod1;
	}
	elsif ($module1 eq $module2) {
	    push @new_mod1, $module1;
	    push @new_mod2, $module2;
	    debug(2, "3--[%s]--[%s]--\n", $module1, $module2);
	    $module1 = shift @old_mod1;
	    $module2 = shift @old_mod2;
	}
	else {
	    if (is_in_buff(\@old_mod2, $module1)) {
		push @new_mod1, mod_ins();
		push @new_mod2, $module2;
		debug(2, "4--[%s]--[%s]--\n", mod_ins(), $module2);
		$module2 = shift @old_mod2;
	    }
	    elsif (is_in_buff(\@old_mod1, $module2)) {
		push @new_mod1, $module1;
		push @new_mod2, mod_del();
		debug(2, "5--[%s]--[%s]--\n", $module2, mod_del());
		$module1 = shift @module1;
	    }
	    else {
		push @new_mod1, $module1;
		push @new_mod2, mod_del();
		push @new_mod1, mod_ins();
		push @new_mod2, $module2;
		debug(2, "6--[%s]--[%s]--\n", $module1, mod_del());
		debug(2, "7--[%s]--[%s]--\n", mod_ins(), $module2);
		$module1 = shift @old_mod1;
		$module2 = shift @old_mod2;
	    }
	}
    }
    debug(1, "NEW1: %s\n", join ' ', @new_mod1);
    debug(1, "NEW2: %s\n", join ' ', @new_mod2);
    if (@new_mod1 != @new_mod2) {
	panic($script, "associate_modules: array size (%d-%d).", @new_mod1, @new_mod2);
	exit -1;
    }

    return (\@new_mod1, \@new_mod2);
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	$ins = mod_ins();
#	$del = mod_del();
#
#	$ins		�}�����W���[���������蕶����
#	$del		�폜���W���[���������蕶����
# ------------------------------------------------------------------------------
sub mod_ins { return '_INS_'; }
sub mod_del { return '_DEL_'; }

# ------------------------------------------------------------------------------
#  Subroutine:
#	\@buff = gather_lines(\%modules, $module);
#
#	%modules	���W���[�����Ɠ��͍s��Ή��t�����n�b�V���e�[�u��
#	$module		�����Ώۂ̃��W���[����
#	@buff		%modules ����L�[�� $module �̍s���W�߂�����
# ------------------------------------------------------------------------------
sub gather_lines
{
    my $modules	= shift || assert(0, "argument mising [\%modules]");
    my $module	= shift || assert(0, "argument mising [\$module]");
    my %modules = %{$modules};

    my @buff = ();
    my %threads = %{$modules{$module}};
    foreach my $t (sort { $a <=> $b } keys %threads) {
	push @buff, @{$threads{$t}};    
    }
    object_dump(3, \@buff, "GATHER_LINES: \@buff");

    return \@buff;
}

# ------------------------------------------------------------------------------
#  Subroutine:
#	$result = is_in_buff(\@buff, $data);
#
#	@buff		�f�[�^�̑��݂��m�F���镶����̔z��
#	$data		�f�[�^������
#	$result		�f�[�^�����݂�����^�A���݂��Ȃ���΋U
# ------------------------------------------------------------------------------
sub is_in_buff
{
    my $buff = shift || assert(0, "argument missing [\$buff]");
    my $data = shift;
    my @buff = @{$buff};

    $judge = 0;
    $line = shift @buff;
    while (defined($line)) {
	if ($line eq $data) {
	    $judge = 1;
	    last;
	}
	$line = shift @buff;
    }
    return $judge == 1;
}

1;
# end: dailybuild_lib.pm
