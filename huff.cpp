#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct node{
  struct node *left, *right;
	int freq;
	char c;
  string code;
  int indx;
};

node n[128];
int ni = 0;
int fcount = 0;

void createnode(node n[], int freq, char c){
  n[ni].freq = freq;
  n[ni].c = c;
  n[ni].indx = ni;
  ni++;
}

void countfreq(string str){
  int freq[256] = {0};
  int i;

  for (i = 0; str[i] != '\0'; i++){
    freq[str[i]]++;
  }

  for(i = 0; i < 256; i++){
    if(freq[i] != 0){
      //cout << (char)i << " : " << freq[i] << endl;
      createnode(n, freq[i], i);
      fcount++;
    }
  }
}

void sortnodes(){
  int i, j;
  node temp;
  for(i = 0; i < fcount; i++){
		for(j = i + 1; j < fcount; j++){
			if(n[i].freq > n[j].freq){
				temp  = n[i];
				n[i] = n[j];
				n[j] = temp;
			}
		}
	}
}

void printnodes(){
  int j;
  for (j = 0; n[j].freq != '\0'; j++){
    cout << "[" << n[j].indx << "] " << n[j].c << " : " << n[j].freq << " : " << n[j].code << endl;
  }
}

int createTree(string str){
  int i;
  int st = fcount;
  for (i = 0; n[i].freq != str.length(); i++){
    n[fcount].freq = n[i].freq + n[i+1].freq;
    n[fcount].c = '^';
    n[fcount].indx = fcount;
    n[fcount].left = &n[i];
    n[fcount].right = &n[i+1];
    //cout << n[fcount].left->freq << " - " << n[fcount].right->freq << endl;
    fcount++;
    i++;
  }
  return st;
}

string compress(int st, string str){
  //cout << st << endl;
  fcount--; //fcount = 14 now
  string s;
  int tempind;
  int tempfam;
  int dnodes;

  int i;
  for (i = 0; i < st; i++){
    tempind = i;
    tempfam = st;
    dnodes = 0;
    while(tempind < fcount){
      if (dnodes % 2 == 0){
        if (tempind % 2 == 0){
          tempind = tempind + (tempfam - ((tempind - dnodes)/2));
          dnodes = dnodes + tempfam;
          tempfam = (tempfam / 2);
          n[i].code += "0";
        }
        else{
          tempind = tempind + (tempfam - ((tempind - dnodes)/2)) - 1;
          dnodes = dnodes + tempfam;
          tempfam = (tempfam / 2);
          n[i].code += "1";
        }
      }
      else{
        if (tempind % 2 == 0){
          tempind = tempind + (tempfam - ((tempind - dnodes)/2));
          dnodes = dnodes + tempfam;
          tempfam = (tempfam / 2);
          n[i].code += "1";
        }
        else{
          tempind = tempind + (tempfam - ((tempind - dnodes)/2)) - 1;
          dnodes = dnodes + tempfam;
          tempfam = (tempfam / 2);
          n[i].code += "0";
        }
      }
    }
  }

  int j;
  string comp;
  for (j = 0; j < st; j++){
    reverse(n[j].code.begin(), n[j].code.end());
  }
  //cout << n[3].code << endl;

  int k, f;
  for (k = 0; k < str.length(); k++){
    for (f = 0; f < st; f++){
      if(str[k] == n[f].c){
        comp += n[f].code;
        break;
      }
    }
  }
  cout << "Compressed Message" << endl;
  cout << comp << endl;

  return comp;
}

void decompress(string comp){
  int i;
  string decomp;
  for (i = 0; i < comp.length(); i=i){
    node temp = n[fcount];
    while (temp.left){
      if(comp[i] == '0'){
        temp = *(temp.left);
        i++;
      }
      else{
        temp = *(temp.right);
        i++;
      }
    }
    decomp += temp.c;
  }
  cout << "Decompressed Message" << endl;
  cout << decomp << endl;
}

int main(){
  string str = "hello world";
  countfreq(str);
  sortnodes();
  ni = 0;
  int st = createTree(str);
  string comp = compress(st, str);
  decompress(comp);
  printnodes();

  return 0;
}
