# Journal Entries
## Week 4/9
This week I've been primarily working out the details of my continued work. That means meeting with Jensen and Matt and Professor Skon. I met with Jensen and Matt separately and walked through how to use my code, as well as sent them both a long, descriptive email for refrence, as follows:
```{txt}
Hi guys,

I put all my connection code (2 .h files, 2 .cpp class definition files, .cpp test file, and the makefile) on my github SCMP repository. Here it is: 
https://github.com/braunk/SCMP401/tree/master

I took out my some of the fields on the sites.h file that might be sensitive (like my username and password) but that part should look as follows:
#define HOST "cs3.kenyon.edu"
#define USER "***"
#define DB "LIM-SERV"
#define PASS "***"
so make sure you change that before you try running it. 

Lastly I want to discuss the syntax that you need to use when using the functions. qByID, latest, and lastWeek will all taken in the sites order in the vector. That order can be found in the push_back order in the sites constructor, but I'll list them below anyways:
0: Log Cabins
1: St. Andrews Primary
2: Victorious Nazarene
3: Toledo Christian Academy
4: San Antonio Primary
5: Faith Nazarene
6: Corazol Methodist
7: ACES
8: Brighter Tomorrow
9: Alvin Young
10: Belopan Baptist High School
11: New Horizons High School
12: San Pedro High School
Next they taken in if you want the results in watts or volts, which you will write as "qWattsMin1" for watts and "qVoltsMin1" for volts (as shown in the test file). Those are all the passed parameters for the second two functions, but make sure that qByID for timestamp1 and timestamp2, the date is formatted correctly as "yyyy-mm-dd 00:00:00", but I don't think it's written to go down to minute by minute for that, so stick with timestamps that are on the hour (timestamp2 is non-inclusive of the hour you stop it in).

Sorry this is so long and probably and excessive explanation of the code, but I hope that it was helpful. Let me know if you have any questions!
```
In addition I met with Skon to discuss the next step of subtabling. We defined the structure of the tables we wanted to add and, in phpmyadmin, I created the two new tables, Sites and Banks. Sites includes only the site name and an unique ID field serving as the primary key. Banks had Bank ID, serving as the primary key, number of panels, and max watts. Banks also had Site ID the corresponded to the site to which it belong and serves as the bridge between the two tables. I also populated the two tables with the bank and site information that I've been using in the vectors I built, as well as information from the website. The idea is to build the vector based off of the sites and bank tables, then continue using the functions as already designed, this way the vector will have the newest information without a doubt.

Here is some code I have been using to test the connection of the two new subtables:
```{SQL}
 SELECT Sites.SiteName, Banks.BankID, Banks.NumPanels, Banks.BankID FROM Sites, Banks WHERE Sites.SiteID=Banks.SiteID;
 ```
 And the output:
 ```{SQL}
 +------------------------------+------------+-----------+------------+
| SiteName                     | BankID     | NumPanels | BankID     |
+------------------------------+------------+-----------+------------+
| Log Cabins                   | A43C8B0C4A |         6 | A43C8B0C4A |
| Log Cabins                   | A43C8B0CD7 |         6 | A43C8B0CD7 |
| St. Andrews Primary          | A43C8B0AB1 |         4 | A43C8B0AB1 |
| St. Andrews Primary          | A43CE7BE69 |         4 | A43CE7BE69 |
| Victorious Nazarene          | A43C6DC4D2 |         3 | A43C6DC4D2 |
| Victorious Nazarene          | A43CE7BE5E |         3 | A43CE7BE5E |
| Kings College                | A43C6DC5EB |         4 | A43C6DC5EB |
| Toledo Christian Academy     | A43C895C02 |         4 | A43C895C02 |
| San Antonio Primary          | A43C6DC815 |         6 | A43C6DC815 |
| Faith Nazarene               | A43CE7BE78 |         6 | A43CE7BE78 |
| Sarteneja Nazarene           | A43C6DC4C6 |         6 | A43C6DC4C6 |
| Corazol Methodist            | A43CE7C04F |         4 | A43CE7C04F |
| ACES                         | A43C8B0B9F |         6 | A43C8B0B9F |
| ACES                         | A43C8B0C4C |         4 | A43C8B0C4C |
| Brighter Tomorrow            | A43CE7BE41 |         4 | A43CE7BE41 |
| Alvin Young                  | A43C6DC863 |         4 | A43C6DC863 |
| Belmopan Baptist High School | A43CD10AAB |         4 | A43CD10AAB |
| New Horizons Primary School  | A43C6DC5E5 |         4 | A43C6DC5E5 |
| New Horizons Primary School  | A43C6DC860 |         4 | A43C6DC860 |
| San Pedro High School        | A43C6DC5CC |         4 | A43C6DC5CC |
| San Pedro High School        | A43C6DC854 |         4 | A43C6DC854 |
+------------------------------+------------+-----------+------------+
```
Lastly, I also have been working on putting together my final presentation and reflecting on the work I have done on this project this semester. My next steps to accomplish in the few short weeks left is to edit the connection tcode to account for the new tables I created, as well as do some testing on the speed of the data retrieval.
## Week 4/2
Aha! I finally got the connection code running (with a lot of help from professor Skon of course). In the end, a lot of my constructors and deconstructors were not build correctly and the classes were having issues with accessing the vector members outside of where they were build. I've included the sites class constructor and deconstructor from the .cpp file below:
```{cpp}
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
```

Below is the test program I wrote:
```{cpp}
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

  return 0;
}
```
And this is the output of that:
```{txt}
hello!
13
Log Cabins:2000:2:A43C8B0C4A:A43C8B0CD7
St. Andrews Primary:1200:2:A43C8B0AB1:A43CE7BE69
Victorious Nazarene:1200:2:A43C6DC4D2:A43CE7BE5E
Toledo Christian Academy:800:1:A43C895C02
San Antonio Primary:1200:1:A43C6DC815
Faith Nazarene:1200:1:A43CE7BE78
Corazol Methodist:1200:1:A43CE7C04F
ACES:1600:2:A43C8B0C4C:A43C8B0B9F
Brighter Tomorrow:800:1:A43CE7BE41
Alvin Young:800:1:A43C6DC863
Belopan Baptist High School:800:1:A43CD10AAB
New Horizons High School:1600:1:A43C6DC860
San Pedro High School:1600:1:A43C6DC854
Now outputting the latest wattage for the first site...
<site><name>St. Andrews Primary</name><maxWatts>1200.000000</maxWatts><numBanks>2</numBanks><bank><mostrecent>2018-04-09 18:52:16</mostrecent><qWattsMin1>59</qWattsMin1></bank><bank><mostrecent>2018-04-09 18:52:15</mostrecent><qWattsMin1>31</qWattsMin1></bank></site>


Now outputting the last week of wattage data for the first site...
<site><name>St. Andrews Primary</name><maxWatts>1200.000000</maxWatts><numBanks>2</numBanks><bank><dayofweek>1</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>42.1429</qWattsMin1><hour>9</hour><qWattsMin1>215.1522</qWattsMin1><hour>10</hour><qWattsMin1>326.1538</qWattsMin1><hour>11</hour><qWattsMin1>316.2439</qWattsMin1><hour>12</hour><qWattsMin1>307.5319</qWattsMin1><hour>13</hour><qWattsMin1>375.3953</qWattsMin1><hour>14</hour><qWattsMin1>365.8571</qWattsMin1><hour>15</hour><qWattsMin1>359.1220</qWattsMin1><hour>16</hour><qWattsMin1>340.1837</qWattsMin1><hour>17</hour><qWattsMin1>288.0698</qWattsMin1><hour>18</hour><qWattsMin1>135.9756</qWattsMin1><hour>19</hour><qWattsMin1>19.4151</qWattsMin1><dayofweek>2</dayofweek><hour>7</hour><qWattsMin1>0.0227</qWattsMin1><hour>8</hour><qWattsMin1>58.3438</qWattsMin1><hour>9</hour><qWattsMin1>213.8444</qWattsMin1><hour>10</hour><qWattsMin1>347.9189</qWattsMin1><hour>11</hour><qWattsMin1>337.0571</qWattsMin1><hour>12</hour><qWattsMin1>343.9000</qWattsMin1><hour>13</hour><qWattsMin1>311.9302</qWattsMin1><hour>14</hour><qWattsMin1>367.6316</qWattsMin1><hour>15</hour><qWattsMin1>310.3902</qWattsMin1><hour>16</hour><qWattsMin1>273.9767</qWattsMin1><hour>17</hour><qWattsMin1>227.9032</qWattsMin1><hour>18</hour><qWattsMin1>139.8947</qWattsMin1><hour>19</hour><qWattsMin1>18.0833</qWattsMin1><dayofweek>3</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>25.9535</qWattsMin1><hour>9</hour><qWattsMin1>108.0426</qWattsMin1><hour>10</hour><qWattsMin1>333.4667</qWattsMin1><hour>11</hour><qWattsMin1>379.0303</qWattsMin1><hour>12</hour><qWattsMin1>299.1860</qWattsMin1><hour>13</hour><qWattsMin1>255.9400</qWattsMin1><hour>14</hour><qWattsMin1>327.4167</qWattsMin1><hour>15</hour><qWattsMin1>322.8571</qWattsMin1><hour>16</hour><qWattsMin1>330.1081</qWattsMin1><hour>17</hour><qWattsMin1>247.3000</qWattsMin1><hour>18</hour><qWattsMin1>128.2667</qWattsMin1><hour>19</hour><qWattsMin1>17.8298</qWattsMin1><dayofweek>4</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>9</hour><qWattsMin1>60.2727</qWattsMin1><hour>10</hour><qWattsMin1>205.1373</qWattsMin1><hour>11</hour><qWattsMin1>383.5306</qWattsMin1><hour>12</hour><qWattsMin1>304.8462</qWattsMin1><hour>13</hour><qWattsMin1>340.6000</qWattsMin1><hour>14</hour><qWattsMin1>335.8235</qWattsMin1><hour>15</hour><qWattsMin1>328.8889</qWattsMin1><hour>16</hour><qWattsMin1>293.2500</qWattsMin1><hour>17</hour><qWattsMin1>151.1905</qWattsMin1><hour>18</hour><qWattsMin1>124.2391</qWattsMin1><hour>19</hour><qWattsMin1>12.9767</qWattsMin1><dayofweek>5</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>25.6429</qWattsMin1><hour>9</hour><qWattsMin1>103.0189</qWattsMin1><hour>10</hour><qWattsMin1>262.7692</qWattsMin1><hour>11</hour><qWattsMin1>328.4706</qWattsMin1><hour>12</hour><qWattsMin1>375.6600</qWattsMin1><hour>13</hour><qWattsMin1>356.2200</qWattsMin1><hour>14</hour><qWattsMin1>353.0175</qWattsMin1><hour>15</hour><qWattsMin1>347.1091</qWattsMin1><hour>16</hour><qWattsMin1>320.0000</qWattsMin1><hour>17</hour><qWattsMin1>248.5435</qWattsMin1><hour>18</hour><qWattsMin1>134.5952</qWattsMin1><hour>19</hour><qWattsMin1>13.9063</qWattsMin1><dayofweek>6</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>22.0698</qWattsMin1><hour>9</hour><qWattsMin1>92.5854</qWattsMin1><hour>10</hour><qWattsMin1>240.4651</qWattsMin1><hour>11</hour><qWattsMin1>372.3077</qWattsMin1><hour>12</hour><qWattsMin1>335.6444</qWattsMin1><hour>13</hour><qWattsMin1>324.0889</qWattsMin1><hour>14</hour><qWattsMin1>292.8400</qWattsMin1><hour>15</hour><qWattsMin1>297.1429</qWattsMin1><hour>16</hour><qWattsMin1>285.0833</qWattsMin1><hour>17</hour><qWattsMin1>248.4118</qWattsMin1><hour>18</hour><qWattsMin1>113.7547</qWattsMin1><hour>19</hour><qWattsMin1>14.6444</qWattsMin1><dayofweek>7</dayofweek><hour>7</hour><qWattsMin1>0.1765</qWattsMin1><hour>8</hour><qWattsMin1>25.1892</qWattsMin1><hour>9</hour><qWattsMin1>162.4286</qWattsMin1><hour>10</hour><qWattsMin1>325.7000</qWattsMin1><hour>11</hour><qWattsMin1>368.5429</qWattsMin1><hour>12</hour><qWattsMin1>353.9756</qWattsMin1><hour>13</hour><qWattsMin1>335.1000</qWattsMin1><hour>14</hour><qWattsMin1>311.2500</qWattsMin1><hour>15</hour><qWattsMin1>313.6875</qWattsMin1><hour>16</hour><qWattsMin1>271.3333</qWattsMin1><hour>17</hour><qWattsMin1>197.1304</qWattsMin1><hour>18</hour><qWattsMin1>116.4082</qWattsMin1><hour>19</hour><qWattsMin1>17.1905</qWattsMin1></bank><bank><dayofweek>1</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>19.1071</qWattsMin1><hour>9</hour><qWattsMin1>98.8824</qWattsMin1><hour>10</hour><qWattsMin1>171.5349</qWattsMin1><hour>11</hour><qWattsMin1>177.8000</qWattsMin1><hour>12</hour><qWattsMin1>157.7500</qWattsMin1><hour>13</hour><qWattsMin1>249.1778</qWattsMin1><hour>14</hour><qWattsMin1>230.9592</qWattsMin1><hour>15</hour><qWattsMin1>222.0250</qWattsMin1><hour>16</hour><qWattsMin1>194.1154</qWattsMin1><hour>17</hour><qWattsMin1>153.2245</qWattsMin1><hour>18</hour><qWattsMin1>57.7674</qWattsMin1><hour>19</hour><qWattsMin1>9.1429</qWattsMin1><dayofweek>2</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>25.3429</qWattsMin1><hour>9</hour><qWattsMin1>98.4750</qWattsMin1><hour>10</hour><qWattsMin1>187.7143</qWattsMin1><hour>11</hour><qWattsMin1>212.1951</qWattsMin1><hour>12</hour><qWattsMin1>220.5714</qWattsMin1><hour>13</hour><qWattsMin1>196.6977</qWattsMin1><hour>14</hour><qWattsMin1>235.4595</qWattsMin1><hour>15</hour><qWattsMin1>171.4000</qWattsMin1><hour>16</hour><qWattsMin1>155.8182</qWattsMin1><hour>17</hour><qWattsMin1>113.0313</qWattsMin1><hour>18</hour><qWattsMin1>60.9189</qWattsMin1><hour>19</hour><qWattsMin1>9.3250</qWattsMin1><dayofweek>3</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>11.7778</qWattsMin1><hour>9</hour><qWattsMin1>51.1489</qWattsMin1><hour>10</hour><qWattsMin1>173.3077</qWattsMin1><hour>11</hour><qWattsMin1>221.7500</qWattsMin1><hour>12</hour><qWattsMin1>187.8140</qWattsMin1><hour>13</hour><qWattsMin1>157.3019</qWattsMin1><hour>14</hour><qWattsMin1>202.3200</qWattsMin1><hour>15</hour><qWattsMin1>192.2432</qWattsMin1><hour>16</hour><qWattsMin1>189.8205</qWattsMin1><hour>17</hour><qWattsMin1>122.4000</qWattsMin1><hour>18</hour><qWattsMin1>54.4894</qWattsMin1><hour>19</hour><qWattsMin1>8.2745</qWattsMin1><dayofweek>4</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>0.0000</qWattsMin1><hour>9</hour><qWattsMin1>32.7391</qWattsMin1><hour>10</hour><qWattsMin1>93.1064</qWattsMin1><hour>11</hour><qWattsMin1>220.1250</qWattsMin1><hour>12</hour><qWattsMin1>174.2549</qWattsMin1><hour>13</hour><qWattsMin1>212.5098</qWattsMin1><hour>14</hour><qWattsMin1>211.1111</qWattsMin1><hour>15</hour><qWattsMin1>195.0488</qWattsMin1><hour>16</hour><qWattsMin1>170.7368</qWattsMin1><hour>17</hour><qWattsMin1>68.9286</qWattsMin1><hour>18</hour><qWattsMin1>53.9375</qWattsMin1><hour>19</hour><qWattsMin1>6.5952</qWattsMin1><dayofweek>5</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>13.6207</qWattsMin1><hour>9</hour><qWattsMin1>50.6327</qWattsMin1><hour>10</hour><qWattsMin1>140.0196</qWattsMin1><hour>11</hour><qWattsMin1>194.3725</qWattsMin1><hour>12</hour><qWattsMin1>237.8491</qWattsMin1><hour>13</hour><qWattsMin1>222.7551</qWattsMin1><hour>14</hour><qWattsMin1>230.1200</qWattsMin1><hour>15</hour><qWattsMin1>214.2632</qWattsMin1><hour>16</hour><qWattsMin1>188.5965</qWattsMin1><hour>17</hour><qWattsMin1>129.2553</qWattsMin1><hour>18</hour><qWattsMin1>57.5556</qWattsMin1><hour>19</hour><qWattsMin1>5.5278</qWattsMin1><dayofweek>6</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>9.8605</qWattsMin1><hour>9</hour><qWattsMin1>43.2791</qWattsMin1><hour>10</hour><qWattsMin1>125.9250</qWattsMin1><hour>11</hour><qWattsMin1>221.8000</qWattsMin1><hour>12</hour><qWattsMin1>208.2245</qWattsMin1><hour>13</hour><qWattsMin1>197.6512</qWattsMin1><hour>14</hour><qWattsMin1>164.9800</qWattsMin1><hour>15</hour><qWattsMin1>170.2174</qWattsMin1><hour>16</hour><qWattsMin1>156.8113</qWattsMin1><hour>17</hour><qWattsMin1>129.7073</qWattsMin1><hour>18</hour><qWattsMin1>50.0962</qWattsMin1><hour>19</hour><qWattsMin1>7.5116</qWattsMin1><dayofweek>7</dayofweek><hour>7</hour><qWattsMin1>0.0000</qWattsMin1><hour>8</hour><qWattsMin1>12.9722</qWattsMin1><hour>9</hour><qWattsMin1>78.8913</qWattsMin1><hour>10</hour><qWattsMin1>176.9756</qWattsMin1><hour>11</hour><qWattsMin1>218.3824</qWattsMin1><hour>12</hour><qWattsMin1>217.9143</qWattsMin1><hour>13</hour><qWattsMin1>207.3846</qWattsMin1><hour>14</hour><qWattsMin1>197.3590</qWattsMin1><hour>15</hour><qWattsMin1>192.5263</qWattsMin1><hour>16</hour><qWattsMin1>160.0323</qWattsMin1><hour>17</hour><qWattsMin1>101.8000</qWattsMin1><hour>18</hour><qWattsMin1>51.5714</qWattsMin1><hour>19</hour><qWattsMin1>7.9412</qWattsMin1></bank></site>
```
I'm meeting with Professor Skon this week to discuss next steps, hopefully sub-tabling, as well as with Jensen and Matt to some them how to use the code I've prepared.

## Week 3/26
This week I spent most of my time fixing up minor errors I've made along the way. For example, my array of all sites had to be defined by individually pushing in each site. In addition, I had to make sure that everything I was passing to my output was of type string (as some of the site functions I made were passing back doubles/ints instead of strings). Finally, I fixed the makefile and got it working. I then ran into the issue that the functions in my sites were not working for any of the sites I declared. I met with Professor Skon on 4/2 and attempted to resolve these issues. After an hour of looking at my code we discovered that for some reason my vector of sites was only taking in one site and then aborting the whole program. We tried many different attempted at discovering how this was happening and how to fix it but with no resolve. We are meeting again next week to discuss this issue again... Lastly, I met with Jensen to discuss the functions I've made and she has requested that I make a fourth function that receives the last 12 hour summaries of data for each site.

## Week 3/19
This week I finished the 3 querying functions in my sites class and formatted the output into XML. My sites.cpp file now looks like the following:
```{cpp}
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

//declaring all the sites
//note: is kind of weird at the moment; some are commented out and some of the bank array sizes don't match the number of banks 
sites::sites(){
  allSites={logCabins("Log Cabins",2000,2,["A43C8B0C4A","A43C8B0CD7"]),StAndrews("St. Andrews Primary", 1200, 2,["A43C8B0AB1","A43CE7BE69"]),VictNaz("Victorious Nazarene",1200,2,["A43C6DC4\
D2","A43CE7BE5E"])/*,Kings("Kings College", 800, 1,["A43C6DC5EB"])*/,TolChristian("Toledo Christian Academy", 800, 1,["A43C895C02"]),SanAntonio("San Antonio Primary", 1200, 1,["A43C6DC815"\
]),FaithNaz("Faith Nazarene", 1200, 1,["A43CE7BE78"])/*,SartenejaNaz("Sarteneja Nazarene", 1200, 1,["A43C6DC4C6"])*/,CorazolMethod("Corazol Methodist", 1200, 1,["A43CE7C04F"]),ACES("ACES",\
 1600, 2,["A43C8B0C4C","A43C8B0B9F"]),Brighter("Brighter Tomorrow", 800, 1,["A43CE7BE41"])/*,Kenyon("Kenyon Solar Demo", 600, 1,["A43C6DC810"])*/,Alvin("Alvin Young", 800, 1,["A43C6DC863"]\
),beloBap("Belopan Baptist High School", 800, 1,["A43CD10AAB"]),NewHorizons("New Horizons High School", 1600, 1,["A43C6DC860,A43C6DC5E5"]),SanPedro("San Pedro High School", 1600, 1,["A43C6\
DC854","A43C6DC5CC"])};
}

//user chooses unit, sitenumber and a date/time range to get results for
string sites::qByID(int sitenum,string wattsOrVolts,string timestamp1, string timestamp2){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

//now formatted in XML
  results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+allSites[sitenum].getMaxWatts()+"</maxWatts><numBanks>"+allSites[sitenum].getNumBanks()+"</numBanks><bank>");
  //want to make a new <bank> if the site has more than one bank
  for(int i=0;i<allSites[sitenum].getNumBanks();i++){
    stmt->execute("SELECT DATE(TimeStamp) AS DAY, HOUR(TimeStamp) as HOUR, AVG(Response) AS AVG FROM `Answers` WHERE IID = '"+allSites[sitenum].getBankIDs(i)+"' AND QID = '" + wattsOrVolts\
 +"' AND TimeStamp BETWEEN '"+timestamp1+"' AND '"+timestamp2+"' GROUP BY DAY,HOUR;");
    std::auto_ptr< sql::ResultSet> res;

    string lastDate="";
    string currentDate="";

    do{
      res.reset(stmt->getResultSet());
      while(res->next()){
        currentDate=res->getString("DAY");
        //only need to list date once
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

//user can query by unit and site number and will get information for the most recent week worth of collected data
string sites::lastWeek(int sitenum,string wattsOrVolts){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+allSites[sitenum].getMaxWatts()+"</maxWatts><numBanks>"+allSites[sitenum].getNumBanks()+"</numBanks><bank>");
  for(int i=0;i<allSites[sitenum].getNumBanks();i++){
    stmt->execute("SELECT DAYOFWEEK(TimeStamp) AS DAY,HOUR(TimeStamp) as HOUR,AVG(Response) AS AVG FROM `Answers` WHERE IID = '"+allSites[sitenum].getbankIDs(i)+"' AND QID = '" + wattsOrVo\
lts +"' AND YEARWEEK (TimeStamp) = YEARWEEK( current_date -interval 1 week ) GROUP BY DAY, HOUR;");

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

//user will choose a site and unit and the most recent data will be returned
string sites::latest(int sitenum, string wattsOrVolts){
  string results="";
 sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  results=("<site><name>"+allSites[sitenum].getSiteName()+"</name><maxWatts>"+allSites[sitenum].getMaxWatts()+"</maxWatts><numBanks>"+allSites[sitenum].getNumBanks()+"</numBanks><bank>");
  for(int i=0;i<allSites[sitenum].getNumBanks();i++){
    stmt->execute("SELECT TimeStamp, Response FROM `Answers` WHERE IID = '"+allSites[sitenum].getbankIDs(i)+"' AND QID = '"+wattsOrVolts+"' ORDER BY TimeStamp DESC LIMIT 1;");
    std::auto_ptr< sql::ResultSet> res;
    do{
      res.reset(stmt->getResultSet());
      while(res->next()){
        reults+=("<mostrecent>"+res->getString("TimeStamp")+"</mostrecent>");
        results+=("<"+wattsOrVolts+">"+res->getString("Response")+"</"+wattsOrVolts+">";
      }
    }while(stmt->getMoreResults());

  return results;
}

//gets most recent data for unit chosen for all sites and banks
string sites::latestForAll(string wattsOrVolts){
  string results="";
  for(int i=0;i<allSites.length();i++){
     results+=latest(i,wattsOrVolts);
  }
  return results;
}
```
Unfortunately I have been having issues compiling this code with my makefile. The errors state that "string" is not a type and that my definition of site.h is incorrect. both errors come from site.h, which is as follows:
```{cpp}
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include<string>
#include <vector>

#ifendef site_H
#define site_H

class site{
 public:
  site();
  site(string name,double mxW,int nBanks,string IDs[nBanks]);
  string getBankIDs(int i);
  int getNumBanks();
  double getMaxWatts();
 private:
  string sitename;
  int numBanks;
  string bankIDs[numBanks];
  double maxWatts;
};

#endif
```
So I am still trying to figure out what is going wrong with this section of the code. I also added the new sites to the database that were created this Spring break in Belize.
## Week 2/26
This week I have completed my C++ connection code and can now move forward with bulding in functions to my "sites" class. Some functions that I will be writing include:
* Query by site, unit, and time frame
* Return most recent site data
* Return site data for the past week
* Most likely more, need to talk with Jensen about her needs for pre-defined queries

Now that I have the connection working, I have rebuilt my layout of the classes a little to make site lookups easier for indivdual sites and as a whole over all the sites. The class sites now does not include individual sites name, max watts, number of banks and bank IDs. Instead it includes a vector of "site"s. Each site (a different class) now holds the site data. The Sites class will have the vector of all sites data, plus functions to query by individual sites and for all sites using the funcitons mentioned above.

I have started to work out the most recent site data function and the past week site data as shown below:
```{cpp}
string sites::lastWeek(int site,string wattsOrVolts){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  stmt->execute("SELECT AVG(Response) AS AVG, HOUR(TimeStamp) as HOUR, DAYOFWEEK(TimeStamp) \
AS DAY FROM `Answers` WHERE IID = '"+allSites[site].getbankIDs()+"' AND QID = '" + wattsOrVo\
lts +"' AND YEARWEEK (TimeStamp) = YEARWEEK( current_date -interval 1 week ) GROUP BY DAY, H\
OUR;");
  std::auto_ptr< sql::ResultSet> res;
  do{
    res.reset(stmt->getResultSet());
    while(res->next()){
      results=results+res->getString("AVG")+",";
      results+=res->getString("HOUR")+",";
      results+=res->getString("DAY")+";";
    }
  }while(stmt->getMoreResults());

  return results;
}

string sites:latest(int sites, string wattsOrVolts){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());

  stmt->execute("SELECT Response, TimeStamp FROM `Answers` WHERE IID = '"+allSites[site].get\
bankIDs()+"' AND QID = '"+wattsOrVolts+"' ORDER BY TimeStamp DESC LIMIT 1;");
  std::auto_ptr< sql::ResultSet> res;
  do{
    res.reset(stmt->getResultSet());
    while(res->next()){
      results+=res->getString("Response")+",";
      results+=res->getString("TimeStamp")+";";
    }
  }while(stmt->getMoreResults());

  return results;
}
```
In addition, I met with Matt and Jensen and we agreed that the best output of my query results would be in XML format, so I am not looking into how to return that to the front-end steps. Most likely I will have a string formatted in XML, since creating a new XML document for each new query would just be silly.

Next week I will be looking into XML formatting as well as (hopefully) finishing up my sites functions for querying.

## Week 2/19
This week I've been focusing on my C++ connection code still. I resolved last week's issue and I am storing all of the query results as one long string. This means that in the upcoming weeks I will need to write code that properly recognizes the seperate pieces of information in the string and formats it in a way that would be useful for Jensen's front-end work and Matt's analysis. I am thinking this will be a vector, but I am meeting with them next Tuesday to discuss some questions such as this. For now, I am using the string. The finished first-draft of the C++ sites file is shown below:
```{cpp}
#include <vector>
#include <iostream>
#include "sites.h"


sites::sites(){
}
sites::sites(string name,double mxW,int nBanks,vector<string> IDs){
  sitename=name;
  maxWatts=mxW;
  for(int i=0;i<IDs.size();i++){
    bankIDs[i]=IDs[i];
  }
  numBanks=nBanks;
}
string sites::qByID(string bankID){
  string results="";
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());
  std::auto_ptr< sql::ResultSet > res;
  stmt->execute("SELECT AVG(Response) AS AVG, HOUR(TimeStamp) as HOUR, DAYOFWEEK(TimeStamp) AS DAY FROM `Answers` WHERE IID = 'A43CE7BE5E' AND QID = 'qWattsMin1' AND YEARWEEK (TimeStamp) =\
 YEARWEEK( current_date -interval 1 week ) GROUP BY DAY, HOUR AS _message;");
  while(res->next()){
    results=results+res->getString("_message");
  }
  return results;
}
```
Besides fixing the getString and result adding portion by naming the output of the query as "\_message" and later calling that to add to the results string, I also realized that the last element of ID's in the sites class should be a vector of bank ID's (since different sites have a varying number of banks). Unfortunately I still have a few minor issues in the code that I am working through at the moment and am meeting with Skon again this week for a short meeting to check-in.

I also did some research on PHP after my presentation on Monday and the discussion that followed. Sam brought up two main points:
1. The servers run using what language/what is it capable of running
2. PHP offers the availability of implementing LAMP (a software bundle stack)
Regarding the server language, I met with Skon on Wednesday and he said that which ever language I chose for my database back-end, the server would be equally as capable of running it. I also did some research on LAMP stacks. LAMP stands for "Linux, Apache, MySQL, and PHP", which are the 4 open-sourced softwares that are used in a LAMP stack to build a web service. Linux is the operating system, Apache is the web server, MySQL is the DB server, and PHP is the CGI element. 

In the end, I had a discussion with professor Skon with these points, and we decided that C++ would still be the best for me to code in, because of the connection speed and the progress that I had already made in my program using C++.
## Week 2/12
This week I got access to the database and I have been exploring the layout as well as setting up a plan for the upcoming weeks. As well as exchanging emails with Skon,
I also met with him on Friday to discuss what interface was best to interact with the database. Note from that meeting can be found [here](https://docs.google.com/document/d/1uGr8fhwKfpG0WXRNelPcNLwHv2UV3NFk50r5TFiK3vE/edit?usp=sharing).

To access the database, I log onto the cslab.kenyon.edu server, then from the command line enter
"mysql -u braunk -h cs3.kenyon.edu -p" (since the database is on the cs3.kenyon.edu server I will
have to access it remotely). The name of the database is "LIM-SERV" ("USE LIM-SERV") and the table is "answers".
I also can access it from a C++ file, which I am currently working on accomplishing.

The program will include an .h file that declares a class called "site" which will hold several data
points, like site name, site ID, number of banks, and watt limit, as well as declare public functions
to interact/receive those data points. This .h file's declared functions will then be defined in a
similarly named .cpp file. *This* .cpp file holds most of the meat of the program, as this is where
the code connecting to the database and retrieving the data will be held. At the moment I am having
some difficulties with data type conversion from C++ and SQL.

Sites.h file is shown below:
```{cpp}
#include <stdlib.h>
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


#ifndef sites_H
#define sites_H

#define HOST "cs3.kenyon.edu"
#define USER "braunk"
#define DB "LIM-SERV"
//password taken out for journal entry use
#define PASS "*********************"

using namespace std;

class sites{
 public:
  site();
  site(string sitename,double maxWatts,int numBanks,string ID);
  //at first I only have one querying function set up that a user will type in a site ID and will get
  //random queried information (not very useable atm, only trying to test connection right now)
  string qByID(string ID);
  string sitename, ID;
  double maxWatts;
  int numBanks;
 private:
  const string url=HOST;
  const string user=USER;
  const string database=DB;
  const string pass=PASS;

};

#endif /* sites_H */
```

The corresponding **unfinished** cpp file is shown below:
```{cpp}
#include <vector>
#include <iostream>
#include "sites.h"


sites:sites(){
}
string sites::qByID(string ID){
  sql::Driver* driver = sql::mysql::get_driver_instance();
  std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
  con->setSchema(database);
  std::auto_ptr<sql::Statement> stmt(con->createStatement());
  stmt->excute("SELECT AVG(Response) AS AVG, HOUR(TimeStamp) as HOUR, DAYOFWEEK(TimeStamp) A\
S DAY FROM `Answers` WHERE IID = '"+ID+"' AND QID = 'qWattsMin1' AND YEARWEEK (TimeS\
tamp) = YEARWEEK( current_date -interval 1 week ) GROUP BY DAY, HOUR;");

  std::auto_ptr< sql::ResultSet > res;

//the trouble comes in here where I want to keep receiving all possible information but I am not sure how to do that/ how to continue to 
//store it all in a string then maybe later I should parse it so that the format is more desirable for use in the front-end products??

```
Professor Skon also sent me a PHP function that has the info on the sites. Each site is laid out as
site(Site name, Maximum watts, number of banks, list of ID's for each bank):
```{php}
function initSites() {
    $ListOfSites[] = new site("Log Cabins",  1500, 2, ["A43C8B0C4A", "A43C8B0CD7"]);
    $ListOfSites[] = new site("St. Andrews Primary", 1500, 2, ["A43C8B0AB1","A43CE7BE69"]);
    $ListOfSites[] = new site("Victorious Nazarene", 800, 2, ["A43C6DC4D2","A43CE7BE5E"]);
    $ListOfSites[] = new site("Kings College", 800, 1, ["A43C6DC5EB"]);
    $ListOfSites[] = new site("Toledo Christian Academy", 800, 1, ["A43C895C02"]);
    $ListOfSites[] = new site("San Antonio Primary", 1200, 1, ["A43C6DC815"]);
    $ListOfSites[] = new site("Faith Nazarene", 1200, 1, ["A43CE7BE78"]);
    $ListOfSites[] = new site("Sarteneja Nazarene", 1200, 1, ["A43C6DC4C6"]);
    $ListOfSites[] = new site("Corazol Methodist", 1200, 1, ["A43CE7C04F"]);
    $ListOfSites[] = new site("ACES", 1500, 2, ["A43C8B0C4A","A43C8B0B9F"]);
    $ListOfSites[] = new site("Brighter Tomorrow", 600, 1, ["A43CE7BE41"]);
    $ListOfSites[] = new site("Kenyon Solar Demo", 600, 1, ["A43C6DC810"]);
    return $ListOfSites;
```
## Week 2/5
I met with Skon on Wednesday to discuss specifics of the project. I've attached my notes from the meeting [here](https://docs.google.com/document/d/1XKVftr6rIlWVmV-PFqNADGkpmC3KiHxBjyMyz9n8Rs8/edit?usp=sharing). Some things that I will need to think about more post-meeting are:
* What sort of queries need to be performed and in what way can I figure out how this queries interact and optimize search results to minimize querying repetition
* How to **only** access the solar panel data, now that I am aware that it sits on the same database table as an abundance of irrelavent data
* Research more about caching (this is a topic that I have never worked with before) and new tables for site specific data

As of Sunday, Professor Skon has still not been able to get me access to the database, or a subset of the database, due to being out-of-state. Hopefully I will have it by tomorrow Monday, February 12th. For now, I have done some research on MySQL Query Cache feature.
The MySQL Query Cache's effectiveness is very dependent on the type of data and queries being performed. For example, databases that are constantly being updated, such as databases with a time-element, for the most part it is counterproductive to cache the queries performed on that database, since the results from the previous queries will all be outdated. Because the database I will be managing is clearly being updated frequently (once every minute), I will need to research how to minimize querying time using caching without storing massive amounts of query results that will never be needed again. I believe this will involve using automatically updating subtables in conjunction with caching. Lastly I logged into my phpMyadmin account on the cslab server to refresh myself with the interface and writing/saving procedures as well as the C++ code I used to pull data from the database, as follows:

```cpp
try {

    sql::Driver* driver = sql::mysql::get_driver_instance();
//line below connects to the database located at a pre-defined url using a pre-defined username and password (named user & pass)
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());
//line below calls to a pre-defined procedure in MySQL named "find_last" and passes the procedure the name "lastMatch"
    stmt->execute("CALL find_last('%"+lastMatch+"%')");
    std::auto_ptr< sql::ResultSet > res;
//continues to get all the possible results in the database
    do {
      res.reset(stmt->getResultSet());
      while (res->next()) {
        cout << res->getString("First") << " "
             << res->getString("Last") << " "
             << res->getString("Phone") << " "
             << res->getString("Type")
             << endl;
      }
    } while (stmt->getMoreResults());
  } catch (sql::SQLException &e) {
        /*
          MySQL Connector/C++ throws three different exceptions:

          - sql::MethodNotImplementedException (derived from sql::SQLException)
          - sql::InvalidArgumentException (derived from sql::SQLException)
          - sql::SQLException (derived from std::runtime_error)
 cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    /* what() (derived from std::runtime_error) fetches error message */
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;

    return EXIT_FAILURE;
  }
```
## Week 1/29
This week Matt, Jensen, and I ironed out who will be working on which sections of the project. We have decied the most logical way to work is to have me work on backend (mostly database management), Matt do data analysis, and Jensen do website visualizations. In addition, we met with Skon and worked on a rough draft [list of requirements for the project](https://docs.google.com/document/d/1XWqd5NIhoF1ryyyDD_2VsPwRrSpgEWXdVBVjxH6XMO4/edit?usp=sharing), as well as finished the [project proposal](https://docs.google.com/document/d/1EHq-PF2LkekZ6_t8fIX1WRgX5D-BSFJQ1DhFqK_1TBY/edit?usp=sharing) and preparing a 45 minute interactive [presentation](https://docs.google.com/presentation/d/1kZP0jXcm2uxT3m3x_Rm_kB_gCOMG2oKM6gRh_aI8YIw/edit?usp=sharing) to inform our classmates of what we will be attempting to accomplish this semester.
