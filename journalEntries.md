# Journal Entries 
## Week 1/29
This week Matt, Jensen, and I ironed out who will be working on which sections of the project. We have decied the most logical way to work is to have me work on backend (mostly database management), Matt do data analysis, and Jensen do website visualizations. In addition, we met with Skon and worked on a rough draft [list of requirements for the project](https://docs.google.com/document/d/1XWqd5NIhoF1ryyyDD_2VsPwRrSpgEWXdVBVjxH6XMO4/edit?usp=sharing), as well as finished the [project proposal](https://docs.google.com/document/d/1EHq-PF2LkekZ6_t8fIX1WRgX5D-BSFJQ1DhFqK_1TBY/edit?usp=sharing) and preparing a 45 minute interactive [presentation](https://docs.google.com/presentation/d/1kZP0jXcm2uxT3m3x_Rm_kB_gCOMG2oKM6gRh_aI8YIw/edit?usp=sharing) to inform our classmates of what we will be attempting to accomplish this semester.
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
## Week 2/12
This week I got access to the database and I have been exploring the layout as well as setting up a plan for the upcoming weeks. As well as exchanging emails with Skon,
I also met with him on Friday to discuss what interface was best to interact with the database. Note from that meeting can be found [here]().

To access the database, I log onto the cslab.kenyon.edu server, then from the command line enter
"mysql -u braunk -h cs3.kenyon.edu -p" (since the database is on the cs3.kenyon.edu server I will
have to access it remotely). The name of the database is "LIM-SERV" and the table is "answers".
I also can access it from a C++ file (as shown below):
```{cpp}
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
