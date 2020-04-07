/*  SUBXOR - SubXor
no tags 
A straightforward question. Given an array of positive integers you have to print the number of subarrays whose XOR is less than K. Subarrays are defined as a sequence of continuous elements Ai, Ai+1, ..., Aj . XOR of a subarray is defined as Ai ^ Ai+1 ^ ... ^ Aj. Symbol ^ is Exclusive Or. You can read more about it here:
http://en.wikipedia.org/wiki/Exclusive_or

Input Format:
First line contains T, the number of test cases. Each of the test case consists of N and K in one line, followed by N space separated integers in next line.

Output Format:
For each test case, print the required answer.

Constraints:
1 ≤ T ≤ 10
1 ≤ N ≤ 10^5
1 ≤ A[i] ≤ 10^5
1 ≤ K ≤ 10^6
Sum of N over all testcases will not exceed 10^5.

Sample Input:
1
5 2
4 1 3 2 7	
Sample Output:
3
Explanation:
Only subarrays satisfying the conditions are [1], [1,3,2] and [3,2].
*/

#include<bits/stdc++.h> 
using namespace std;
typedef long long int ll;
#define MOD 1000000007
#define fo(i,k,n) for(int i=k;i<=n;++i)
#define endl '\n'
class trienode{
	public:
	ll children=0;
	trienode* left;
	trienode* right;
};
void insert(trienode* head,ll val){
	trienode* curr = head;
	for(ll i=31;i>=0;i--){
		ll b = (val>>i)&1;
		if(b==0){
			if(!curr->left){
				curr->left = new trienode();
			}
			//curr->children++;
			curr = curr->left;
		}else{
			if(!curr->right){
				curr->right = new trienode();
			}
			//curr->children++;
			curr = curr->right;
		}
		curr->children++;
	}
}
int findAns(trienode* head,ll val,ll k){
	trienode* curr = head;
	int ans=0;
	for(ll i=31;i>=0;i--){
		ll kb = (k>>i)&1 ;
		ll vb = (val>>i)&1;
		if(kb==1 && vb==1){
			if(curr->right) ans += curr->right->children;
			if(curr->left)curr=curr->left;
			else break;
		}else if(kb==1 && vb==0){
			if(curr->left) ans+= curr->left->children;
			if(curr->right) curr = curr->right;
			else break;
		}else if(kb==0 && vb==1){
			if(curr->right) curr = curr->right;
			else break;
		}else if(kb==0 && vb==0){
			if(curr->left) curr = curr->left;
			else break;
		}
	}
	return ans;
}
void solve(){
	ll n,k;
	cin>>n>>k;
	ll* arr = new ll[n];
	fo(i,0,n-1) cin>>arr[i];
	trienode* head = new trienode();
	ll prexor=0,curxor,ans =0;
	fo(i,0,n-1){
		insert(head,prexor);
		curxor = prexor^arr[i];
		ans += findAns(head,curxor,k);
		prexor = curxor;
	}
	cout<<ans<<endl;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
