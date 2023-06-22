//
// Created by dat on 6/3/23.
//

#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "PA2023"

bool verifyUser(const gchar *user_name, const gchar *pass_word);
#endif // LOGIN_INTERFACE_H

