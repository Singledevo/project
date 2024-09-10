#include <stdio.h>
#include <mysql/mysql.h>
int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "sunbeam", "sunbeam", "password", "hotel", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "SELECT * FROM your_table")) {
        fprintf(stderr, "mysql_query() failed\n");
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s %s\n", row[0], row[1]); // Adjust based on your table structure
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
