# Build the Contact Management System.
# sqlite3.c is the bundled SQLite amalgamation (public domain, sqlite.org).

CC     = gcc
CFLAGS = -Wall -O2
LDLIBS = -lpthread -ldl -lm

contacts: contacts.c sqlite3.c
	$(CC) $(CFLAGS) -o contacts contacts.c sqlite3.c $(LDLIBS)

clean:
	rm -f contacts contacts.db
