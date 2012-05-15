/*
 * UVA 10476 Spam or Not Spam
 * 2005-08-02
 * by nya
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <cmath>

#define CHARACTERS 96
#define STATS (CHARACTERS*CHARACTERS*CHARACTERS)

typedef long long int integer;
typedef long double decimal;
struct Stat {
    int freq[STATS];
    integer sqsum;
};

const double EP = 1.0e-10;

bool readMail(std::string& line) {
    std::getline(std::cin, line);
    return (line != "ENDMESSAGE");
}

inline int tocode(char c) {
    return (int)(c - 32);
}

void clear_stat(Stat& stat) {
    std::fill(stat.freq, stat.freq+STATS, 0);
}

void make_stat(Stat& stat, const std::string& mail) {
    if (mail.size() >= 3) {
        int code = tocode(mail[0])*CHARACTERS+tocode(mail[1]);
        for(int i=2; i<(int)mail.size(); i++) {
            code = code*CHARACTERS%STATS + tocode(mail[i]);
            stat.freq[code]++;
            //std::printf("[%s] ", mail.substr(i-2, 3).c_str());
        }
    }
    //std::printf("\n");
}

void finish_stat(Stat& stat) {
    stat.sqsum = std::inner_product(stat.freq, stat.freq+STATS, stat.freq, (integer)0);
}

double my_distance(const Stat& a, const Stat& b) {
    return ( (double)std::inner_product(a.freq, a.freq+STATS, b.freq, (integer)0) /
             std::sqrt( (double)a.sqsum * (double)b.sqsum ) );
}

Stat spam, nonspam, mail;

int main() {
    std::string line;

    for(int iCase=0; ; iCase++) {
        std::getline(std::cin, line);
        int nSpams, nNonSpams, nClassifies;

        {
            std::istringstream is(line);
            is >> nSpams >> nNonSpams >> nClassifies;
        }

        if (nSpams == 0 && nNonSpams == 0 && nClassifies == 0)
            break;

        clear_stat(spam);
        clear_stat(nonspam);
        for(int i=0; i<nSpams; i++) {
            while(readMail(line))
                make_stat(spam, line);
        }
        for(int i=0; i<nNonSpams; i++) {
            while(readMail(line))
                make_stat(nonspam, line);
        }
        finish_stat(spam);
        finish_stat(nonspam);

        std::printf("Set %d:\n", iCase+1);
        for(int i=0; i<nClassifies; i++) {
            clear_stat(mail);
            while(readMail(line))
                make_stat(mail, line);
            finish_stat(mail);

            double spam_similarity = my_distance(spam, mail);
            double nonspam_similarity = my_distance(nonspam, mail);
            std::printf("%.05f %.05f\n", spam_similarity, nonspam_similarity);
            std::printf("%s\n", (spam_similarity > nonspam_similarity + EP ? "spam" : "non-spam") );
        }

    }
    return 0;
}
