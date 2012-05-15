#!/usr/bin/perl

use strict;
use utf8;
use Encode;
use open ":utf8";
use open ":std";

chdir $ARGV[0];

my @files = sort(<E383A9E382A4E38396E383A9E383AA2F*.txt>);

foreach my $file (@files) {
    my $name = $file;
    $name =~ s/^E383A9E382A4E38396E383A9E383AA2F//;
    $name =~ s/\.txt$//;
    $name =~ s/([0-9A-F][0-9A-F])/pack('H2', $1)/eg;
    $name = Encode::decode("utf8", $name);

    my $lastsection = "";
    my $lastsubsection = "";
    my ($section, $subsection, $article) = ($name =~ /(.*)\/(.*)\/(.*)/);
    if (defined($article)) {

        print "% PROCESSING $file ($section : $subsection : $article)\n\n";

        open(IN, "$file") or die;
        my $text = join('', <IN>);
        close(IN);

        $text =~ /^/g;

        my @implements = split(/\*\*\s*解説.*?\n/s, $text);
        shift(@implements);

        if (@implements > 0) {

            if ($section != $lastsection) {
                print "\\section{$section}\n\n";
                $lastsection = $section;
                $lastsubsection = "";
            }

            if ($subsection != $lastsubsection) {
                print "\\subsection{$subsection}\n\n";
                $lastsubsection = $subsection;
            }
            
            foreach my $text0 (@implements) {
                $text0 = "\*\* 解説 [#hoge]\n" . $text0;

                my $desc = "";
                my @memos;
                my $status = "\\nottested\n";
                my $code = "";
                    
                my @parts = split(/^\*\*\s*/m, $text0);
                foreach my $part (@parts) {
                    
                    my ($title) = ($part =~ /^(.*?)\s*\[#/s);
                    $part =~ s/^.*?\n//;
                    
                    if ($title eq "解説") {
                        $desc = $part;
                        $desc =~ s/^\s*//s;
                        $desc =~ s/\s*$//s;
                        $desc .= "\n";
                    }
                    if ($title eq "前提条件") {
                        push(@memos, &split_items($part));
                    }
                    if ($title eq "コード") {
                        ($code) = ($part =~ /#code\(\)\{\{\s*(.*?)\s*\}\}/s);
                    }
                    if ($title eq "検証状態") {
                        if ($part =~ /^-.*検証済み/m) {
                            $status = "";
                            while($part =~ /^--\s*(.*?)\s*$/mg) {
                                $status .= "\\accepted{$1}\n";
                            }
                            if ($status eq "") {
                                $status .= "\\accepted{}\n";
                            }
                        }
                        if ($part =~ /^-.*検証なし/m) {
                            $status = "";
                        }
                    }
                    if ($title eq "メモ") {
                        push(@memos, &split_items($part));
                    }
                    if ($title eq "依存関係") {
                    }
                }

                print "% BEGIN OF ARTICLE\n\n";
                print "% DESCRIPTION:\n$desc\n";
                print "% NOTES:\n" . &texize_items(@memos) . "\n";
                print "% STATUS:\n$status\n";
                print "% CODE:\n\\begin{code}\n";
                print $code;
                print "\n\\end{code}\n";
                print "% END OF ARTICLE\n\n\n\n\n";
            }
        }
    }
}


sub split_items {
    my ($text) = @_;
    my @res;

    while($text =~ /^(-+)\s*(.*?)\s*$/mg) {
        my ($indent, $s) = (length($1), $2);
        push(@res, "$indent $s");
    }

    return @res;
}

sub texize_items {
    my $res = "";
    my $level = 0;
    foreach(@_) {
        my ($i, $s) = /(\d+) (.*)/;
        while($level < $i) {
            $res .= "\\begin{itemize}\n";
            $level++;
        }
        while($level > $i) {
            $res .= "\\end{itemize}\n";
            $level--;
        }
        $res .= "\\item{$s}\n";
    }
    while($level > 0) {
        $res .= "\\end{itemize}\n";
        $level--;
    }
    return $res;
}

