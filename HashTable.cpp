#include <iostream>

using namespace std;

class HashTable{

   private:
    struct Hash{
       string key;
       string val;
    };
    Hash **tab;
   public:
    HashTable(){}
    HashTable(int n);
    void insert(string,string);
    void search(string);
    unsigned int h1(unsigned int);
    int size;
};
HashTable::HashTable(int n){
    size = n*1.4;
    tab = new Hash*[size];
    for (int i = 0; i < size; i++){
        tab[i] = NULL;
    }
}
unsigned int HashTable::h1(unsigned int hash){
    hash = hash * hash * 17389;
    return hash%size;
}
void HashTable::insert(string klucz, string wart){
    unsigned long hash = h1((int)(klucz[0]*klucz[(klucz.length()-1)/2]));
    while(tab[hash]!=NULL){
        hash = hash+1;
    }
    tab[hash] = new Hash();
    tab[hash]->key = klucz;
    tab[hash]->val = wart;

}
void HashTable::search(string klucz){
    unsigned long hash = h1((int)(klucz[0]*klucz[(klucz.length()-1)/2]));
    while (tab[hash] != NULL && tab[hash]->key != klucz){
        hash = hash+1;
    }
    if (tab[hash] == NULL)
       cout << "-\n";
    else
        cout <<  tab[hash]->val << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    int n;

    string nazwa, miejsce;
    char c;
    cin >> n;
    HashTable h(n);
    for(int i = 0; i < n; i++){
        cin >> c;
        if(c == 'A'){
            cin >> nazwa >> miejsce;
            h.insert(nazwa,miejsce);
        }
        else{
            cin >> nazwa;
            h.search(nazwa);
        }
    }
}
