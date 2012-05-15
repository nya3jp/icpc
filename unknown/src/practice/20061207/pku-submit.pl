#!/usr/bin/perl

use strict;

use HTTP::Cookies;
use LWP::Simple;
use LWP::UserAgent;

$| = 1;

my ($username, $password, $language);

if (open(CONF, "$ENV{HOME}/.pku-submit")) {
    foreach(<CONF>) {
        /^\s*([^=]*?)\s*=\s*(.*?)\s*$/;
        my ($name, $value) = (uc($1), $2);
        $username = $value if ($name eq 'USERNAME');
        $password = $value if ($name eq 'PASSWORD');
        $language = $value if ($name eq 'LANGUAGE');
    }
    close(CONF);
}

while(@ARGV > 0) {
    my $cmd = $ARGV[0];
    last unless ($cmd =~ /^-/);
    if ($cmd eq '-user') {
        $username = $ARGV[1];
        shift(@ARGV);
        shift(@ARGV);
    }
    elsif ($cmd eq '-lang') {
        $language = $ARGV[1];
        shift(@ARGV);
        shift(@ARGV);
        redo;
    }
    elsif ($cmd eq '-pass') {
        $password = $ARGV[1];
        shift(@ARGV);
        shift(@ARGV);
    }
    else {
        die "unknown option: $ARGV[0]\n";
    }
}

if (@ARGV != 2) {
    print <<"__EOF__";
Usage: pku-submit.pl [OPTION]... PROBLEM-ID SOURCE
Submits a solution to PKU Online Judge.

Options: -user USERNAME    set username to USERNAME.
         -pass PASSWORD    set password to PASSWORD.
         -lang LANGUAGE    set language to LANGUAGE.

Supported languages are:
    g++, gcc, Java, Pascal, c++, c

Put config file to ~/.pku-submit like this:

    USERNAME = nya
    PASSWORD = foobar
    LANGUAGE = g++

__EOF__
    exit 1;
}

die "password is not specified" if (!defined($password));

my $langid = -1;
$language = uc($language);
$langid = 0 if ($language eq 'G++');
$langid = 1 if ($language eq 'GCC');
$langid = 2 if ($language eq 'JAVA');
$langid = 3 if ($language eq 'PASCAL');
$langid = 4 if ($language eq 'C++');
$langid = 5 if ($language eq 'C');

if ($langid < 0) {
    print "Language $language is not supported.\n";
    exit 1;
}

my $problemid = shift(@ARGV);
my $codefile = shift(@ARGV);

print "submitting $codefile (problem: $problemid) ... ";

my $login_url = 'http://acm.pku.edu.cn/JudgeOnline/login';
my $submit_url = 'http://acm.pku.edu.cn/JudgeOnline/submit';
my $status_url = 'http://acm.pku.edu.cn/JudgeOnline/status';

open(CODE, $codefile) or die "cannot open source code!";
my $code = join('', <CODE>);
close(CODE);

my $cookie_jar = HTTP::Cookies->new();

my $ua = LWP::UserAgent->new();
$ua->cookie_jar($cookie_jar);

my %login_form = ('user_id1' => $username, 'password1' => $password);
my $login_res = $ua->post($login_url, \%login_form);

my $login_body = $login_res->content;
$login_body =~ /failed/ and die "Invalid login name and/or password!";

my %submit_form = ('problem_id' => $problemid,
                   'language' => $langid,
                   'source' => $code);

my $submit_res = $ua->post($submit_url, \%submit_form);

print "Done.\n";

my $cnt = 0;
while(1) {

    $cnt++;
    print "Waiting for result ...\n";

    my $status_res = get($status_url . "?problem_id=$problemid&user_id=$username");

    my ($id, $result, $memory, $runtime, $lang, $length, $date) = ($status_res =~ m{<tr align=center><td>(\d*)</td><td><a href=userstatus\?user_id=$username>$username</a></td><td><a href=problem\?id=$problemid>$problemid</a></td><td><font color=[^>]*>([^<]*)</font></td><td>([^<]*)</td><td>([^<]*)</td><td>([^<]*)</td><td>([^<]*)</td><td>([^<]*)</td></tr>}o);

    if (!($result =~ /ing$/)) {
        if ($result eq 'Accepted') {
            print <<"__EOF__";

\ ###   ###   ###  ##### ####  ##### ##### ####   ## ##
\#   # #   # #   # #     #   #   #   #     #   #  ## ##
\##### #     #     ##### ####    #   ##### #   #  ## ##
\#   # #   # #   # #     #       #   #     #   #       
\#   #  ###   ###  ##### #       #   ##### ####   ## ##

Running Time: $runtime
Used Memory:  $memory
Code Length:  $length

__EOF__
        }
        else {
            print "$result.\n";
        }
        last;
    }

    sleep(1);
}

