#include <vector>
#include <string>
#include <iostream>
#include "site.h"


site::site(){
}

site::site(string name,double mxW,int nBanks, string ID1, string ID2){
  sitename=name;
  maxWatts=mxW;
  numBanks=nBanks;
  bankIDs.push_back(ID1);
  if (ID2.size()>1)
    bankIDs.push_back(ID2);
  //  display();
}

string site::getBankIDs(int i){
  return bankIDs[i];
}
string site::getSiteName(){
  return sitename;
}
int site::getNumBanks(){
  return numBanks;
}
double site::getMaxWatts(){
  return maxWatts;
}

void site::display() {
  cout << sitename << ":" << maxWatts << ":" << numBanks;
  for (int i = 0; i<numBanks; i++) {
    cout << ":" << bankIDs[i];
  }
  cout << endl;
}
