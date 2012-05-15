
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)

// int b[1000000];
// long long r = -1; a[1000000];
// int N = 1000000;

// int main(void) {
//   int n = 1, k, m;
//   for(;N;) {
//     b[N] = N;
//     a[N--] = 1;
//   }

//   for(; N <= 1000000; ){
//     for(k = 1; k < 2; k = b[++N])
//       r = a[N] += r;
//     for(n = N; n <= 1000000; n += k){
//       for(m=k-1; b[n]%k ? 0 : (a[n] *= m, b[n] /= m = k);)
// 	;
//     }
//   }
  
//   // a[n]
  
//   return 0;
// }


#define N 1000000
int b[N+1];
long long a[N+1];

int main(void) {
  REP(i, N+1){
    b[i] = i;
    a[i] = 1;
  }

  a[0] = 0;
  REP(k, N+1){
    if(b[k] < 2)
      continue;

    // k is prime
    for(int n = k; n <= N; n += k){
      a[n] *= k-1;
      b[n] /= k;
      while(b[n] % k == 0){
	a[n] *= k;
	b[n] /= k;
      }
    }
  }

  // now
  // a[n] == phi(n)
  // (b[n] == 1)
  
  return 0;
}
