#!/usr/bin/perl

use strict;
use Jcode;
use POSIX 'strftime';

my $output = "";


my $contenttype = "text/plain; charset=Shift_JIS";
my $downname;

if ($ENV{QUERY_STRING} eq 'binary') {
    $contenttype = "application/octet-stream";
    $downname = "libicpc.tex";
}

$output .= "Content-Type: $contenttype\n";
if (defined($downname)) {
    $output .= "Content-Disposition: attachment; filename=\"$downname\"\n";
    $output .= "Content-Type: application/download; name=\"$downname\"\n";
}
$output .= "\n";


my $header = &read_file("./texize.header");
my $footer = &read_file("./texize.footer");

chdir "wiki";

my $generatedate = strftime("%Y/%m/%d", localtime);
my $generatetime = strftime("%Y/%m/%d %H:%M:%S", localtime);
my $updatedate = strftime("%Y/%m/%d", localtime((stat("."))[9]));
my $updatetime = strftime("%Y/%m/%d %H:%M:%S", localtime((stat("."))[9]));

$header =~ s/\$updatedate\$/$updatedate/isg;
$header =~ s/\$generatedate\$/$generatedate/isg;
$footer =~ s/\$updatedate\$/$updatedate/isg;
$footer =~ s/\$generatedate\$/$generatedate/isg;

$output .= "%\n";
$output .= "% Generated from libicpc wiki (http://nya3.jp/libicpc/)\n";
$output .= "% on $generatetime\n";
$output .= "% by texize.cgi\n";
$output .= "%\n\n";

$output .= $header;

my $lastsection = "";
my $lastsubsection = "";

my $library_index = &read_file(&encode_utf8_hex("ライブラリ") . ".txt");

my @sections;
while($library_index =~ /^\s*#include\(ライブラリ\/([^,)]*)(,[^,)]*)*\)/mg) {
    push(@sections, $1);
}

foreach my $section (@sections) {

    $output .= "\\section{$section}\n\n";

    my $section_index = &read_file(&encode_utf8_hex("ライブラリ/$section") . ".txt");

    my @subsections;
    while($section_index =~ /^\s*#lsx\(prefix=(\.\/)?([^)]*)\)/mg) {
        push(@subsections, $2);
    }

    foreach my $subsection (@subsections) {

        $output .= "\\subsection{$subsection}\n\n";

        my @subsection_files = glob(&encode_utf8_hex("ライブラリ/$section/$subsection/") . "*.txt");

        foreach my $file (@subsection_files) {
            my $name = $file;
            $name =~ s/^E383A9E382A4E38396E383A9E383AA2F//;
            $name =~ s/\.txt$//;
            $name = &decode_utf8_hex($name);

            my ($section2, $subsection2, $article) = ($name =~ /(.*)\/(.*)\/(.*)/);

            next unless defined($article);
            if ($section2 ne $section || $subsection2 ne $subsection) {
                $output .= "% ERROR: SECTION/SUBSECTION NAME DOES NOT MATCH!\n\n";
                next;
            }

            $output .= "% PROCESSING $file\n\n";

            my $text = &read_file($file);

            $text = jcode($text)->utf8;

            $text =~ /^/g;

            my @implements = split(/\*\*\s*解説.*?\n/s, $text);
            shift(@implements);

            if (@implements > 0) {

                my $iimpl = 0;
                foreach my $text0 (@implements) {
                    $text0 = "\*\* 解説 [#hoge]\n" . $text0;

                    my $desc = "";
                    my @memos;
                    my $status = "\\nottested\n\n";
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
                            $desc = &texize_wiki($desc);
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
                                    $status .= "\\accepted{$1}\n\n";
                                }
                                if ($status eq "") {
                                    $status .= "\\accepted{NO VERIFICATION PROBLEM AVAILABLE}\n\n";
                                }
                            }
                            if ($part =~ /^-.*検証なし/m) {
                                $status = "\\accepted{検証なし}\n\n";
                            }
                        }
                        if ($title eq "メモ") {
                            push(@memos, &split_items($part));
                        }
                        if ($title eq "依存関係") {
                        }
                    }

                    my $articlename = $article;
                    if (@implements > 1) {
                        $articlename .= " (" . ($iimpl+1) . ")";
                    }

                    $output .= "% BEGIN OF ARTICLE\n\n";
                    $output .= "\\subsubsection{$articlename}\n\n";
                    $output .= "% DESCRIPTION:\n$desc\n";
                    $output .= "% NOTES:\n" . &texize_items(@memos) . "\n";
                    $output .= "% STATUS:\n$status\n";
                    $output .= "% CODE:\n\\begin{code}\n";
                    $output .= $code;
                    $output .= "\n\\end{code}\n\n";
                    $output .= "% END OF ARTICLE\n\n\n\n\n";

                    $iimpl++;
                }
            }
        }
    }

    $output .= "\\newpage\n\n";
}

$output .= $footer;

print jcode($output)->sjis;

exit 0;








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
        $s = &texize_wiki($s);
        $res .= "\\item{$s}\n";
    }
    while($level > 0) {
        $res .= "\\end{itemize}\n";
        $level--;
    }
    return $res;
}

sub texize_wiki {
    my ($in) = @_;
    my $out = "";

    my @parts = split(/\$/, $in);
    my $math = 0;
    foreach my $part (@parts) {

        if ($math) {
            $out .= "\$$part\$";
        }
        else {

            $part =~ s/^\/\/[^\n]*\n//mg;

            $part =~ s/\[\[([^]]*)>[^]]*\]\]/\1/sg;
            $part =~ s/\[\[([^]]*)\]\]/\1/sg;

            $part =~ s/\\/\$\\backslash\$/sg;
            $part =~ s/{/\\{/sg;
            $part =~ s/}/\\}/sg;

            $part =~ s/\'\'(.*?)\'\'/{\\textbf \1}/sg;
            $part =~ s/%%(.*?)%%/\\strike{\1}/sg;
            #$part =~ s/\&?COLOR\(.*?\){(.*?)};/{\\textbf \1}/sig;
            #$part =~ s/\&?SIZE\(.*?\){(.*?)};/\1/sig;
            $part =~ s/\&?COLOR\(.*?\)\\{(.*?)\\};/{\\textbf \1}/sig;
            $part =~ s/\&?SIZE\(.*?\)\\{(.*?)\\};/\1/sig;
            $part =~ s/^\s*#(\S*?)(\(.*?\))?/(\1 IS NOT SUPPORTED)/mg;
            $part =~ s/&(\S*?)(\(.*?\))?;/(\1 IS NOT SUPPORTED)/sg;

            $part =~ s/_/\\_/sg;
            $part =~ s/#/\\#/sg;
            $part =~ s/%/\\%/sg;
            $part =~ s/&/\\&/sg;
            $part =~ s/~/\\textasciitilde{}/sg;
            $part =~ s/\^/\\textasciicircum{}/sg;
            $part =~ s/</\$<\$/sg;
            $part =~ s/>/\$>\$/sg;

            $out .= $part;
        }

        $math ^= 1;
    }

    return $out;
}

sub encode_utf8_hex {
    my ($str) = @_;
    $str =~ s/(.)/unpack('H2', $1)/eg;
    $str =~ tr/abcdef/ABCDEF/;
    return $str;
}

sub decode_utf8_hex {
    my ($str) = @_;
    $str =~ s/([0-9A-F][0-9A-F])/pack('H2', $1)/eg;
    return $str;
}

sub read_file {
    my ($file) = @_;
    open(IN, $file) or die $file;
    my $text = join('', <IN>);
    close(IN);
    return $text;
}
