USER= braunk

CC= g++

CFLAGS= -std=c++11  -Wno-deprecated-declarations

RM= /bin/rm -f

all: TestDBquery

site.o: site.h site.cpp
        $(CC) -c $(CFLAGS) site.cpp

sites.o: sites.h sites.cpp
        $(CC) -c $(CFLAGS) sites.cpp

TestDBquery.o: TestDBquery.cpp
        $(CC) -c $(CFLAGS) TestDBquery.cpp

TestDBquery: TestDBquery.o sites.o site.o
        $(CC) $(CFLAGS) TestDBquery.o sites.o site.o -L/usr/lib -o TestDBquery -L/usr/local/\
lib -lcgicc -lmysqlcppconn
