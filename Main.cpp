#include <iostream>
//#include "ISCAS.h"
//#include "ROBDD.h"
#include "map.h"

using namespace std;

int main() {

//    ISCAS iscas(stdin);
//    ROBDD robdd;
//
//    robdd.drawGraph(iscas);
//
//    return 0;

//    map_rb<int, char> mymap;
//    auto var1 = std::pair<int, char>(0, 'a');
//    auto var2 = std::pair<int, char>(1, 'b');
//    auto var3 = std::pair<int, char>(2, 'c');
//    mymap.insert(var1);
//     mymap.insert(var2);
//     mymap.insert(var3);
//
//
//
////    cout << "key 0: " <<  res.first->first << "\nchar 0: " << res.first->second << "\nresult insert 0 : " << res.second << std::endl;
////    cout << "key 1: " <<  res2.first->first << "\nchar 1: " << res2.first->second << "\nresult insert 1 : " << res2.second << std::endl;
////    cout << "key 2: " <<  res3.first->first << "\nchar 2: " << res3.first->second << "\nresult insert 2 : " << res3.second << std::endl;
//
//    for(auto i = mymap.begin(); i != mymap.end(); i++){
//        cout << "key : " <<  i->first << "\nchar : " << i->second << endl;
//        cout << "+++++++++" << endl;
//    }

    int a = 12;
    int[] tester = new int[2];
    tester[0] = 2;
    cout << "tester : " << *tester << endl;
    cout << "tester 1 : " << *++tester << endl;
    cout << "tester 2 : " << *++tester << endl;
}
