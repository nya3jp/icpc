#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

#define MAX_PRIME 11000

bool isprime[MAX_PRIME+1];

std::vector<int> primes;

void make_prime_table() {
  std::fill(isprime, isprime+MAX_PRIME+1, true);
  isprime[0] = isprime[1] = false;
  for(int i=2; i<=MAX_PRIME; i++) {
    if (isprime[i]) {
      for(int j=i*i; j<=MAX_PRIME; j+=i)
	isprime[j] = false;
      primes.push_back(i);
    }
  }
}

int main() {
  make_prime_table();

  std::vector<int> sums;
  sums.push_back(0);
  std::copy(primes.begin(), primes.end(), std::back_inserter(sums));
  std::partial_sum(sums.begin(), sums.end(), sums.begin());

  //std::copy(sums.begin(), sums.end(), std::ostream_iterator<int>(std::cout, "\n"));

  std::ifstream fin("A.txt");

  int n;
  while(fin >> n && n != 0) {
    int c = 0;
    for(int i=1; i<(int)sums.size(); i++) {
      int t = sums[i] - n;
      if (std::binary_search(sums.begin(), sums.end(), t))
	c++;
    }
    std::cout << c << std::endl;
  }

  return 0;
}
