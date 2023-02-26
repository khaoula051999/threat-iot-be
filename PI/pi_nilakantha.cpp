#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <cmath>
#include  <thread>


using namespace std;

#define TEST_CASE 1e4
#define NB_THREADS 8

double somme_globale=0.0f;
int nb_iteration_d_un_thread=(int)(TEST_CASE/NB_THREADS);

//This algorithm is an infinite series called Nilakantha series.
// pi is equal to 3 + 4/(2*3*4) - 4/(4*5*6) + 4/(6*7*8) ...
// see https://www.ias.ac.in/article/fulltext/reso/002/05/0029-0043 for proof.
// const long TEST_CASE = 1e4;
void callcul_pi_partiel_arctang(int myNum){  
    cout << "Thread No " << myNum << " lancé\n";
    srand(time(0));
    double somme_locale = 3.0f; 
    for (int i = 0; i < nb_iteration_d_un_thread ; i ++){ 
        somme_locale += (i % 2 == 0 ? +1.0 : -1.0) * 4.0/( (2*i+2) * (2*i+3) * (2*i+4) );       
    }
    somme_globale += somme_locale;
}

int main() {
    std::thread Ids[NB_THREADS];
    for(int k=0; k<NB_THREADS; k++)
        Ids[k]=thread(callcul_pi_partiel_arctang, k);
    for(int k=0; k<NB_THREADS; k++)
        Ids[k].join();
    cout << "Valeur approchée de Pi (méthode basique 1) : " << somme_globale/NB_THREADS << endl;
    return 0;
}
// the result of the output:
// Thread No 0 lancé
// Thread No 1 lancé
// Thread No 2 lancé
// Thread No 3 lancé
// Thread No 4 lancé
// Thread No 5 lancé
// Thread No 6 lancé
// Thread No 7 lancé
// Valeur approchée de Pi (méthode basique 1) : 3.14159