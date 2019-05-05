#ifndef STRETCH_H
#define STRETCH_H

#include "Station.h"

class Stretch
{
public:
    Stretch();
    Stretch(int id, int pass, Station from, Station to); //nazwa, przepustowosc i skad dokad
    virtual ~Stretch();

    int getId();
    void setId(int val);
    int getPass();
    void setPass(int val);
    Station getFrom();
    void setFrom(Station val);
    Station getTo(int fromm = 0);
    void setTo(Station val);

protected:

private:
    int mId;
    //maximum number of passengers transported at the same time
    int mPass; //przepustowosc
    Station mFrom;
    Station mTo;
};

#endif // STRETCH_H