#include <iostream>
#include <queue>

using namespace std;

class Graf{
private:
    struct szach{
        bool czy_bud;
        bool czy_dodany;
    };
    struct sasiad{
        int numer;
        sasiad *nastepny;
    };
    struct wierzcholek{
        sasiad *sasiedzi;
    };
    wierzcholek *tab;

    int skojarzenia;
    int n;
    int il_par;
    int rozm;
    szach **szachownica;
public:
    Graf(){}
    Graf(int );
    void budynek(int, int);
    void przeksztalc();
    void max_skojarzenie();
};

Graf::Graf( int n ){
    this->n = n;

    szachownica = new szach*[n];
    for( int i = 0; i < n; i++ ){
        szachownica[i] = new szach[n];
        for( int j = 0; j < n; j++ ){
            szachownica[i][j].czy_bud = false;
            szachownica[i][j].czy_dodany = false;
        }
    }

    rozm = n*n+2;
    tab = new wierzcholek[rozm];
    for( int i = 0; i < rozm; i++ ){
        tab[i].sasiedzi = NULL;
    }
}

void Graf::budynek(int x, int y){

    szachownica[y][x].czy_bud = true;

}

void Graf::przeksztalc(){
    sasiad *s;
    bool flag;
    int wP, wN;
    int j;
    wP = wN = 0;

    for ( int i = 2; i < n; i++ ){
        if( !(i&1) ){
            j = 1;
        }
        else{
            j = 0;
        }

        for( j; j < n; j += 2 ){
            flag = false;
            if( !szachownica[i][j].czy_bud ){
                if ( j - 1 >= 0){
                    if ( !szachownica[i-2][j-1].czy_bud ){
                        wN++;
                        flag = true;

                        s = new sasiad;
                        s->numer = n*(i-2)+(j-1);
                        s->nastepny = tab[n*i+j].sasiedzi;
                        tab[n*i+j].sasiedzi = s;

                        if( !szachownica[i-2][j-1].czy_dodany ){
                            szachownica[i-2][j-1].czy_dodany = true;
                            s = new sasiad;
                            s->numer = rozm-1;
                            s->nastepny = tab[n*(i-2)+(j-1)].sasiedzi;
                            tab[n*(i-2)+(j-1)].sasiedzi = s;
                        }
                    }
                }
                if ( j + 1 < n ){
                    if ( !szachownica[i-2][j+1].czy_bud ){
                        wN++;
                        flag = true;

                        s = new sasiad;
                        s->numer = n*(i-2)+(j+1);
                        s->nastepny = tab[n*i+j].sasiedzi;
                        tab[n*i+j].sasiedzi = s;

                        if( !szachownica[i-2][j+1].czy_dodany ){
                            szachownica[i-2][j+1].czy_dodany = true;
                            s = new sasiad;
                            s->numer = rozm-1;
                            s->nastepny = tab[n*(i-2)+(j+1)].sasiedzi;
                            tab[n*(i-2)+(j+1)].sasiedzi = s;
                        }

                    }
                }
                if ( i - 3 >= 0 ){
                    if ( !szachownica[i-3][j].czy_bud ){
                        wN++;
                        flag = true;

                        s = new sasiad;
                        s->numer = n*(i-3)+j;
                        s->nastepny = tab[n*i+j].sasiedzi;
                        tab[n*i+j].sasiedzi = s;

                        if( !szachownica[i-3][j].czy_dodany ){
                            szachownica[i-3][j].czy_dodany = true;
                            s = new sasiad;
                            s->numer = rozm-1;
                            s->nastepny = tab[n*(i-3)+j].sasiedzi;
                            tab[n*(i-3)+j].sasiedzi = s;
                        }
                    }
                }
                if( flag ){
                    s = new sasiad;
                    s->numer = n*i+j;
                    s->nastepny = tab[rozm-2].sasiedzi;
                    tab[rozm-2].sasiedzi = s;

                    wP++;
                }
            }
        }
    }
    if ( wP < wN )
        il_par = wP;
    else
        il_par = wN;
}

void Graf::max_skojarzenie(){
    bool flag;
    int it;
    int k_front;
    sasiad *z_p;
    sasiad *wejscie;
    sasiad *s;
    sasiad *poprzedni;
    int skojarzenia = 0;
    int sciezka[rozm];
    bool *odwiedzone;

    wejscie = tab[rozm-2].sasiedzi;

    while( skojarzenia < il_par && wejscie != NULL ){
        odwiedzone = new bool[rozm]();
        queue <int> kolejka;
        flag = false;

        kolejka.push(wejscie->numer);
        odwiedzone[wejscie->numer] = true;
        sciezka[wejscie->numer] = rozm-2;

        odwiedzone[rozm-2] = true;

        if( kolejka.empty() ){
            break;
        }
        else{
            while(!kolejka.empty()){

                k_front = kolejka.front();
                kolejka.pop();
                z_p = tab[k_front].sasiedzi;

                while( z_p != NULL ){
                    if ( !odwiedzone[z_p->numer] ){

                        kolejka.push(z_p->numer);
                        odwiedzone[z_p->numer] = true;
                        sciezka[z_p->numer] = k_front;

                        if( z_p->numer == rozm-1 ){

                            skojarzenia++;
                            it = z_p->numer;

                            while( it != rozm-2 ){

                                s = new sasiad;
                                s->numer = sciezka[it];
                                s->nastepny = tab[it].sasiedzi;
                                tab[it].sasiedzi = s;

                                s = tab[sciezka[it]].sasiedzi;
                                poprzedni = NULL;

                                while( s != NULL ){
                                    if( s->numer == it ){
                                        if( poprzedni != NULL ){
                                            poprzedni->nastepny = s->nastepny;
                                        }
                                        else{
                                            tab[sciezka[it]].sasiedzi = s->nastepny;
                                        }
                                        delete s;
                                        break;
                                    }
                                    poprzedni = s;
                                    s = s->nastepny;
                                }
                                it = sciezka[it];
                            }
                            flag = true;
                        }
                    }
                    z_p = z_p->nastepny;
                }
                if(flag)
                    break;
            }
        }
        wejscie = wejscie->nastepny;
        delete[] odwiedzone;
    }
    cout << n*n - skojarzenia;
}

int main(){
    ios_base::sync_with_stdio(false);
    int rozmiar_pola, ilosc_bud;
    cin >> rozmiar_pola >> ilosc_bud;
    Graf g(rozmiar_pola);
    int x, y;
    for( int i = 0; i < ilosc_bud; i++ ){
        cin >> x >> y;
        g.budynek(x, y);
    }
    g.przeksztalc();
    g.max_skojarzenie();
}
