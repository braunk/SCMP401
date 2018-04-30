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
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());
  stmt->execute("SELECT Sites.SiteName as SITE, Banks.BankID AS BANKID FROM Sites, Banks WHE\
RE Sites.SiteID=Banks.SiteID;");
  std::auto_ptr< sql::ResultSet> res;

  string currentSite="",lastSite="";
  string bank;
  site tempsite;
  do{
    res.reset(stmt->getResultSet());
    while(res->next()){
      currentSite=res->getString("SITE");
      bank=res->getString("BANKID");
      if(lastSite==currentSite){
        tempsite.setBank2(bank);
      }
      else{
        if(tempsite.getSiteName()!=""){
          allSites.push_back(tempsite);
        }
        tempsite=site(currentSite,bank,"");
      }
      lastSite=currentSite;
    }
  }while(stmt->getMoreResults());
   allSites.push_back(tempsite);
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

string sites::yesterday(int sitenum, string wattsOrVolts){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  results=("<site><name>"+allSites[sitenum].getSiteName()+"</name>");
  for(int i=0;i<allSites[sitenum].getNumBanks();i++){
    results+="<bank>";
    stmt->execute("SELECT HOUR(TimeStamp) as HOUR,AVG(Response) AS AVG FROM `Answers` WHERE \
IID = '"+allSites[sitenum].getBankIDs(i)+"' AND QID='"+wattsOrVolts +"' AND YEARWEEK (TimeSt\
amp) = YEARWEEK( current_date -interval 1 day ) AND (TimeStamp >= DATE_SUB(CURDATE(), INTERV\
AL 1 DAY) AND TimeStamp < CURDATE()) GROUP BY HOUR;");
    std::auto_ptr< sql::ResultSet> res;
    do{
      res.reset(stmt->getResultSet());
      while(res->next()){
        results+=("<hour>" + res->getString("HOUR") + "</hour>");
        results+=("<"+ wattsOrVolts + ">" + res->getString("AVG") + "</"+ wattsOrVolts + ">"\
);
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
