#include<cstdio>
#include<algorithm>
using namespace std;
int k, n, temp;
struct node{
	int data;
	struct node *l, *r;
} * root;
void Insert(node * & root, int v){
	if(root == NULL){
		root = new node;
		root->data = v;
		root->l = root->r = NULL;
		return;
	}
	if(abs(root->data) <= abs(v)) Insert(root->l, v);
	else Insert(root->r, v);
}

int getnum(node * root){
	if(root == NULL) return 0;
	int l = getnum(root->l);
	int r = getnum(root->r);
	return  root->data > 0? max(l, r) + 1 : max(l, r);
} 


bool judge1(node * root){
	if(root == NULL ) return true;
	if(root->data < 0){
		if(root->l != NULL && root->l->data < 0) return false;
		if(root->r != NULL && root->r->data < 0) return false;
	}
	return judge1(root->l) && judge1(root->r);
}
bool judge2(node * root){
	if(root == NULL) return true;
	int l = getnum(root->l);
	int r = getnum(root->r);
	if(l != r) return false;
	return judge2(root->l) && judge2(root->r);
}





int main(){
	scanf("%d", &k);
	for(int i = 0; i < k; ++i){
		scanf("%d", &n);
		for(int j = 0; j < n; ++j){
			scanf("%d", &temp);
			Insert(root, temp);
		}
		if(root->data > 0 && judge1(root) && judge2(root)) printf("Yes\n");
		else printf("No\n");
		root = NULL;
	}
	return 0;
}