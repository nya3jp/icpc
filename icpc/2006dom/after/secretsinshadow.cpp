#include<iostream>
#include<complex>
#include<vector>

using namespace std;

#define PI 3.1415926535897932384626433832795028841971L
#define DELTA 0.000000000001L

//実は double で余裕みたい

typedef long double ld;
typedef complex<ld> cld;

//定義域に移す
ld trim(ld t){
	if(t < -0.5 * PI){
		return(t + PI);
	}
	if(t > 0.5 * PI){
		return(t - PI);
	}
	return(t);
}

int main(void){
	while(true){
		int n;
		
		//入力
		cin >> n;
		if(n == 0)break;
		cld p[n];
		for(int i=0;i<n;i++){
			ld x,y;
			cin >> x >> y;
			p[i] = cld(x, y);
		}
		
		//円の位置関係が変わらない区間の生成
		vector<ld> theta;
		theta.push_back(-PI/2);
		theta.push_back( PI/2);
		
		ld xdiff[] = {-2.0L, 0.0L, 2.0L};
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				cld v = p[i] - p[j];
				for(int k=0;k<3;k++){
					ld y = sqrt(norm(v) - xdiff[k] * xdiff[k]);
					ld t = trim(arg(cld(xdiff[k], y) / v));
					theta.push_back(t);
				}
			}
		}
		sort(theta.begin(), theta.end());
		
		ld maxlen = -1.0;
		ld maxt;
		ld minlen = 10000.0;
		ld mint;
		
		for(int i=1; i<theta.size(); i++){
			
			ld tb = theta[i - 1];
			ld te = theta[i];
			ld tc = 0.5L * (tb + te);
			
			//回転
			cld rot = cld(cos(tc), sin(tc));
			pair<ld, int> xandindex[n];
			for(int j=0;j<n;j++){
				cld prot = p[j] * rot;
				xandindex[j] = make_pair(real(prot), j);
			}
			sort(xandindex, xandindex + n);
			
			ld length = 0.0L;
			cld factor = cld(0.0L, 0.0L);
			
			//連結領域の算出
			for(int i=0;i<n;){
				int leftindex = i;
				int rightindex = i;
				while(rightindex + 1 < n && xandindex[rightindex + 1].first - xandindex[rightindex].first < 2.0L){
					rightindex++;
				}
				length += 2.0L;
				i = rightindex + 1;
				
				if(leftindex == rightindex)continue;
				
				cld pr = p[xandindex[rightindex].second];
				cld pl = p[xandindex[leftindex].second];
				
				factor += (pr - pl);
			}
			
			//区間内での最大値/最小値の計算
			vector<pair<ld,ld> > lengthandtheta;
			
			cld v;
			v = cld(cos(tb), sin(tb));
			lengthandtheta.push_back(make_pair(length + real(v * factor), tb));
			
			v = cld(cos(te), sin(te));
			lengthandtheta.push_back(make_pair(length + real(v * factor), te));
			
			ld t = trim(arg(conj(factor)));
			if(tb < t && t < te){
				lengthandtheta.push_back(make_pair(length + abs(factor), t));
			}
			
			//全体の最大値/最小値のアップデート
			for(int i=0;i<lengthandtheta.size();i++){
				ld len = lengthandtheta[i].first;
				ld t = lengthandtheta[i].second;
				if(maxlen < len){
					maxlen = len;
					maxt = t;
				}
				if(minlen > len){
					minlen = len;
					mint = t;
				}
			}
		}
		printf("%.10Lf\n", mint + 0.5*PI);
		printf("%.10Lf\n", maxt + 0.5*PI);
	}
}
