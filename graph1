#include <iostream>

using namespace std;

class Graf{
private:
    int n;
    int n_lst;
    int *kolejka;
    struct sasiad{
        int numer;
        double prowizja1;
        double prowizja2;
        sasiad *nastepny;
    };
    struct wierzcholek{
        double suma1;
        double suma2;
        bool bajtcoin;
        sasiad *sasiedzi;
    };
    wierzcholek *tab;
    void push_lst(int);
    int find1();
    int find2();
    void pop(int);
    bool empty();
public:
    Graf(int, bool*, int);
    Graf(){}
    void push(int , int, double, double);
    void bfs1(int );
    void bfs2(int );
    void bfs3(int );
    void znajdz(int);
};
void Graf::push_lst(int x){
    kolejka[n_lst] = x;
    n_lst++;
}
void Graf::pop(int x){
    for(int i = 0; i < n_lst; i++){
        if(kolejka[i] == x){
            for(int j = i; j < n_lst-1; j++){
                kolejka[j] = kolejka[j+1];
            }
            n_lst--;
        }
    }
}
int Graf::find1(){
    int max = 0;
    int max_index;
    for(int i = 0; i < n_lst; i++){
        if(tab[kolejka[i]].suma1 > max){
            max = tab[i].suma1;
            max_index = i;
        }
    }
    return kolejka[max_index];
}

int Graf::find2(){
    int max = 0;
    int max_index;
    for(int i = 0; i < n_lst; i++){
        if(tab[kolejka[i]].suma2 > max){
            max = tab[i].suma2;
            max_index = i;
        }
    }
    return kolejka[max_index];
}
bool Graf::empty(){
    if(n_lst == 0)
        return true;
    return false;
}
Graf::Graf(int n, bool *czy_bc, int m){
    this->n = n;
    tab = new wierzcholek[n];
    for(int i = 0; i < n; i++){
        tab[i].sasiedzi = NULL;
        tab[i].suma1 = 0;
        tab[i].suma2 = 0;
        tab[i].bajtcoin = czy_bc[i];
    }
    n_lst = 0;
    kolejka = new int[m];
}
void Graf::bfs1(int v){
    n_lst = 0;
    sasiad *z_p;
    tab[v].suma1 = 100000;
    push_lst(v);
    while(!empty()){
        v = find1();
        pop(v);
        z_p = tab[v].sasiedzi;
        while(z_p != NULL){
            if( tab[v].suma1 - (tab[v].suma1 * z_p->prowizja1) > tab[z_p->numer].suma1){
                tab[z_p->numer].suma1 = tab[v].suma1 - (tab[v].suma1 * z_p->prowizja1);
                push_lst(z_p->numer);
            }
            z_p = z_p->nastepny;
        }
    }
}

void Graf::bfs2(int v){
    n_lst = 0;
    tab[v].suma2 = 100000;
    push_lst(v);
    sasiad *z_p;
    while(!empty()){
        v = find2();
        pop(v);
        z_p = tab[v].sasiedzi;
        while(z_p != NULL){
            if(tab[v].suma2 - (tab[v].suma2 * z_p->prowizja2) > tab[z_p->numer].suma2){
                tab[z_p->numer].suma2 = tab[v].suma2 - (tab[v].suma2 * z_p->prowizja2);
                push_lst(z_p->numer);
            }
            z_p = z_p->nastepny;
        }
    }
}

void Graf::bfs3(int v){
    n_lst = 0;
    tab[v].suma1 *= 1.2;
    push_lst(v);
    sasiad *z_p;
    while(!empty()){
        v = find1();
        pop(v);
        z_p = tab[v].sasiedzi;
        while(z_p != NULL){
            if(tab[v].suma1 - (tab[v].suma1 * z_p->prowizja1) > tab[z_p->numer].suma1){
                tab[z_p->numer].suma1 = tab[v].suma1 - (tab[v].suma1 * z_p->prowizja1);
                push_lst(z_p->numer);
            }
            z_p = z_p->nastepny;
        }
    }
}

void Graf::znajdz(int s){
    bfs1(s);
    bfs2(s);
    int max = 0;
    int max_index;
    for(int i = 0 ; i< n; i++){
        if(tab[i].bajtcoin && tab[i].suma1 + tab[i].suma2 > max){
            max = tab[i].suma1 + tab[i].suma2;
            max_index = i;
        }
    }
    for(int i = 0 ; i< n; i++){
        if(i != max_index){
            tab[i].suma1 = 0;
        }
    }
    bfs3(max_index);
    cout << tab[s].suma1;
}

void Graf::push(int x, int y, double p1, double p2){
    sasiad *s = new sasiad;
    s->numer = y;
    s->prowizja1 = p1;
    s->prowizja2 = p2;
    s->nastepny = tab[x].sasiedzi;
    tab[x].sasiedzi = s;

    s = new sasiad;
    s->numer = x;
    s->prowizja1 = p2;
    s->prowizja2 = p1;
    s->nastepny = tab[y].sasiedzi;
    tab[y].sasiedzi = s;

}
int main(){
    int il_gield, il_krawedzi, wiodaca;
    cin >> il_gield;
    bool *status = new bool[il_gield];
    for(int i = 0; i < il_gield; i++){
        cin >> status[i];
    }
    cin >> il_krawedzi;
    Graf g(il_gield, status, il_krawedzi);
    int gielda1, gielda2;
    double prow1, prow2;
    for(int i = 0; i < il_krawedzi; i++){
        cin >> gielda1 >> gielda2;
        cin >> prow1 >> prow2;
        g.push(gielda1, gielda2, prow1, prow2);
    }
    cin >> wiodaca;
    g.znajdz(wiodaca);
}
