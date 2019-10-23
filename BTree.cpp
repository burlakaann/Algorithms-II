#include <iostream>
#include <queue>

using namespace std;

class bst{
public:
    struct atrakc{
        double klucz;
        bool kolor;
        atrakc *l_syn;
        atrakc *p_syn;
        atrakc *ojciec;
        string pseud;
    };
    atrakc *root;
public:
    bst();
    atrakc* search1(double);
    void insert1(double, string);
};
bst::bst(){
    root = NULL;
}

bst::atrakc* bst::search1(double atr){
    atrakc *z_p = root;
    if(z_p != NULL){
        while(z_p->p_syn != NULL){
            z_p = z_p->p_syn;
        }
    }
    else{
        return z_p;
    }

    if(z_p->klucz >= atr){
        return z_p;
    }
    else{
        return NULL;
    }
}
void bst::insert1(double atr, string pseud){
    atrakc *v1, *v2;
    atrakc *poprzedni;
    v2 = root;
    if (root == NULL){
        v1 = new atrakc;
        v1->ojciec = NULL;
        v1->pseud = pseud;
        v1->l_syn = v1->p_syn = NULL;
        v1->klucz = atr;
        v1->kolor = true;
        root = v1;
    }
    else{
        while(v2 != NULL && v2->klucz != atr){
            poprzedni = v2;
            if(v2->klucz < atr)
                v2 = v2->p_syn;
            else
                v2 = v2->l_syn;
        }
        if(v2 == NULL){
            v1 = new atrakc;
            v1->l_syn = v1->p_syn = NULL;
            v1->klucz = atr;
            v1->kolor = true;
            v1->ojciec = poprzedni;
            v1->pseud = pseud;
            if(poprzedni->klucz > v1->klucz){
                poprzedni->l_syn = v1;
            }
            else if(poprzedni->klucz < v1->klucz){
                poprzedni->p_syn = v1;
            }
            else{
                v1->pseud = pseud;
            }

        }
        else{
            v2->pseud = pseud;
        }
    }
}

class BTree{
private:
    struct wezel{
        int *klucze;
        wezel **dzieci;
        bool czy_lisc;
        int liczba_kluczy;
        bst **wartosc;
    };
    wezel *korzen;
public:
    BTree();
    wezel* konstruktor();
    wezel*getRoot();
    void search(int, double);
    void insert(int, double, string);
    wezel* split(wezel*, wezel*);
};
BTree::BTree(){
    korzen = NULL;
}
BTree::wezel* BTree::getRoot(){
    return korzen;
}
BTree::wezel* BTree::konstruktor(){
    wezel * v = new wezel;

    v->czy_lisc = true;
    v->klucze = new int[19];
    v->liczba_kluczy = 0;
    v->wartosc = new bst*[19];
    v->dzieci = new wezel*[20];

    for (int i = 0; i < 20; i++){
        v->dzieci[i] = NULL;
    }
    return v;
}
BTree::wezel* BTree::split(wezel* v, wezel *ojciec){
    wezel *nowy;
    int i;
    wezel *z_p;
    if(v == korzen){
        nowy = konstruktor();
        nowy->klucze[nowy->liczba_kluczy] = v->klucze[9];
        nowy->wartosc[nowy->liczba_kluczy] = v->wartosc[9];
        nowy->liczba_kluczy++;
        nowy->czy_lisc = false;
        z_p = konstruktor();
        z_p->czy_lisc = v->czy_lisc;
        for(int i = 10; i < 19; i++){
            z_p->klucze[i-10] = v->klucze[i];
            z_p->wartosc[i-10] = v->wartosc[i];

        }
            for(int i = 10; i < 20; i++){
                z_p->dzieci[i-10] = v->dzieci[i];
                v->dzieci[i] = NULL;
            }
        z_p->liczba_kluczy = 9;
        v->liczba_kluczy = 9;
        nowy->dzieci[0] = v;
        nowy->dzieci[1] = z_p;
        nowy->liczba_kluczy = 1;
        korzen = nowy;
        return nowy;
    }
    else{
        nowy = konstruktor();
        nowy->czy_lisc = v->czy_lisc;
        for(int j = 0; j < 9; j++){
            nowy->klucze[j] = v->klucze[j+10];
            nowy->wartosc[j] = v->wartosc[j+10];
        }
        nowy->liczba_kluczy = 9;
        if(v->czy_lisc == false){
            for(int j = 0; j < 10; j++){
                nowy->dzieci[j] = v->dzieci[j+10];
                v->dzieci[j+10] = NULL;
            }
        }
        for( i = 0 ; i < ojciec->liczba_kluczy && v->klucze[9] > ojciec->klucze[i]; i++){}

        for(int j = ojciec->liczba_kluczy; j >= i+1; j--){
            ojciec->dzieci[j+1] = ojciec->dzieci[j];
        }
        ojciec->dzieci[i+1] = nowy;
        for(int j = ojciec->liczba_kluczy-1; j >= i; j--){
            ojciec->klucze[j+1] = ojciec->klucze[j];
            ojciec->wartosc[j+1] = ojciec->wartosc[j];
        }
        ojciec->klucze[i] = v->klucze[9];
        ojciec->wartosc[i] = v->wartosc[9];
        ojciec->liczba_kluczy++;
        v->liczba_kluczy = 9;
        return ojciec;
    }
}

void BTree::insert(int key, double wspol, string pseud){

    wezel *v = korzen;
    wezel *ojciec = NULL;
    int i;
    if(v == NULL){
        v = konstruktor();
        v->klucze[0] = key;
        v->liczba_kluczy++;
        v->wartosc[0] = new bst;
        v->wartosc[0]->insert1(wspol, pseud);
        korzen = v;
    }
    else{
        while(v != NULL && v->czy_lisc == false){
            if(v->liczba_kluczy == 19){
                v = split(v, ojciec);
            }
            for( i = 0 ; i < v->liczba_kluczy && key > v->klucze[i]; i++){}
            if(v->klucze[i] == key){
                v->wartosc[i]->insert1(wspol, pseud);
                return;
            }
            else{
                ojciec = v;
                v = v->dzieci[i];
            }
        }
        if(v->liczba_kluczy == 19){
            v = split(v, ojciec);
            for( i = 0 ; i < v->liczba_kluczy && key > v->klucze[i]; i++){}
            if(v->klucze[i] == key){
                v->wartosc[i]->insert1(wspol, pseud);
                return;
            }
            else{
                ojciec = v;
                v = v->dzieci[i];
            }
        }

        for( i = 0 ; i < v->liczba_kluczy && key > v->klucze[i]; i++){}

        if( v->klucze[i] == key ){
            v->wartosc[i]->insert1(wspol,pseud);
        }
        else{
            int k;
            for(k = v->liczba_kluczy; k > i; k-- ){
                v->klucze[k] = v->klucze[k-1];
                v->wartosc[k] = v->wartosc[k-1];
            }
            v->liczba_kluczy++;
            v->klucze[i] = key;
            v->wartosc[i] = new bst;
            v->wartosc[i]->insert1(wspol, pseud);
        }
    }
}

void BTree::search(int x, double atrakc){
    wezel *z_p = korzen;
    wezel *szukany = NULL;
    int i,j;
    while(z_p != NULL){
        for( i = 0 ; i < z_p->liczba_kluczy && x > z_p->klucze[i];i++){}

        if(z_p->klucze[i] != x){
            z_p = z_p->dzieci[i];
        }else{
            szukany = z_p;
            break;
        }
    }


    bst::atrakc *s ;

    if(szukany == NULL){
        cout << "-\n";
    }
    else{
        s = szukany->wartosc[i]->search1(atrakc);
        if(s==NULL){
            cout << "-\n";
        }
        else{
            cout << s->pseud << "\n";
        }
    }

}
double oblicz_wspol(double x, int y){
    return x/5*(int)(y/1000);
}
int main(){
ios_base::sync_with_stdio(false);
bst bs;
BTree bt;
int il_operacji;
cin >> il_operacji;
char ch;
double p1, atrakcyjnosc;
int p2, koszt, il_pien;
string pseudonim;
for(int i = 0; i < il_operacji; i++){
    cin >> ch;
    if(ch == 'A'){
        cin >> p1;
        cin >> p2;
        cin >> koszt;
        cin >> pseudonim;
        bt.insert(koszt, oblicz_wspol(p1,p2), pseudonim);
    }
    else{
        cin >> il_pien >> atrakcyjnosc;
        bt.search(il_pien, atrakcyjnosc);
    }
}
}
