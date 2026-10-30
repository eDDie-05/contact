# Contact Management System — C and SQLite

A menu-driven command-line contact manager written in C. It stores contact names, phone numbers and email addresses in a local SQLite database.

## Features visible in the source
- Create the contacts table on first run
- Add contacts using parameterized SQLite statements
- Persistent local database storage
- Menu-driven command-line interface

Review the source before relying on additional operations or data-management features.

## Requirements
- GCC or another C compiler
- Make
- SQLite amalgamation files included in the repository (`sqlite3.c` and `sqlite3.h`)

## Build and run
```bash
make
```

Run the executable produced by the Makefile (check the Makefile for its exact output name).

## Main files
- `contacts.c` — application logic
- `sqlite3.c`, `sqlite3.h` — bundled SQLite library
- `Makefile` — build instructions
- `contacts.db` — local database file currently present in the repository

## Privacy and repository hygiene
A contacts database and an additional data file are currently committed. Before keeping this repository public, confirm that they contain only synthetic test data. Never publish real people's names, phone numbers, email addresses or other personal information. For future commits, keep runtime database files out of version control and provide a safe sample database instead.

## Attribution
SQLite is public-domain software. See the official project at https://sqlite.org and the repository's `REPORT.md` for the bundled version and attribution details.
