/*
 * Contact Management System
 * -------------------------
 * A small menu-driven command-line application that stores personal
 * contacts (name, phone, email) in a persistent SQLite database.
 *
 * Open-source library used:
 *   SQLite (public domain) - https://sqlite.org
 *   The library is bundled as the official "amalgamation" (sqlite3.c /
 *   sqlite3.h) and compiled directly into this program. See the project
 *   report for full attribution.
 *
 * Author: Jelius Heneriko
 * Course final project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define DB_FILE "contacts.db"
#define BUF 128

static sqlite3 *db;   /* global database handle, opened in main() */

/* Read a line of text from the user into buf and strip the trailing '\n'. */
static void input(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';   /* remove newline left by fgets */
}

/* Create the contacts table on first run (id is auto-assigned). */
static void init_db(void)
{
    const char *sql =
        "CREATE TABLE IF NOT EXISTS contacts ("
        "  id    INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  name  TEXT NOT NULL,"
        "  phone TEXT,"
        "  email TEXT);";
    char *err = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", err);
        sqlite3_free(err);
        exit(1);
    }
}

/* Add a new contact using a parameterised statement (prevents SQL injection). */
static void add_contact(void)
{
    char name[BUF], phone[BUF], email[BUF];
    input("Name : ", name, BUF);
    input("Phone: ", phone, BUF);
    input("Email: ", email, BUF);

    if (name[0] == '\0') {
        printf("Name cannot be empty.\n");
        return;
    }

    const char *sql = "INSERT INTO contacts (name, phone, email) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Prepare failed: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_text(stmt, 1, name,  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, phone, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, email, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE)
        printf("Contact added (id %lld).\n", (long long)sqlite3_last_insert_rowid(db));
    else
        fprintf(stderr, "Insert failed: %s\n", sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
}

/* Print every row returned by the given prepared statement as a table. */
static void print_rows(sqlite3_stmt *stmt)
{
    int found = 0;
    printf("\n%-4s %-20s %-16s %-25s\n", "ID", "NAME", "PHONE", "EMAIL");
    printf("--------------------------------------------------------------------\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%-4d %-20s %-16s %-25s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2) ? sqlite3_column_text(stmt, 2) : (const unsigned char *)"",
               sqlite3_column_text(stmt, 3) ? sqlite3_column_text(stmt, 3) : (const unsigned char *)"");
        found = 1;
    }
    if (!found)
        printf("(no contacts)\n");
    printf("\n");
}

/* List all contacts ordered by name. */
static void list_contacts(void)
{
    const char *sql = "SELECT id, name, phone, email FROM contacts ORDER BY name;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        return;
    }
    print_rows(stmt);
    sqlite3_finalize(stmt);
}

/* Search contacts whose name contains the typed text (case-insensitive). */
static void search_contacts(void)
{
    char term[BUF];
    input("Search name: ", term, BUF);

    char like[BUF + 2];
    snprintf(like, sizeof(like), "%%%s%%", term);   /* wrap in % wildcards */

    const char *sql =
        "SELECT id, name, phone, email FROM contacts "
        "WHERE name LIKE ? COLLATE NOCASE ORDER BY name;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_text(stmt, 1, like, -1, SQLITE_TRANSIENT);
    print_rows(stmt);
    sqlite3_finalize(stmt);
}

/* Delete a contact by its numeric id. */
static void delete_contact(void)
{
    char idbuf[BUF];
    input("Delete id: ", idbuf, BUF);

    const char *sql = "DELETE FROM contacts WHERE id = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Query failed: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_int(stmt, 1, atoi(idbuf));
    if (sqlite3_step(stmt) == SQLITE_DONE)
        printf("Deleted %d row(s).\n", sqlite3_changes(db));
    else
        fprintf(stderr, "Delete failed: %s\n", sqlite3_errmsg(db));
    sqlite3_finalize(stmt);
}

/* Show the menu and return the user's choice. */
static int menu(void)
{
    char choice[BUF];
    printf("==== Contact Manager ====\n");
    printf("1. Add contact\n");
    printf("2. List contacts\n");
    printf("3. Search contacts\n");
    printf("4. Delete contact\n");
    printf("5. Quit\n");
    input("Choose: ", choice, BUF);
    return atoi(choice);
}

int main(void)
{
    if (sqlite3_open(DB_FILE, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    init_db();

    int running = 1;
    while (running) {
        switch (menu()) {
            case 1: add_contact();     break;
            case 2: list_contacts();   break;
            case 3: search_contacts(); break;
            case 4: delete_contact();  break;
            case 5: running = 0;       break;
            default: printf("Invalid choice.\n");
        }
    }

    sqlite3_close(db);
    printf("Goodbye.\n");
    return 0;
}
