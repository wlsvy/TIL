/*
=========
첫번째 방법- stack 활용
=========
*/
long long candies(int n, vector<int> arr) {

    stack<int> st, rst;
    vector<long long> candyCnt(arr.size(), 0);

    for (int i = 0; i < arr.size(); ) {
        if (st.empty() || st.top() < arr[i]) {
            st.push(arr[i]);
            candyCnt[i] = st.size();
            i++;
            continue;
        }

        if (st.top() == arr[i]) {
            while (!st.empty()) st.pop();
            st.push(arr[i]);
            candyCnt[i] = st.size();

            i++;
            continue;
        }

        int j = i;
        while (arr[j - 1] > arr[j]) {
            j++;
            if (j >= arr.size())  break;
        }
        int next = --j;
        //cout << "next " << next << " i : " << i << endl;
        while (j >= i - 1) {
            rst.push(arr[j]);
            candyCnt[j] = max(candyCnt[j], (long long)rst.size());

            j--;
        }

        i = next;

        while (!st.empty()) st.pop();
        while (!rst.empty()) rst.pop();
    }

    long long sum = 0;
    for (auto c : candyCnt) {
        sum += c;
    }

    return sum;
}


/*
=========
두번째 방법- 배열을 정방향, 역방향으로 오르내리는 정도를 구하는 것
-이게 더 효율적
=========
*/

#include <cstdio>
#include <string>
using namespace std;

typedef long long ll;

int a[100005],b[100005];

inline int maxi(int x,int y) {
	return (x>y)?x:y;
}

int main() {
int i,j,n;
ll ans;

	scanf("%d",&n);
	for (i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	a[0]=a[1];
	a[n+1]=a[n];
	for (i=1;i<=n;++i) {
		if ((a[i]<=a[i+1]) && (a[i]<=a[i-1])) {
			b[i]=1;
			for (j=i-1;j && (a[j]>a[j+1]);--j) {
				b[j]=b[j+1]+1;
			}
			for (;i<n && (a[i+1]>a[i]);++i) {
				b[i+1]=b[i]+1;
			}
		}
	}
	ans=0;
	for (i=1;i<=n;++i) {
		if ((a[i]>a[i-1]) && (a[i]>a[i+1])) {
			b[i]=maxi(b[i-1],b[i+1])+1;
		}
		ans+=b[i];
	}
	printf("%Ld\n",ans);
	return 0;

}
