#include <vector>
#include <iostream>
#include "sites.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


sites::sites(){
  allSites.reserve(20);
  //push these in individually
  allSites.push_back(site("Log Cabins",2000,2,"A43C8B0C4A","A43C8B0CD7"));
  allSites.push_back(site("St. Andrews Primary", 1200, 2,"A43C8B0AB1","A43CE7BE69"));
  allSites.push_back(site("Victorious Nazarene",1200,2,"A43C6DC4D2","A43CE7BE5E"));
  /*,Kings("Kings College", 800, 1,["A43C6DC5EB"])*/
  allSites.push_back(site("Toledo Christian Academy", 800, 1,"A43C895C02",""));
  allSites.push_back(site("San Antonio Primary", 1200, 1,"A43C6DC815",""));
  allSites.push_back(site("Faith Nazarene", 1200, 1,"A43CE7BE78",""));
  /*,SartenejaNaz("Sarteneja Nazarene", 1200, 1,["A43C6DC4C6"])*/
  allSites.push_back(site("Corazol Methodist", 1200, 1,"A43CE7C04F",""));
  allSites.push_back(site("ACES", 1600, 2,"A43C8B0C4C","A43C8B0B9F"));
  allSites.push_back(site("Brighter Tomorrow", 800, 1,"A43CE7BE41",""));
  /*,Kenyon("Kenyon Solar Demo", 600, 1,["A43C6DC810"])*/
  allSites.push_back(site("Alvin Young", 800, 1,"A43C6DC863",""));
  allSites.push_back(site("Belopan Baptist High School", 800, 1,"A43CD10AAB",""));
  allSites.push_back(site("New Horizons High School", 1600, 1,"A43C6DC860","A43C6DC5E5"));
  allSites.push_back(site("San Pedro High School", 1600, 1,"A43C6DC854","A43C6DC5CC"));
}

sites::~sites(){
  allSites.clear();
}

void sites::listSites(){
  cout << allSites.size()<<endl;
  for(int i=0; i < allSites.size(); i++){
    allSites[i].display();
  }
}

string sites::qByID(int sitenum,string wattsOrVolts,string timestamp1, string timestamp2){
    string results="";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());

    results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+to_string(al\
lSites[sitenum].getMaxWatts())+"</maxWatts><numBanks>"+to_string(allSites[sitenum].getNumBan\
ks())+"</numBanks>");
    for(int i=0;i<allSites[sitenum].getNumBanks();i++){
      results+="<bank>";
      stmt->execute("SELECT DATE(TimeStamp) AS DAY, HOUR(TimeStamp) as HOUR, AVG(Response) A\
S AVG FROM `Answers` WHERE IID = '"+allSites[sitenum].getBankIDs(i)+"' AND QID = '" + wattsO\
rVolts +"' AND TimeStamp BETWEEN '"+timestamp1+"' AND '"+timestamp2+"' GROUP BY DAY,HOUR;");
      std::auto_ptr< sql::ResultSet> res;

      string lastDate="";
      string currentDate="";

      do{
        res.reset(stmt->getResultSet());
        while(res->next()){
          currentDate=res->getString("DAY");
          if(lastDate!=currentDate){
            results+=("<date>"+currentDate+"</date>");
          }
          lastDate=currentDate;
          results+=("<hour>"+res->getString("HOUR")+"</hour>");
          results+=("<"+wattsOrVolts+">"+res->getString("AVG")+"</"+wattsOrVolts+">");
        }
      }while(stmt->getMoreResults());
      results+="</bank>";
    }
    results+="</site>";
    return results;
  }

string sites::lastWeek(int sitenum,string wattsOrVolts){
    string results="";
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());

    results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+to_string(al\
lSites[sitenum].getMaxWatts())+"</maxWatts><numBanks>"+to_string(allSites[sitenum].getNumBan\
ks())+"</numBanks>");
    for(int i=0;i<allSites[sitenum].getNumBanks();i++){
      results+="<bank>";
      stmt->execute("SELECT DAYOFWEEK(TimeStamp) AS DAY,HOUR(TimeStamp) as HOUR,AVG(Response\
) AS AVG FROM `Answers` WHERE IID = '"+allSites[sitenum].getBankIDs(i)+"' AND QID = '" + wat\
tsOrVolts +"' AND YEARWEEK (TimeStamp) = YEARWEEK( current_date -interval 1 week ) GROUP BY \
DAY, HOUR;");
      std::auto_ptr< sql::ResultSet> res;

      string lastDate="";
      string currentDate="";

      do{
        res.reset(stmt->getResultSet());
        while(res->next()){
          currentDate=res->getString("DAY");
          if(lastDate!=currentDate){
            results+=("<dayofweek>"+currentDate+"</dayofweek>");
          }
          lastDate=currentDate;
          results+=("<hour>"+res->getString("HOUR")+"</hour>");
          results+=("<"+wattsOrVolts+">"+res->getString("AVG")+"</"+wattsOrVolts+">");
        }
      }while(stmt->getMoreResults());
      results+="</bank>";
    }
    results+="</site>";

    return results;
}

string sites::latest(int sitenum, string wattsOrVolts){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+to_string(allS\
ites[sitenum].getMaxWatts())+"</maxWatts><numBanks>"+to_string(allSites[sitenum].getNumBanks\
())+"</numBanks>");
  for(int i=0;i<allSites[sitenum].getNumBanks();i++){
    results+="<bank>";
    stmt->execute("SELECT TimeStamp, Response FROM `Answers` WHERE IID = '"+allSites[sitenum\
    ].getBankIDs(i)+"' AND QID = '"+wattsOrVolts+"' ORDER BY TimeStamp DESC LIMIT 1;");
    std::auto_ptr< sql::ResultSet> res;
    do{
      res.reset(stmt->getResultSet());
      while(res->next()){
        results+=("<mostrecent>"+res->getString("TimeStamp")+"</mostrecent>");
        results+=("<"+wattsOrVolts+">"+res->getString("Response")+"</"+wattsOrVolts+">");
      }
    }while(stmt->getMoreResults());
    results+="</bank>";
  }
  results+="</site>";
  return results;
}

string sites::latestForAll(string wattsOrVolts){
  string results="";
  for(int i=0;i<allSites.size();i++){
    results+=latest(i,wattsOrVolts);
  }
  return results;
}
