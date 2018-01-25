path = -I ../Eigen

className = HarmonySearch

test:HS testHS

HS:HS_class HS_ar

HS_class:HarmonySearch.h HarmonySearch.cpp
	g++ -c HarmonySearch.cpp $(path) -std=c++11

HS_ar:HarmonySearch.o
	ar rvs HarmonySearch.a HarmonySearch.o
testHS:HarmonySearch.a testHS.cpp
	g++ testHS.cpp HarmonySearch.a -o testHS $(path) -std=c++11
