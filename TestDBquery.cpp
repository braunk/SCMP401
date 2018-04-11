#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "sites.h"
#include "site.h"

using namespace std;

int main(){
  sites testsites;
  cout << "hello!" <<endl;
  testsites.listSites();
  cout << "Now outputting the latest wattage for the first site..." << endl;
  cout << testsites.latest(1,"qWattsMin1") << endl << endl << endl;
  cout << "Now outputting the last week of wattage data for the first site..." << endl;
  cout << testsites.lastWeek(1,"qWattsMin1") << endl << endl << endl;
  cout << "Now outputting the data for the first site data on April 9th, 7am to 7pm... " << \
endl;
  cout << testsites.qByID(1,"qWattsMin1","2018-4-9 7:00:00","2018-4-9 20:00:00") <<endl<< en\
dl << endl;
  return 0;
}
