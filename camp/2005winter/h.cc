#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define EP 1.0e-8

struct Reward {
    double rate;
    double remain;

    friend bool operator<(const Reward& a, const Reward& b) {
        return (a.rate < b.rate);
    }
};

struct Job {
    double cost;
    double limit;
    Reward reward;

    friend bool operator<(const Job& a, const Job& b) {
        return (a.limit < b.limit);
    }
};


int main() {
    ifstream fin("lazy.in");

    int n;
    while(fin >> n && n != 0) {

        vector<Job> jobs(n);
        for(int i = 0; i < n; i++) {
            Job& job = jobs[i];
            double a, b, d;
            fin >> a >> b >> d;
            job.cost = b;
            job.limit = d;
            job.reward.rate = a;
            job.reward.remain = b/a;
        }
        sort(jobs.begin(), jobs.end());

        priority_queue<Reward> q;
        double cost = 0;
        double total_reward = 0;
        for(int i = 0; i < n; i++) {

            const Job& job = jobs[i];
            cost += job.cost;

            q.push(job.reward);

            while(cost > job.limit+EP) {
                Reward r = q.top();
                q.pop();

                double accel = (cost - job.limit) / r.rate;
                accel = min(accel, r.remain);

                cost -= accel * r.rate;
                r.remain -= accel;
                total_reward += accel;

                if (r.remain > 0+EP)
                    q.push(r);
            }
        }

        printf("%.3f\n", total_reward);
    }

    return 0;
}




