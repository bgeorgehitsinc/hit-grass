#ifndef DBSTUBS_H
#define DBSTUBS_H

extern int db__driver_add_column(dbString *, dbColumn *);
extern int db__driver_bind_update(dbCursor *);
extern int db__driver_close_cursor(dbCursor *);
extern int db__driver_close_database(void);
extern int db__driver_create_index(dbIndex *);
extern int db__driver_create_table(dbTable *);
extern int db__driver_create_database(dbHandle *);
extern int db__driver_delete(dbCursor *);
extern int db__driver_delete_database(dbHandle *);
extern int db__driver_describe_table(dbString *, dbTable **);
extern int db__driver_drop_column(dbString *, dbString *);
extern int db__driver_drop_index(dbString *);
extern int db__driver_drop_table(dbString *);
extern int db__driver_execute_immediate(dbString *);
extern int db__driver_fetch(dbCursor *, int, int *);
extern int db__driver_find_database(dbHandle *, int *);
extern int db__driver_finish(void);
extern int db__driver_init(int, char **);
extern int db__driver_insert(dbCursor *);
extern int db__driver_list_indexes(dbString *, dbIndex **, int *);
extern int db__driver_list_tables(dbString **, int *, int);
extern int db__driver_list_databases(dbString *, int, dbHandle **, int *);
extern int db__driver_open_insert_cursor(dbCursor *);
extern int db__driver_open_select_cursor(dbString *, dbCursor *, int);
extern int db__driver_open_update_cursor(dbString *, dbString *, dbCursor *,
                                         int);
extern int db__driver_open_database(dbHandle *);
extern int db__driver_grant_on_table(dbString *, int, int);
extern int db__driver_get_num_rows(dbCursor *);
extern int db__driver_begin_transaction(void);
extern int db__driver_commit_transaction(void);
extern int db__driver_update(dbCursor *);

#ifdef DB_DRIVER_C
int (*db_driver_add_column)(dbString *, dbColumn *) = db__driver_add_column;
int (*db_driver_bind_update)(dbCursor *) = db__driver_bind_update;
int (*db_driver_close_cursor)(dbCursor *) = db__driver_close_cursor;
int (*db_driver_close_database)(void) = db__driver_close_database;
int (*db_driver_create_index)(dbIndex *) = db__driver_create_index;
int (*db_driver_create_table)(dbTable *) = db__driver_create_table;
int (*db_driver_create_database)(dbHandle *) = db__driver_create_database;
int (*db_driver_delete)(dbCursor *) = db__driver_delete;
int (*db_driver_delete_database)(dbHandle *) = db__driver_delete_database;
int (*db_driver_describe_table)(dbString *,
                                dbTable **) = db__driver_describe_table;
int (*db_driver_drop_column)(dbString *, dbString *) = db__driver_drop_column;
int (*db_driver_drop_index)(dbString *) = db__driver_drop_index;
int (*db_driver_drop_table)(dbString *) = db__driver_drop_table;
int (*db_driver_execute_immediate)(dbString *) = db__driver_execute_immediate;
int (*db_driver_fetch)(dbCursor *, int, int *) = db__driver_fetch;
int (*db_driver_find_database)(dbHandle *, int *) = db__driver_find_database;
int (*db_driver_finish)(void) = db__driver_finish;
int (*db_driver_init)(int, char **) = db__driver_init;
int (*db_driver_insert)(dbCursor *) = db__driver_insert;
int (*db_driver_list_indexes)(dbString *, dbIndex **,
                              int *) = db__driver_list_indexes;
int (*db_driver_list_tables)(dbString **, int *, int) = db__driver_list_tables;
int (*db_driver_list_databases)(dbString *, int, dbHandle **,
                                int *) = db__driver_list_databases;
int (*db_driver_open_insert_cursor)(dbCursor *) = db__driver_open_insert_cursor;
int (*db_driver_open_select_cursor)(dbString *, dbCursor *,
                                    int) = db__driver_open_select_cursor;
int (*db_driver_open_update_cursor)(dbString *, dbString *, dbCursor *,
                                    int) = db__driver_open_update_cursor;
int (*db_driver_open_database)(dbHandle *) = db__driver_open_database;
int (*db_driver_grant_on_table)(dbString *, int,
                                int) = db__driver_grant_on_table;
int (*db_driver_get_num_rows)(dbCursor *) = db__driver_get_num_rows;
int (*db_driver_begin_transaction)(void) = db__driver_begin_transaction;
int (*db_driver_commit_transaction)(void) = db__driver_commit_transaction;
int (*db_driver_update)(dbCursor *) = db__driver_update;
#else
extern int (*db_driver_add_column)(dbString *, dbColumn *);
extern int (*db_driver_bind_update)(dbCursor *);
extern int (*db_driver_close_cursor)(dbCursor *);
extern int (*db_driver_close_database)(void);
extern int (*db_driver_create_index)(dbIndex *);
extern int (*db_driver_create_table)(dbTable *);
extern int (*db_driver_create_database)(dbHandle *);
extern int (*db_driver_delete)(dbCursor *);
extern int (*db_driver_delete_database)(dbHandle *);
extern int (*db_driver_describe_table)(dbString *, dbTable **);
extern int (*db_driver_drop_column)(dbString *, dbString *);
extern int (*db_driver_drop_index)(dbString *);
extern int (*db_driver_drop_table)(dbString *);
extern int (*db_driver_execute_immediate)(dbString *);
extern int (*db_driver_fetch)(dbCursor *, int, int *);
extern int (*db_driver_find_database)(dbHandle *, int *);
extern int (*db_driver_finish)(void);
extern int (*db_driver_init)(int, char **);
extern int (*db_driver_insert)(dbCursor *);
extern int (*db_driver_list_indexes)(dbString *, dbIndex **, int *);
extern int (*db_driver_list_tables)(dbString **, int *, int);
extern int (*db_driver_list_databases)(dbString *, int, dbHandle **, int *);
extern int (*db_driver_open_insert_cursor)(dbCursor *);
extern int (*db_driver_open_select_cursor)(dbString *, dbCursor *, int);
extern int (*db_driver_open_update_cursor)(dbString *, dbString *, dbCursor *,
                                           int);
extern int (*db_driver_open_database)(dbHandle *);
extern int (*db_driver_grant_on_table)(dbString *, int, int);
extern int (*db_driver_get_num_rows)(dbCursor *);
extern int (*db_driver_begin_transaction)(void);
extern int (*db_driver_commit_transaction)(void);
extern int (*db_driver_update)(dbCursor *);
#endif

#endif
