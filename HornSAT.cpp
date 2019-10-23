#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>

using namespace std;

bool compare( vector<int> *first, vector<int> *second ){
    return first->size() > second->size();
}


class HornSAT{
private:
    class Package{
    public:
        bool sign;
        bool unit_clause;
        Package(){
            sign = false;
            unit_clause = false;
        }
    };
    bool result;
    Package *packages;
    vector<vector<int>*> excursions;
public:
    HornSAT( int );
    void add_clause( int, int* );
    void hornsat ();
};

HornSAT::HornSAT( int number_of_excursion_packages ){

    packages = new Package[number_of_excursion_packages + 1]();
    result = false;

}

void HornSAT::add_clause( int package_counter, int *packages1 ){

    vector<int> *clause = new vector<int>;

    if( package_counter == 1 ){
        if( packages[abs(packages1[0])].unit_clause ){
            if ( packages[abs(packages1[0])].sign != packages1[0] > 0 ){
                cout << "NIE";
                result = true;
                return;
            }
            else{
                return;
            }
        }
        else{
            packages[abs(packages1[0])].unit_clause = true;
            packages[abs(packages1[0])].sign = packages1[0] > 0;
            clause->push_back(packages1[0]);
        }
    }
    else{
        for( int i = 0; i < package_counter; i++ ){
            if( packages[abs(packages1[i])].unit_clause ){
                if ( packages[abs(packages1[i])].sign == packages1[i] > 0 ){
                    return;
                }
            }
            else{
                clause->push_back(packages1[i]);
            }
        }
    }

    if( clause->size() != 0 ){
        excursions.push_back(clause);
    }
    else{
        delete clause;
    }
}

void HornSAT::hornsat(){
    if( !result ){
        int min_number_of_humanists = 0;
        vector<int> *back_el;
        vector<vector<int>*>::iterator it1;
        vector<int>::iterator it2;
        while(!excursions.empty()){

            if( excursions.back()->size() != 1 ){
                sort( excursions.begin(), excursions.end(), compare );

                while( !excursions.empty() && excursions.back()->size() == 0 ){
                    excursions.pop_back();
                }

                if( excursions.empty() ){
                    break;
                }

                if( excursions.back()->size() > 1 ){
                    cout << min_number_of_humanists;
                    return;
                }

            }

            back_el = excursions.back();
            excursions.pop_back();

            if( back_el->front() < 0 )
                min_number_of_humanists++;

            for ( it1 = excursions.begin(); it1 != excursions.end(); ++it1 ){
                for( it2 = (*it1)->begin(); it2 != (*it1)->end(); ){
                    if( back_el->front() == *it2 ){
                        (*it1)->clear();
                        break;
                    }
                    else if( back_el->front() == (*it2)*(-1) && (*it1)->size() == 1){
                        cout << "NIE";
                        return;
                    }
                    else if( back_el->front() == (*it2)*(-1) ){
                        it2 = (*it1)->erase(it2);
                    }
                    else{
                        ++it2;
                    }
                }
            }
        }
        cout << min_number_of_humanists;
    }
}
int main(){
    ios_base::sync_with_stdio(false);

    int number_of_excursion_packages;
    int number_of_excursions;
    int number_of_participants;
    cin >> number_of_excursion_packages;
    cin >> number_of_excursions;

    HornSAT hornsat(number_of_excursion_packages);

    for ( int i = 0; i < number_of_excursions; i++ ){
        cin >> number_of_participants;
        int *packages = new int[number_of_participants];
        for ( int j = 0; j < number_of_participants; j++ ){
            cin >> packages[j];
        }
        hornsat.add_clause(number_of_participants, packages);
        delete[] packages;
    }
    hornsat.hornsat();
}
