/*
 * File:   Globals.h
 * Author: atghosh
 *
 * Created on 3 August, 2013, 8:39 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>

/* Path to store data when server is killed */

#define INT_FILE_PATH "/tmp/mcsll_int"
#define FLOAT_FILE_PATH "/tmp/mcsll_float"
#define STRING_FILE_PATH "/tmp/mcsll_string"

static const char death_msg[] =  "I am sorry to \
say that the server has been shut!\n";              /* Server killed message*/

#endif	/* GLOBALS_H */

