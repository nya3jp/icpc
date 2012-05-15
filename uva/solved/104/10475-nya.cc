/*
 * UVA 10475 Help the Leaders
 * 2005-08-02
 * by nya
 */

#include <cstdio>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

typedef std::vector< std::list<int> > Graph;

bool topic_sorter(const std::string& a, const std::string& b) {
    if (a.size() != b.size())
        return (a.size() > b.size());
    return (a < b);
}

void toupper(char* p) {
    while(*p != '\0') {
        *p = std::toupper(*p);
        p++;
    }
}

void search(std::vector<int>& groupTopics, std::vector<int>& visited, int iNextTopic, const Graph& g, const std::vector<std::string>& topics, const int nGroupTopics) {
    int iTopic = (int)groupTopics.size();
    if (iTopic == nGroupTopics) {
        for(int i=0; i<nGroupTopics; i++) {
            if (i > 0)
                std::printf(" ");
            std::printf("%s", topics[ groupTopics[i] ].c_str() );
        }
        std::printf("\n");
    }
    else {
        for(int i=iNextTopic; i<(int)topics.size(); i++) {
            if (visited[i] == 0) {
                for(Graph::value_type::const_iterator it = g[i].begin();
                    it != g[i].end();
                    ++it) {
                    visited[*it]++;
                }
                groupTopics.push_back(i);
                search(groupTopics, visited, i+1, g, topics, nGroupTopics);
                for(Graph::value_type::const_iterator it = g[i].begin();
                    it != g[i].end();
                    ++it) {
                    visited[*it]--;
                }
                groupTopics.pop_back();
            }
        }
    }
}

int main() {

    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase=0; iCase<nCases; iCase++) {

        char buf[16], buf1[16], buf2[16];
        int nTopics, nRejects, nGroupTopics;

        std::scanf("%d%d%d", &nTopics, &nRejects, &nGroupTopics);

        std::vector<std::string> topics;
        for(int i=0; i<nTopics; i++) {
            std::scanf("%s", buf);
            toupper(buf);
            topics.push_back( std::string(buf) );
        }
        std::sort(topics.begin(), topics.end(), topic_sorter);

        std::map< std::string, int > hTopics;
        for(int i=0; i<nTopics; i++)
            hTopics[topics[i]] = i;

        Graph g(nTopics);
        for(int i=0; i<nTopics; i++) {
            g[i].push_back(i);
        }
        for(int i=0; i<nRejects; i++) {
            std::scanf("%s%s", buf1, buf2);
            toupper(buf1);
            toupper(buf2);
            int iTopic1 = hTopics[std::string(buf1)];
            int iTopic2 = hTopics[std::string(buf2)];
            g[iTopic1].push_back(iTopic2);
            g[iTopic2].push_back(iTopic1);
        }

        std::printf("Set %d:\n", iCase+1);

        std::vector<int> groupTopics;
        std::vector<int> visited(nTopics, 0);
        search(groupTopics, visited, 0, g, topics, nGroupTopics);

        std::printf("\n");
    }
    return 0;
}
