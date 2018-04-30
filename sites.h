#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "site.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#ifndef sites_H
#define sites_H

#define HOST "" //taken out for security reasons
#define USER "" //taken out for security reasons
#define DB "" //taken out for security reasons
#define PASS "" //taken out for security reasons

using namespace std;

class sites{
 public:
  sites();
  ~sites();
  //for individual sites
  string qByID(int site, string wattsOrVolts, string timestamp1, string timestamp2);
  string lastWeek(int site, string wattsOrVolts);
  string latest(int site, string wattsOrVolts);
  string yesterday(int site, string wattsOrVolts);
  //for all sites
  string latestForAll(string wattsOrVolts);
  void listSites();
 private:
  vector<site> allSites;
  const string url=HOST;
  const string user=USER;
  const string database=DB;
  const string pass=PASS;
};

#endif
