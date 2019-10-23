#include <iostream>
#include <stdio.h>

using namespace std;

class Graf{
private:
    int n;
    int n_lst;
    struct sasiad{
        int numer;
        double prawdopod;
        sasiad *nastepny;
    };
    struct wierzcholek{
        bool czy_odw;
        sasiad *sasiedzi;
    };
    sasiad *kolejka;
    wierzcholek *tab;
    void push_lst(sasiad);
    sasiad find();
    void pop(sasiad);
    bool empty();
public:
    Graf(int, int);
    Graf(){}
    void push(int, int, double);
    double bfs();
};

Graf::sasiad Graf::find(){
    double max = 0;
    int max_index;
    for(int i = 0; i < n_lst; i++){
        if(kolejka[i].prawdopod > max){
            max = kolejka[i].prawdopod;
            max_index = i;
        }
    }
    return kolejka[max_index];
}
void Graf::push_lst(sasiad x){
    kolejka[n_lst] = x;
    n_lst++;
}
bool Graf::empty(){
    if(n_lst == 0)
        return true;
    return false;
}
void Graf::pop(sasiad x){
    for(int i = 0; i < n_lst; i++){
        if(kolejka[i].numer == x.numer){
            for(int j = i; j < n_lst-1; j++){
                kolejka[j] = kolejka[j+1];
            }
            n_lst--;
        }
    }
}
Graf::Graf(int n, int m){
    this->n = n;
    tab = new wierzcholek[n];

    for(int i = 0; i < n; i++){
        tab[i].sasiedzi  = NULL;
        tab[i].czy_odw = false;
    }
    n_lst = 0;
    kolejka = new sasiad[m];
}

void Graf::push(int x, int y, double p){
    sasiad *s = new sasiad;
    s->numer =  y;
    s->prawdopod = p;
    s->nastepny = tab[x].sasiedzi;
    tab[x].sasiedzi = s;

    s = new sasiad;
    s->numer = x;
    s->prawdopod = p;
    s->nastepny = tab[y].sasiedzi;
    tab[y].sasiedzi = s;
}
double Graf::bfs(){
    double prawdopodobienstwo = 1;
    sasiad *z_p;
    z_p = tab[0].sasiedzi;
    tab[0].czy_odw = true;
    while (z_p != NULL){
        push_lst(*z_p);
        z_p = z_p->nastepny;
    }

    sasiad s;
    while(!empty()){
        s = find();
        pop(s);
        if(!tab[s.numer].czy_odw){
            tab[s.numer].czy_odw = true;
            prawdopodobienstwo *= s.prawdopod;
            z_p = tab[s.numer].sasiedzi;
            while(z_p != NULL){
                push_lst(*z_p);
                z_p = z_p->nastepny;
            }
        }
    }
    return prawdopodobienstwo;
}
int main(){
    int il_szczytow;
    int il_szlakow;
    cin >> il_szczytow;
    cin >> il_szlakow;
    int w1, w2;
    double p;
    Graf g(il_szczytow, il_szlakow);
    for(int i = 0; i < il_szlakow; i++){
        cin >> w1 >> w2;
        cin >> p;
        g.push(w1, w2, p);
    }
    printf("%.3f", g.bfs());
}
