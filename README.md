# RECIPES API

This is a program created to pass the 2nd year :)

## Table of Contents

- [Project Description](#project-description)
- [Installation](#installation)
- [Usage](#usage)

## Project Description

The goal of this program is allow user to give the exact input include:

- URL
- TOKEN
- QUERY
- ADDITION

With the structure of the URL. 

## Installation
After install cJon, mysql, curl, gtk. Run the following command:

```gcc -o recipesApi main.c apiFood.c splitString.c login_interface.c -lcurl -lmysqlclient -lcjson `pkg-config --cflags --libs gtk+-3.0` ```

## Usage

After open the project, you need to create table 'users', it needs to have 2 columns: 'username' and 'password'
- SERVER "localhost"
- USER "root"
- PASSWORD "root"
- DATABASE "PA2023"

