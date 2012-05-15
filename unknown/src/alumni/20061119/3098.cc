#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(),(c).end()

using namespace std;

int main()
{
  string line;
  while (true) {
    // 辞書を読み込み
    vector<string> words;
    while(getline(cin, line)) {
      if (line == "#")
        goto end;
      if (line == "*")
        break;
      words.push_back(line);
    }
    sort(ALL(words));

    // クエリーを読み込み
    vector<string> queries;
    while(getline(cin, line)) {
      if (line == "**")
        break;
      queries.push_back(line);
    }

    /*
    REP(i, words.size())
      cout << "word = " << words[i] << endl;
    REP(i, queries.size())
      cout << "query = " << queries[i] << endl;
    */

    // dictを構築
    vector<vector<int> > dict;
    REP(i, words.size()) {
      vector<int> zeros(26, 0);

      string word = words[i];
      REP(j, word.size()) {
        zeros[word[j] - 'a'] = 1;
      }

      dict.push_back(zeros);
    }

    // queryを1つづつしょり
    REP(i, queries.size()) {
      string query = queries[i];
      istringstream iss(query);
      vector<string> parts;
      string s;
      while(getline(iss, s, '|'))
        parts.push_back(s);

      int foundidx = INT_MAX;

      // partsを１つづつ処理
      REP(j, parts.size()) {
        // マイナス、プラスを操作
        vector<int> partdict(26, 0);
        string part = parts[j];
        REP(k, part.size()) {
          if (part[k] == '-') {
            if (partdict[part[k + 1] - 'a'] == 1)
              partdict.assign(26, -1);
            else
              partdict[part[k + 1] - 'a'] = -1;
          }
          if (part[k] == '+') {
            if (partdict[part[k + 1] - 'a'] == -1)
              partdict.assign(26, -1);
            else
              partdict[part[k + 1] - 'a'] = 1;
          }
        }

        // 最初のオアクエリを取り出す
        string orquery = "";
        REP(k, part.size()) {
          if (part[k] == '-' || part[k] == '+')
            break;
          else
            orquery += part[k];
        }

        //      cout << "orquery = " << orquery << endl;

        // オアクエリを見て処理を行う
        REP(k, orquery.size()) {
          vector<int> orpartdict = partdict;

          if (orpartdict[orquery[k] - 'a'] == -1)
            orpartdict.assign(26, -1);
          else
            orpartdict[orquery[k] - 'a'] = 1;

          REP(iword, words.size()) {
            string word = words[iword];
            vector<int> worddict = dict[iword];
            bool isMatch = true;
            REP(l, 26) {
              if ((orpartdict[l] == 1 && worddict[l] == 0)
                  || (orpartdict[l] == -1 && worddict[l] == 1))
                isMatch = false;
            }

            if (isMatch)
              foundidx <?= iword;
          }
        }
      }

      if (foundidx == INT_MAX)
        cout << "NONE" << endl;
      else
        cout << words[foundidx] << endl;
    }
    cout << "$" << endl;
  }

 end:
  return 0;
}
