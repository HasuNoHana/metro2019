#include "../include/Display.h"
#define WIDTH 4
#define WIDTHS 5


using namespace std;


void Display::drawMetro() {

    cout.setf(ios::left, ios::adjustfield);
    cout.width(WIDTHS);
    cout << " ";

    for(auto i: mGraph->getStations()){
        cout.width(WIDTHS);
        cout << i->getName();
    }
    cout<< endl;

    for(auto i: mGraph->getStations()){
        cout.width(WIDTHS);
        cout << i->getName();

        for(auto j: mGraph->getStations()){

            bool pom = false;
            for(auto k: mGraph->getStretches()){
                if((k->getFrom()->getID() == (j)->getID() &&
                        k->getTo()->getID() == i->getID())
                   || (k->getTo()->getID() == j->getID() &&
                       k->getFrom()->getID() == i->getID())){


                    cout.width(WIDTHS);
                    cout << "X";
                    pom = true;
                    break;
                }

            }
                if(!pom){
                    cout.width(WIDTHS);
                    cout << " ";
                }
        }
        cout<<endl;
    }
}

void Display::drawPop() {

    int size = mGraph->getArea()->getSize();
    cout << endl;

    for(int i = 0; i < size ; i++){ // here was SIZE

        cout << "|";

        for (int j = 0; j < size; j++){ // here was SIZE
            cout.width(WIDTH);
            cout << mGraph->getArea()->getPopulation()[i][j] ;
            cout << "|";

        }

        cout << endl;

        for(int a = 0; a < (WIDTH+1)*size + 1; a++){
            cout << "-";
        }

        cout << endl;
    }
}

/////////////////////wzorzec obserwator
////////////dodatkowe klasy design

void Display::savePop(){

    int size = mGraph->getArea()->getSize();

    ofstream file;

    file.open("population.txt", ofstream::out);

    for(int a = 0; a < (WIDTH+1)*size + 1; a++){
        file << "-";
    }

    file << endl;

    for(int i = 0; i < size; i++){

        file << "|";

        for (int j = 0; j < size; j++){
            file.width(WIDTH);
            file << mGraph->getArea()->getPopulation()[i][j] ;
            file << "|";

        }

        file << endl;

        for(int a = 0; a < (WIDTH+1)*size + 1; a++){
            file << "-";
        }

        file << endl;
    }

    file.close();
}