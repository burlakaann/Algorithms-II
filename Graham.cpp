#include <iostream>
#include<stack>
#include<cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

class Graham{
private:
    struct punkt{
        int x;
        int y;
    };
    stack <punkt> stos;
    int n;
    punkt *tab;
    punkt p0;
    int licznik;
public:
    Graham(){}
    Graham(int);
    int det(punkt, punkt, punkt);
    void insert_to_tab(int, int);
    void wykonaj();
    double odleglosc(punkt, punkt);
    void quicksort(punkt*, int);
    punkt nastepny();
};
Graham::Graham(int n){
    this->n = n;
    tab = new punkt[n];
    licznik = 0;
}
double Graham::odleglosc(punkt p1, punkt p2){
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
Graham::punkt Graham::nastepny(){
    punkt p;
    p = stos.top();
    punkt w ;
    stos.pop();
    w = stos.top();
    stos.push(p);
    return w;
}
void Graham::quicksort(punkt *tab, int licznik){
    int mniejsze = 0;
    int rowne = 0;
    int wieksze = 0;
    int wart;
    punkt losowy = tab[rand()%licznik];
    int i = 0;
    punkt z_p;

    while( licznik > mniejsze+wieksze+rowne ){
        wart = det(p0, losowy, tab[i]);
        if(wart < 0 || (wart == 0 && ( tab[i].y < losowy.y || tab[i].x < losowy.x ) ) ){
            z_p = tab[i];
            tab[i] = tab[mniejsze];
            tab[mniejsze] = z_p;
            mniejsze++;
            i++;
        }else if(wart > 0 || (wart == 0 && ( tab[i].y > losowy.y || tab[i].x > losowy.x ) ) ){
            wieksze++;
            z_p = tab[i];
            tab[i] = tab[licznik-wieksze];
            tab[licznik-wieksze] = z_p;
        }else{
            rowne++;
            i++;
        }
    }
    if(wieksze > 0){
        quicksort(tab+mniejsze+rowne, wieksze);
    }
    if(mniejsze > 0){
        quicksort(tab, mniejsze);
    }
}
int Graham::det(punkt p1, punkt p2, punkt p3){
    return (p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);
}

void Graham::insert_to_tab(int x, int y){
    tab[licznik].x = x;
    tab[licznik].y = y;
    licznik++;
}
void Graham::wykonaj(){
    double suma = 0;
    int min = 0;
    int minY = tab[0].y;
    punkt z_p;
    if(n > 2){
        for (int i = 1; i < n; i++){
            int y = tab[i].y;
            if ((y < tab[min].y) || (y == tab[min].y && tab[i].x < tab[min].x)){
                min=i;
            }
        }
        z_p = tab[0];
        tab[0] = tab[min];
        tab[min] = z_p;

        p0 = tab[0];
        quicksort(tab+1, licznik-1);

        stos.push(p0);
        stos.push(tab[1]);
        for (int i = 2; i < n; i++){
            while (stos.size() > 1 && det(nastepny(), stos.top(), tab[i]) <= 0){
                stos.pop();
            }
            stos.push(tab[i]);
        }
        stos.push(tab[0]);
        while (stos.size() > 1){
            suma+=odleglosc(stos.top(), nastepny());
            stos.pop();
        }
    }
    printf("%.2f", suma);
}

int main(){
   int n;
   cin >> n;
   Graham g(n);
   int x, y;
   for(int i = 0; i < n; i++){
       cin >> x >> y;
       g.insert_to_tab(x,y);
   }
   g.wykonaj();
}
