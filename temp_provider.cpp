#include "temp.h"

TempProvider::TempProvider() {
}

void TempProvider::init() {
    timeInitiated = -1;
}

bool TempProvider::isStable() {
    int count = lastTemps.size();
    std::vector<int> xs;
    std::vector<int> ys;

    for (int i = 0 ; i < lastTemps.size() ; i++) {
        xs.pushBack(i+1);
        ys.pushBack(lastTemps.at(i));
    }    

    double a = 0;
    double b;
    double c;
    double d;

    for (int i = 0 ; i < lastTemps.size() ; i++) {
        a += (i+1)*lastTemps.at(i);
    }
    a = count * a;
    b = std::accumulate(xs.begin(), xs.end(), 0, [](int a, int b){ return a+b; })*std::accumulate(ys.begin(), ys.end(), 0, [](int a, int b){ return a+b; });
    c = count*std::accumulate(xs.begin(), xs.end(), 0, [](int a, int b){ return a+b*b; });
    d = std::accumulate(xs.begin(), xs.end(), 0, [](int a, int b){ return a+b; })*std::accumulate(xs.begin(), xs.end(), 0, [](int a, int b){ return a+b; });

    //std::transform(xs.begin(), xs.end(), vec.begin(), [](int i){ return i*i;} );

    // std::accumulate(vec.begin(), vec.end(), 1, [](int a, int b){ return a*b; });  

    double e;
    double f;
}