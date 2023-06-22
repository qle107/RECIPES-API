#include "login_interface.h"

bool verifyUser(const gchar *user_name, const gchar *pass_word) {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "Failed to initialize MySQL connection\n");
        return false;
    }

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to MySQL server: %s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }

    char sql_query[250];
    sprintf(sql_query, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", user_name, pass_word);

    if (mysql_query(conn, sql_query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }

    int num_rows = mysql_num_rows(res);
    mysql_free_result(res);
    mysql_close(conn);

    return num_rows > 0;
}
