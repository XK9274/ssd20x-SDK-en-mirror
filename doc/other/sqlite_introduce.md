<!--
  * @Author: Flying
  * @Date: 2021-12-16 10:47:48
  * @LastEditors: Flying
  * @LastEditTime: 2021-12-26 00:46:14
  * @Description: Create a new file
-->

# SQLite basic concepts and usage overview

- Introduced based on SSD platform
  
## 1. What is SQL?

- SQL stands for Structured Query Language
- SQL gives us the ability to access the database
- SQL is an ANSI standard computer language used to access and operate database systems. SQL statements are used to retrieve and update data in the database. SQL works with database programs such as MS Access, DB2, Informix, MS SQL Server, Oracle, Sybase and other database systems.

- Unfortunately, there are many different versions of the SQL language, but in order to be compatible with the ANSI standard, they must jointly support some major keywords (such as SELECT, UPDATE, DELETE, INSERT, WHERE, etc.) in a similar way ).
  
## 2. What is a database?

- A database is a warehouse where data is stored.
- A database is a computer software system that stores and manages data in a data structure. The concept of database actually includes two meanings.
   - (1) A database is an entity. It is a "warehouse" that can reasonably store data. Users store transaction data to be managed in this "warehouse". The two concepts of "data" and "library" are combined into a database.
   - (2) Database is a new method and technology for data management. It can organize data more appropriately, maintain data more conveniently, control data more closely and utilize data more effectively.
  
## 3. What is SQLite

- SQLite is a C language library that implements a small, fast, self-contained, highly reliable, full-featured SQL database engine. SQLite is the most used database engine in the world. SQLite is built into all mobile phones and most computers, and bundled with countless other applications that people use every day.
- SQLite is a software library that implements a self-sufficient, serverless, zero-configuration, transactional SQL database engine. SQLite is the most widely deployed SQL database engine in the world. SQLite source code is not subject to copyright restrictions.
- The SQLite file format is stable, cross-platform, and backwards compatible, and the developers promise to stay that way until 2050. SQLite database files are commonly used as containers for transferring rich content between systems and as long-term archiving formats for data. There are over 1 trillion (1e12) SQLite databases in active use.

## 4. Why use SQLite?

- Resources are limited on Linux arm, and several methods are used when data needs to be saved.
  
### 4.1. Thinking

- Need to save 3 accounts, passwords and personalized signatures. How to store on Linux arm (when storing, you need to consider how to reasonably add, delete, modify, and check)
  
   ```shell
   1001 abc123 Personalized signature 123
   1002 abc456 personalized signature 456
   1003 abc789 personalized signature 789
   ```

### 4.2. Save through text (fopen...)

#### 4.2.1, ini format storage

   ```ini
   [User 1]
   id = 1001;
   passwd = abc123;
   other = personalized signature 123;
   [User 2]
   id = 1002;
   passwd = abc456;
   other = personalized signature 456;
   [User 3]
   id = 1003;
   passwd = abc789;
   other = personalized signature 789;
   ```

- Store according to certain specifications and can be easily expanded

#### 4.2.2, csv format storage

   ```c
   id,passwd,other
   1001,"abc123","Personal signature 123"
   1002,"abc456","Personal signature 456"
   1003,"abc789","Personal signature 789"
   ```
  
- Store according to certain specifications and can be easily expanded
  
#### 4.2.3, json format storage

   ```json
   {
     "User 1":{
           "id":1001,
           "passwd":"abc123",
           "other":"Personal signature 123"
       },
     "User 2":{
           "id":1002,
           "passwd":"abc456",
           "other":"Personal signature 789"
       },
     "User 3":{
           "id":1003,
           "passwd":"abc789",
           "other":"Personal signature 789"
       },
   }
   ```
  
- Store according to certain specifications and can be easily expanded

#### 4.2.4. Save data directly

- Directly save the original data as a string
  
   ```shell
   1001 abc123 Personalized signature 123
   1002 abc456 personalized signature 456
   1003 abc789 personalized signature 789
   ```

- When reading, read according to the original data rules.
- When writing data, you need to calculate the cursor position that needs to be modified. It is also necessary to move the modified position back and then rewrite the data.
  
- If you need to add a column of "Registration Time", you need to re-modify the data reading rules.
  
#### 4.2.5. Summary

Directly storing data with the text listed above has the following problems:

- The method of directly storing text will be troublesome when adding, deleting or modifying.
- When operating in ini or csv mode, if you insert or delete data from it, you need to read the inserted data, insert or modify it, and then rewrite the file.
- json, save the original data directly. When adding, deleting or modifying, you need to read out all the data. After the modification is completed, re-write the data.
- The speed is slower when operating large files. If the device is suddenly powered off during operation, all data will be lost.
- **Text saving method is suitable for data storage that rarely needs to be modified: such as configuration files, etc.**

## 5. SQLite advantages

- Lightweight: low resource usage (less than 400KiB when fully configured, less than 250KiB when optional function configuration is omitted)
- Written in pure C, easy to transplant
- Published in the public domain (Public Domain);

## 6. SQLite3 download and compile lib

### 6.1. Install sqlite command on ubuntu

- Install sqlite3 command `sudo apt-get install sqlite3`
- Install the sqlite3 header file `sudo apt-get install libsqlite3-dev`

### 6.2. Download

- Direct download from sqlite official website https://www.sqlite.org/
- You can download it directly through wget under ubuntu `wget https://www.sqlite.org/snapshot/sqlite-snapshot-202107191400.tar.gz`

### 6.2 Decompression, configuration and compilation

```shell
#
tar -zxvf sqlite-snapshot-202107191400.tar.gz
cd sqlite-snapshot-202107191400/
mkdir build
./configure CC=arm-linux-gnueabihf-gcc --host=arm-linux --prefix=$PWD/build
make -j8
make install
```

## 7. SQLite3 command line operation

- Environment: ubuntu
- If you enter a non-dot (`.`) command, it ends with a semicolon (`;`)
- **shell command**
- Enter the `sqlite3` command to enter the sqlite3 prompt

sqlite3 prompt command | Description | Example
---------|---------- | ----------
.exit | Exit sqlite3 interaction | \
.quit | Exit sqlite3 interaction | \
.help | show dot command help | \
.databases | List the names of databases and their attached files | \
.show | View the default settings for the SQLite command prompt | \
CREATE |Create table| CREATE TABLE test_table (id integer, passwd text, other text);
.schema | View all table structures | \
INSERT | Insert data |INSERT INTO test_table (id, passwd, other) VALUES (1001, "abc123", "Personal signature 123");
SELECT | Query data | SELECT * FROM test_table;
UPDATE | Modify data | UPDATE test_table SET passwd = "abc1234" WHERE id = 1001;
DELETE | Delete data | DELETE FROM test_table WHERE id = 1001;

- Operation examples

```c
sqlite3 test.db
CREATE TABLE test_table (id integer ,passwd text, other text);
INSERT INTO test_table (id,passwd,other) VALUES(1001,"abc123","Personal signature 123");
INSERT INTO test_table VALUES(1002,"abc456","Personal signature 456"), (1003,"abc789","Personal signature 789");
SELECT * FROM test_table;
INSERT INTO test_table VALUES(1004,"smc-xm","smc other");
SELECT * FROM test_table;
UPDATE test_table SET passwd = "cccccc" WHERE id = 1004;
SELECT * FROM test_table;
DELETE FROM test_table WHERE id = 1004;
SELECT * FROM test_table;
```

![Operation](https://gitee.com/mFlying/flying_picgo_img/raw/master/sqlite_test.png)

## 8. SQLite common statements

- Basic operations in database operations: add, delete, modify, and query.

### 8.1 CREATE TABLE statement

- Create table

```sqlite3
CREATE TABLE table_name(
    column1 datatype,
    column2 datatype,
    column3 datatype,
    .....
    columnN datatype,
    PRIMARY KEY(one or more columns)
);
```

### 8.2 INSERT INTO statement

- Insert data

```sqlite3
INSERT INTO table_name( column1, column2....columnN)
VALUES ( value1, value2....valueN);
```

### 8.3 DELETE statement

- delete data

```sqlite3
DELETE FROM table_name
WHERE {CONDITION};
```

### 8.4 UPDATE statement

- Modify/update data

```sqlite3
UPDATE table_name
SET column1 = value1, column2 = value2....columnN=valueN
[ WHERE CONDITION ];
```

### 8.5 SELECT statement

- Modify/update data

```sqlite3
SELECT column1, column2....columnN
FROM table_name;
```

## 9. SQLite syntax

- An important point to note is that SQLite is not case-sensitive, but there are also some commands that are case-sensitive. For example, GLOB and glob have different meanings in SQLite statements.

- All SQLite statements can start with any keyword, such as SELECT, INSERT, UPDATE, DELETE, ALTER, DROP, etc., and all statements end with a semicolon;

- Support arithmetic operators (+ - * / %)
- Support comparison operators (== != > <…)
-Support logical operators (AND OR NOT IN...)
- Supports bitwise operators (& | ~ << >>)

- type of data

storage class | description
----------|----------
  NULL | value is a NULL value.
  INTEGER | The value is a signed integer stored in 1, 2, 3, 4, 6, or 8 bytes depending on the size of the value.
  REAL | The value is a floating point value stored as an 8-byte IEEE floating point number.
  TEXT | The value is a text string stored using the database encoding (UTF-8, UTF-16BE, or UTF-16LE).
  BLOB | Binary

## 10. SQLite C sample code

### 10.1. Use SQL statements to simply call C code to use DMEO

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// sqlite3_exec callback function, after executing the sql statement, the callback function will be called when the content is obtained (such as SELECT statement)
int callback(void *data, int ncols, char **values, char **headers)
{
     int i;
     fprintf(stderr, "%s : ", (char *)data);
     for (i = 0; i < ncols; i++)
     {
         fprintf(stderr, "%s=%s ", headers[i], values[i]);
     }
     fprintf(stderr, "\n");
     return 0;
}

int main(int argc, char *argv[])
{
     //Open the database or create a database
     sqlite3 *db;
     char *err;
     int rc = sqlite3_open("./test.db", &db);
     if(rc)
     {
         fprintf(stderr, "Cannot open the database, the error is as follows: %s\n", sqlite3_errmsg(db));
         return -1;
     }

     //Execute sql statement
     struct sqlbuff_t
     {
         char *sql;
         int (*callback)(void *, int, char **, char **);
         void *data;
     } sqlbuff[] = {
         {"CREATE TABLE test_table (id integer PRIMARY KEY ,passwd text, other text);", NULL, NULL},
         {"INSERT INTO test_table (id,passwd,other) VALUES(1001,'abc123','Personal signature 123');", NULL, NULL},
         {"INSERT INTO test_table VALUES(1002,'abc456','Personalized signature 456'), (1003,'abc789','Personalized signature 789');", NULL, NULL},
         {"SELECT * FROM test_table;", callback, (void *)"First query callback"},
         {"INSERT INTO test_table VALUES(1004,'smc-xm','smc other');", NULL, NULL},
         {"SELECT * FROM test_table;", callback, (void *)"Query after adding data"},
         {"UPDATE test_table SET passwd = 'cccccc' WHERE id = 1004;", NULL, NULL},
         {"SELECT * FROM test_table;", callback, (void *)"Query after modifying data"},
         {"DELETE FROM test_table WHERE id = 1004;", NULL, NULL},
         {"SELECT * FROM test_table;", callback, (void *)"Query after deleting data"}};

     for (int i = 0; i < sizeof(sqlbuff) / sizeof(sqlbuff[0]); i++)
     {
         rc = sqlite3_exec(db, sqlbuff[i].sql, sqlbuff[i].callback, sqlbuff[i].data, &err);
         if (rc != SQLITE_OK)
         {
             if (err)
             {
                 fprintf(stderr, "SQL error: %s\n", err);
                 sqlite3_free(err);
             }
         }
     }
     sqlite3_close(db);
     return 0;
}
```

- Results of the:

![Execute](https://gitee.com/mFlying/flying_picgo_img/raw/master/sqlite_test1.png)

## 11. SQLite C common API

- An Introduction To The SQLite C/C++ Interface https://www.sqlite.org/cintro.html

### 11.1. Open the database

```c
int sqlite3_open(
   const char *filename, /* Database filename (UTF-8) */
   sqlite3 **ppDb /* OUT: SQLite db handle */
);
int sqlite3_open16(
   const void *filename, /* Database filename (UTF-16) */
   sqlite3 **ppDb /* OUT: SQLite db handle */
);
int sqlite3_open_v2(
   const char *filename, /* Database filename (UTF-8) */
   sqlite3 **ppDb, /* OUT: SQLite db handle */
   int flags, /* Flags */
   const char *zVfs /* Name of VFS module to use */
);
```

### 11.2. Execute database statements

```c
int sqlite3_exec(
   sqlite3*, /* An open database */
   const char *sql, /* SQL to be evaluated */
   int (*callback)(void*,int,char**,char**), /* Callback function */
   void *, /* 1st argument to callback */
   char **errmsg /* Error msg written here */
);
```

### 11.3. Close the database

```c
int sqlite3_close(sqlite3*);
int sqlite3_close_v2(sqlite3*);
```

### 11.4. Release the resources requested internally by sqlite3

```c
void sqlite3_free(void*);
```

### 11.5. Return error information during sqlite3 execution

```c
char *sqlite3_errmsg(sqlite3*);
```

### 11.6. Others

- sqlite3_get_table
- sqlite3_prepare
- sqlite3_column
- sqlite3_bind
- sqlite3_step
-…

## 12. Resources

- sqlite3
   - Official website: `https://www.sqlite.org/index.html`
- SQLiteC++ provides an encapsulation of SQLite's native C API and provides some intuitive and well-documented C++ classes.
   - Source code path: `https://github.com/SRombauts/SQLiteCpp`
- sqlitestudio (SQLite database management tool)
   - Official website: `https://sqlitestudio.pl/`
   - Source code path: `https://github.com/pawelsalawa/sqlitestudio.git`

## 13. Commonly used advanced SQLite

### 13.1、PRAGMA

- SQLite's PRAGMA command is a special command that can be used to control various environment variables and status flags within the SQLite environment. A PRAGMA value can be read and set as required.
- eg: encoding Pragma controls how strings are encoded and stored in database files

### 13.2. Constraints

- Constraints are rules that are enforced on the data columns of a table. These are used to limit the types of data that can be inserted into the table. This ensures the accuracy and reliability of the data in the database.
- eg: Limit id cannot be empty `NO NULL`

### 13.3. Alias

- A table or column can be temporarily renamed to another name, which is called an alias. Using a table alias means renaming a table within a specific SQLite statement. Renaming is a temporary change and the actual table name in the database does not change.
- eg: There are two tables, both of which have ID fields. You need to use a SQL statement to query and print.

### 13.4. Trigger

- SQLite trigger (Trigger) is a callback function of the database, which will automatically execute/call when a specified database event occurs.
- eg: In a smart home, there are scene tables and device tables. When deleting a device, you need to delete the contents of the device in the scene table simultaneously.

### 13.5. Transaction

- Transaction is a unit of work performed on the database
- eg: guaranteed data
Database integrity. When there are too many SQL statements, data may be incomplete due to device power outage. Data integrity can be ensured through transaction processing.
