/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

int main() {
    std::vector<float> lastTemps;
    lastTemps.push_back(65);
    lastTemps.push_back(65.5);
    lastTemps.push_back(65.3);
    lastTemps.push_back(65);
    lastTemps.push_back(65.2);
    
    int count = lastTemps.size();
    std::vector<int> xs;
    std::vector<int> ys;

    for (int i = 0 ; i < lastTemps.size() ; i++) {
        xs.push_back(i+1);
        ys.push_back(lastTemps.at(i));
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
    
    cout<<"Slope " << a << " - " << b << " - " << c << " - " << d << " - " << (a-b)/(c-d);

    return 0;
}
