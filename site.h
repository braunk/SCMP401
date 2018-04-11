#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef site_H
#define site_H

using namespace std;
class site{
 public:
  site();
  site(string name,double mxW,int nBanks, string ID1, string ID2);
  string getBankIDs(int i);
  string getSiteName();
  int getNumBanks();
  double getMaxWatts();
  void display();
 private:
  string sitename;
  int numBanks;
  vector<string> bankIDs;
  double maxWatts;
};

#endif
