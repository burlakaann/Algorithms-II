#include <iostream>
#include <stack>

using namespace std;

class bst{
public:
    struct atrakc{
        double klucz;
        atrakc *l_syn;
        atrakc *p_syn;
        atrakc *ojciec;
        stack <string> pseud;
    };
    atrakc *root;
public:
    bst();
    atrakc* search1(double);
    void insert1(double, string);
    void erase1(atrakc*);
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
    v1 = new atrakc;
    v1->l_syn = v1->p_syn = NULL;
    v1->klucz = atr;
    v2 = root;
    if (root == NULL){
        v1->ojciec = NULL;
        v1->pseud.push(pseud);
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
            v1->pseud.push(pseud);
            if(poprzedni->klucz > v1->klucz){
                poprzedni->l_syn = v1;
                v1->ojciec = poprzedni;
            }
            else if(poprzedni->klucz < v1->klucz){
                poprzedni->p_syn = v1;
                v1->ojciec = poprzedni;
            }
            else{
                v1->pseud.push(pseud);
            }
        }
        else{
            v2->pseud.push(pseud);
        }
    }
}
void bst::erase1(atrakc *v){
    v->pseud.pop();
    if(v->pseud.empty()){
        atrakc *nastepny;
        if(v->l_syn == NULL && v->p_syn == NULL){
            if(v->ojciec == NULL){
                root = NULL;
            }
            else{
                if(v->klucz > v->ojciec->klucz){
                    v->ojciec->p_syn = NULL;
                }
                else{
                    v->ojciec->l_syn = NULL;
                }
            }
        }
        else if(v->p_syn != NULL ){
            nastepny = v->p_syn;
            while(nastepny->l_syn != NULL){
                nastepny = nastepny->l_syn;
            }

            v->klucz = nastepny->klucz;
            v->pseud = nastepny->pseud;

            if(nastepny->p_syn != NULL){
                if(nastepny->klucz < nastepny->ojciec->klucz){
                    nastepny->p_syn->ojciec = nastepny->ojciec;
                    nastepny->ojciec->l_syn = nastepny->p_syn;
                }
                else{
                    nastepny->p_syn->ojciec = nastepny->ojciec;
                    nastepny->ojciec->p_syn = nastepny->p_syn;
                }
            }
            else{
                if(nastepny->klucz < nastepny->ojciec->klucz){
                    nastepny->ojciec->l_syn = NULL;
                }
                else{
                    nastepny->ojciec->p_syn = NULL;
                }
            }
        }

        else{
            nastepny = v->l_syn;
            while(nastepny->p_syn != NULL){
                nastepny = nastepny->p_syn;
            }

            v->klucz = nastepny->klucz;
            v->pseud = nastepny->pseud;

            if(nastepny->l_syn != NULL){
                if(nastepny->klucz > nastepny->ojciec->klucz){
                    nastepny->l_syn->ojciec = nastepny->ojciec;
                    nastepny->ojciec->p_syn = nastepny->l_syn;
                }
                else{
                    nastepny->l_syn->ojciec = nastepny->ojciec;
                    nastepny->ojciec->l_syn = nastepny->l_syn;
                }
            }
            else{
                if(nastepny->klucz > nastepny->ojciec->klucz){
                    nastepny->ojciec->p_syn = NULL;
                }
                else{
                    nastepny->ojciec->l_syn = NULL;
                }
            }
        }
    }
}

class BST{
private:
    struct wezel{
        int klucz;
        wezel *l_syn;
        wezel *p_syn;
        wezel *ojciec;
        bst *wartosc;
    };
    wezel *korzen;
public:
    BST();
    void search(int, double);
    void insert(int, double, string);
    void erase(wezel*);
};
BST::BST(){
    korzen = NULL;
}

void BST::erase(wezel *v){
    wezel *nastepny;
    if(v->l_syn == NULL && v->p_syn == NULL){
        if(v->ojciec == NULL){
            korzen = NULL;
        }
        else{
            if(v->klucz > v->ojciec->klucz){
                v->ojciec->p_syn = NULL;
            }
            else{
                v->ojciec->l_syn = NULL;
            }
        }
    }
    else if(v->p_syn != NULL ){
        nastepny = v->p_syn;
        while(nastepny->l_syn != NULL){
            nastepny = nastepny->l_syn;
        }
        v->klucz = nastepny->klucz;
        v->wartosc = nastepny->wartosc;

        if(nastepny->p_syn != NULL){
            if(nastepny->klucz < nastepny->ojciec->klucz){
                nastepny->p_syn->ojciec = nastepny->ojciec;
                nastepny->ojciec->l_syn = nastepny->p_syn;
            }
            else{
                nastepny->p_syn->ojciec = nastepny->ojciec;
                nastepny->ojciec->p_syn = nastepny->p_syn;
            }
        }
        else{
            if(nastepny->klucz < nastepny->ojciec->klucz){
                nastepny->ojciec->l_syn = NULL;
            }
            else{
                nastepny->ojciec->p_syn = NULL;
            }
        }
    }
    else{
        nastepny = v->l_syn;
        while(nastepny->p_syn != NULL){
            nastepny = nastepny->p_syn;
        }

        v->klucz = nastepny->klucz;
        v->wartosc = nastepny->wartosc;

        if(nastepny->l_syn != NULL){
            if(nastepny->klucz > nastepny->ojciec->klucz){
                nastepny->l_syn->ojciec = nastepny->ojciec;
                nastepny->ojciec->p_syn = nastepny->l_syn;
            }
            else{
                nastepny->l_syn->ojciec = nastepny->ojciec;
                nastepny->ojciec->l_syn = nastepny->l_syn;
            }
        }
        else{
            if(nastepny->klucz > nastepny->ojciec->klucz){
                nastepny->ojciec->p_syn = NULL;
            }
            else{
                nastepny->ojciec->l_syn = NULL;
            }
        }
    }
}
void BST::insert(int key, double wspol, string pseud){
    wezel *v1, *v2;
    wezel *poprzedni;
    v1 = new wezel;
    v1->l_syn = v1->p_syn = NULL;
    v1->klucz = key;
    v2 = korzen;
    if (korzen == NULL){
        v1->ojciec = NULL;
        v1->wartosc = new bst;
        v1->wartosc->insert1(wspol, pseud);
        korzen = v1;
    }
    else{
        while(v2 != NULL && v2->klucz != key){
            poprzedni = v2;
            if(v2->klucz < key)
                v2 = v2->p_syn;
            else
                v2 = v2->l_syn;
        }
        if(v2 == NULL){
            v1->wartosc = new bst;
            v1->wartosc->insert1(wspol, pseud);
            if(poprzedni->klucz > key){
                poprzedni->l_syn = v1;
                v1->ojciec = poprzedni;
            }
            else if(poprzedni->klucz < key){
                poprzedni->p_syn = v1;
                v1->ojciec = poprzedni;
            }
            else{
                v1->wartosc->insert1(wspol, pseud);
            }
        }
        else{
            v2->wartosc->insert1(wspol, pseud);
        }
    }
}

void BST::search(int x, double atrakc){
    wezel *z_p = korzen;
    while (z_p != NULL && z_p->klucz != x){
        if(z_p->klucz < x){
            z_p = z_p->p_syn;
        }
        else {
            z_p = z_p->l_syn;
        }
    }
    bst::atrakc *s ;

    if(z_p == NULL){
        cout << "-\n";
    }
    else{
        s = z_p->wartosc->search1(atrakc);
        if(s==NULL){
            cout << "-\n";
        }
        else{
            cout << s->pseud.top() << "\n";
            z_p->wartosc->erase1(s);
            if(z_p->wartosc->root==NULL){
                erase(z_p);
            }
        }
    }
}
double oblicz_wspol(double x, int y){
    return x/5*(int)(y/1000);
}
int main(){
ios_base::sync_with_stdio(false);
bst bs;
BST bst;
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
        bst.insert(koszt, oblicz_wspol(p1,p2), pseudonim);
    }
    else{
        cin >> il_pien >> atrakcyjnosc;
        bst.search(il_pien, atrakcyjnosc);
    }
}
}
