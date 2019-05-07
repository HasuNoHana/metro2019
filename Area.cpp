#include <vector>
#include <iostream>
#include <ctime>
#include <string> 
#include <queue>
#include "Area.h"
#include "Station.h"
#define INF 1000000000 //10^9

using namespace std;

// Point[] wszedzie gdzie masz

/*Point* Area::getCity() {
    return mCity;
}

void Area::setCity(Point * city) {
    mCity = city;
}*/

int &Area::operator[](Point p)
{
    return this->mPopulation[p.getX()][p.getY()];
}

int Area::getSumOfPeople()
{
    return mSumOfPeople;
}

int Area::getTemple() {
    return mTemple;
}

void Area::setTemple(int temple) {
    mTemple = temple;
}

/*Area::Area(Point * city, int temple) {
    mCity = city;
    mTemple = temple;
    mPopulation.assign(100, 0);
}*/


Area::Area() {
    mSize = 100;
    mPopulation = new int*[100]; //domyslny rozmiar
    for(int i=0; i<100; i++)
        mPopulation[i] = new int[100];
    this->generatePopulation();

//    mCity = new Point[100];
    mTemple = 0;
//    mPopulation.assign(100, 0);
}

Area::Area(int size)
{
    mSize = size;
    mPopulation = new int*[size];
    for(int i=0; i<size; ++i)
    {
        mPopulation[i] = new int[size];
        for(int j=0; j<size; ++j)
            mPopulation[i][j]=0;
    }
    this->generatePopulation();
}

Area::~Area() {
//	delete[] mCity;
    for(int i=0; i<mSize; ++i)
            delete[] mPopulation[i];
    delete[] mPopulation;
    cout << "Area has been destroyed..." << "\n";
}

void Area::generatePopulation() // O(mSize^3)
{
    for(int k=0; k<mSize/2; ++k) //zeby w centrum miasta bylo wiecej ludzi
        for(int i = k; i < mSize-k; ++i)
            for(int j = k; j < mSize-k; ++j)
            {
                int r = rand()%5 + 1;
                mSumOfPeople += r;
                mPopulation[i][j] += r;
            }
}

void Area::populationToStation( vector <Station*> stations )
{
    for(int i=0; i<stations.size(); ++i)
        stations[i]->setPeople(0);

    vector <int> tab[mSize][mSize];
    for(int i=0; i<mSize; ++i)
        for(int j=0; j<mSize; j++)
            tab[i][j].push_back(INF);

    queue < pair<Point, int> > Q;

    for(int i=0; i<stations.size(); ++i)
    {
        Q.push( make_pair(stations[i]->getPoint(), i) );
        tab[Q.back().first.getX()][Q.back().first.getY()][0]=1;
        tab[Q.back().first.getX()][Q.back().first.getY()].push_back(i);
    }
    while( !Q.empty() )
    {
        //cout << "R";
        int s = Q.size();
        for(int i=0; i<s; ++i)
        {
            //cout << "n";
            Point p = Q.front().first;
            int ac = Q.front().second;
   //         cout << p.getX() << " " << p.getY() << endl;
            Q.pop();

            if( p.getX()-1 >= 0)
            {
                if( tab[ p.getX()-1 ][ p.getY() ][0] == tab[ p.getX() ][ p.getY() ][0]+1 ) //X-1, Y
                {
                    bool help = true;
                    for(int j=1; j < tab[ p.getX()-1 ][ p.getY() ].size(); ++j)
                        if(tab[ p.getX()-1 ][ p.getY() ][j] == ac) 
                        {
                            help = false;
                            break;
                        }
                    if(help)
                    {
                        tab[ p.getX()-1 ][ p.getY() ].push_back(ac);
                        Q.push( make_pair( Point( p.getX()-1, p.getY() ), ac) );
                    }
                }
                else if(tab[ p.getX()-1 ][ p.getY() ][0] == INF)
                {
                    tab[ p.getX()-1 ][ p.getY() ][0] = tab[ p.getX() ][ p.getY() ][0]+1;
                    tab[ p.getX()-1 ][ p.getY() ].push_back(ac);
                    Q.push( make_pair( Point( p.getX()-1, p.getY() ), ac) );
                }
            }
//return;
            if( p.getX()+1 < mSize)
            {
                if( tab[ p.getX()+1 ][ p.getY() ][0] == tab[ p.getX() ][ p.getY() ][0]+1 ) //X+1, Y
                {
                    bool help = true;
                    for(int j=1; j < tab[ p.getX()+1 ][ p.getY() ].size(); ++j)
                        if(tab[ p.getX()+1 ][ p.getY() ][j] == ac) 
                        {
                            help = false;
                            break;
                        }
                    if(help)
                    {
                        tab[ p.getX()+1 ][ p.getY() ].push_back(ac);
                        Q.push( make_pair( Point( p.getX()+1, p.getY() ), ac) );
                    }
                }
                else if(tab[ p.getX()+1 ][ p.getY() ][0] == INF)
                {
                    tab[ p.getX()+1 ][ p.getY() ][0] = tab[ p.getX() ][ p.getY() ][0]+1;
                    tab[ p.getX()+1 ][ p.getY() ].push_back(ac);
                    Q.push( make_pair( Point( p.getX()+1, p.getY() ), ac) );
                }
            }

            if( p.getY()-1 >= 0)
            {
                if( tab[ p.getX() ][ p.getY()-1 ][0] == tab[ p.getX() ][ p.getY() ][0]+1 ) //X, Y-1
                {
                    bool help = true;
                    for(int j=1; j < tab[ p.getX() ][ p.getY()-1 ].size(); ++j)
                        if(tab[ p.getX() ][ p.getY()-1 ][j] == ac) 
                        {
                            help = false;
                            break;
                        }
                    if(help)
                    {
                        tab[ p.getX() ][ p.getY()-1 ].push_back(ac);
                        Q.push( make_pair( Point( p.getX(), p.getY()-1 ), ac) );
                    }
                }
                else if(tab[ p.getX() ][ p.getY()-1 ][0] == INF)
                {
                    tab[ p.getX() ][ p.getY()-1 ][0] = tab[ p.getX() ][ p.getY() ][0]+1;
                    tab[ p.getX() ][ p.getY()-1 ].push_back(ac);
                    Q.push( make_pair( Point( p.getX(), p.getY()-1 ), ac) );
                }
            }

            if( p.getY()+1 < mSize)
            {
                if( tab[ p.getX() ][ p.getY()+1 ][0] == tab[ p.getX() ][ p.getY() ][0]+1 ) //X, Y+1
                {
                    bool help = true;
                    for(int j=1; j < tab[ p.getX() ][ p.getY()+1 ].size(); ++j)
                        if(tab[ p.getX() ][ p.getY()+1 ][j] == ac) 
                        {
                            help = false;
                            break;
                        }
                    if(help)
                    {
                        tab[ p.getX() ][ p.getY()+1 ].push_back(ac);
                        Q.push( make_pair( Point( p.getX(), p.getY()+1 ), ac) );
                    }
                }
                else if(tab[ p.getX() ][ p.getY()+1 ][0] == INF)
                {
                    tab[ p.getX() ][ p.getY()+1 ][0] = tab[ p.getX() ][ p.getY() ][0]+1;
                    tab[ p.getX() ][ p.getY()+1 ].push_back(ac);
                    Q.push( make_pair( Point( p.getX(), p.getY()+1 ), ac) );
                }
            }
        }
    }
//return;
    for(int i=0; i<mSize; ++i)
        for(int j=0; j<mSize; ++j)
            for(int k=1; k<tab[i][j].size(); ++k)
            {
//                cout << i << " " << j << " -> " << mPopulation[i][j] << " / " << tab[i][j].size()-1 << endl;
                (*stations[ tab[i][j][k] ]) += mPopulation[i][j] / (tab[i][j].size()-1);
                //wedlug valgrind jest blad z mPopulation 
            }
}

// generates the population
// it's just pseudo - random numbers <200, 1200)
/*std::vector<int> Area::generatePopulation(int lenOfDistricts)
{
    //std::vector<int> population;
    mPopulation.assign(100, 0); // sets the value of the vector to 0s
    for (int i = 0; i < lenOfDistricts; i++) {
        mPopulation[i] = rand() % 1000 + 200;
    }


    return mPopulation;
}

// simply returns the member population
std::vector<int> Area::getPopulation()
{
    return mPopulation;
}

// a setter for population
void Area::setPopulation(std::vector<int> population)
{
    mPopulation = population;
}

// writes population to the file
// saves it in the file
void Area::savePopulation(ofstream* toFile)
{
    std::vector<int> temp = this->getPopulation();
    for (int i = 0; i < temp.size(); i++) {
        *toFile << temp[i] << "\n";
    }
	temp.clear();
}

// extract from file
// and restores the population
void Area::restorePopulation(ifstream* fromFile, int elToRead)
{
    std::vector<int> temp;
    temp.assign(100, 0);  // wypełnia zerami
    for (int i = 0; i < elToRead; i++) {
        *fromFile >> temp.at(i);
    }

    this->setPopulation(temp);
}

void Area::printPopulation() {
    for (int i = 0; i < mPopulation.size(); i++) {
        cout << mPopulation[i] << "\n";
    }
}*/


// TODO: match points in area with population on each district





/*int main() {

    srand(time(NULL));
    Area Area;

    // generates the population
    std::vector<int> population = Area.GeneratePopulation(100);
    int genLen = population.size();

    // sets the mPopulation
    Area.SetPopulation(population);

    // that's where the writing goes
    std::ofstream toFile;
    toFile.open("data.txt", ios::out);

    Area.SavePopulation(&toFile);

    toFile.close();

    // for testing purposes associates
    // the population vector to zeros
    std::vector<int> test;
    test.assign(100, 0);
    Area.SetPopulation(test);


    // restoring the population
    std::ifstream fromFile;
    fromFile.open("data.txt", ios::in);

//    std::vector<int> newPop;
    Area.RestorePopulation(&fromFile, genLen);

    // and prints the result
    Area.printPopulation();
}*/
