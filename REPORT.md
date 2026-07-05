# Contact Management System — Project Report

**Author:** Jelius Heneriko
**Language:** C
**Open-source library used:** SQLite (public domain)

---

## 1. Nature of the Project

The Contact Management System is a menu-driven command-line application
written in C. It lets a user keep a personal address book on disk. The
program supports the four operations that any real address book needs:

1. **Add** a contact (name, phone, email)
2. **List** all contacts (sorted by name)
3. **Search** contacts by name (case-insensitive, partial match)
4. **Delete** a contact by its id

All data is stored in a real relational database file (`contacts.db`), so
the contacts survive between runs of the program.

---

## 2. Open-Source Library and Attribution

The project uses **SQLite**, an embedded SQL database engine.

- **Website / source:** https://sqlite.org
- **Licence:** Public Domain (no restrictions on use)
- **Form used:** the official *amalgamation* — a single source file
  `sqlite3.c` and its header `sqlite3.h`, downloaded from
  https://www.sqlite.org/download.html

The amalgamation is compiled directly into the executable, so the finished
program needs no external database server or extra installation. SQLite is
the intellectual property of its authors (D. Richard Hipp and contributors);
it is included here unmodified and credited in both this report and the
header comment of `contacts.c`.

---

## 3. Design Choices

**Why SQLite instead of plain files?**
A flat text file would force me to write my own parsing, searching and
updating logic. SQLite gives durable storage, sorting and searching for
free through SQL, while still being a single bundled file with zero setup.
This keeps my own code short and reliable — a key requirement of the task.

**Why a single C file?**
The whole application logic lives in `contacts.c` (about 200 lines). This
makes the program easy to read and grade. Each feature is its own small
function (`add_contact`, `list_contacts`, `search_contacts`,
`delete_contact`), and shared work is factored into helpers (`input`,
`print_rows`).

**Security — prepared statements.**
Every query that takes user input uses SQLite *prepared statements* with
bound parameters (`sqlite3_bind_text` / `sqlite3_bind_int`) instead of
building SQL strings by hand. This prevents SQL-injection and correctly
handles names containing quotes.

**Safe input handling.**
User text is read with `fgets` into fixed-size buffers, and the trailing
newline is stripped. This avoids the classic buffer-overflow risk of
`scanf("%s")` / `gets`.

**Database schema.**

| Column | Type    | Notes                       |
|--------|---------|-----------------------------|
| id     | INTEGER | primary key, auto-increment |
| name   | TEXT    | required                    |
| phone  | TEXT    | optional                    |
| email  | TEXT    | optional                    |

---

## 4. How to Build and Run

```
make          # compiles contacts.c + sqlite3.c into ./contacts
./contacts    # run the program
make clean     # remove the binary and the database file
```

The program then shows a numbered menu; type a number and press Enter.

---

## 5. File Listing

| File         | Purpose                                             |
|--------------|-----------------------------------------------------|
| `contacts.c` | The complete application (my own code).             |
| `sqlite3.c`  | Bundled SQLite library — public domain (sqlite.org).|
| `sqlite3.h`  | SQLite public header — public domain (sqlite.org).  |
| `Makefile`   | Build script.                                       |
| `REPORT.md`  | This report.                                        |

---

## 6. References

1. SQLite Home Page. https://sqlite.org (accessed 2026).
2. SQLite Amalgamation / Download page. https://www.sqlite.org/download.html
3. SQLite C/C++ Interface documentation. https://www.sqlite.org/c3ref/intro.html
