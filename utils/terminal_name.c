/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "terminal_name.h"

void get_t_name(terminal t, char *name)
{
  /*
    Get the name of terminal from it's enum int value
  */

  // TO DO: edit this list as per terminal order in entities.h
  switch (t)
  {
  case 0:
    strcpy(name, "DECLARE");
    break;
  case 1:
    strcpy(name, "MODULE");
    break;
  case 2:
    strcpy(name, "ID");
    break;
  case 3:
    strcpy(name, "SEMICOL");
    break;
  case 4:
    strcpy(name, "DRIVERDEF");
    break;
  case 5:
    strcpy(name, "DRIVER");
    break;
  case 6:
    strcpy(name, "PROGRAM");
    break;
  case 7:
    strcpy(name, "DRIVERENDDEF");
    break;
  case 8:
    strcpy(name, "DEF");
    break;
  case 9:
    strcpy(name, "ENDDEF");
    break;
  case 10:
    strcpy(name, "TAKES");
    break;
  case 11:
    strcpy(name, "INPUT");
    break;
  case 12:
    strcpy(name, "SQBO");
    break;
  case 13:
    strcpy(name, "SQBC");
    break;
  case 14:
    strcpy(name, "RETURNS");
    break;
  case 15:
    strcpy(name, "COLON");
    break;
  case 16:
    strcpy(name, "COMMA");
    break;
  case 17:
    strcpy(name, "INTEGER");
    break;
  case 18:
    strcpy(name, "REAL");
    break;
  case 19:
    strcpy(name, "BOOLEAN");
    break;
  case 20:
    strcpy(name, "ARRAY");
    break;
  case 21:
    strcpy(name, "OF");
    break;
  case 22:
    strcpy(name, "RANGEOP");
    break;
  case 23:
    strcpy(name, "START");
    break;
  case 24:
    strcpy(name, "END");
    break;
  case 25:
    strcpy(name, "BO");
    break;
  case 26:
    strcpy(name, "BC");
    break;
  case 27:
    strcpy(name, "GET_VALUE");
    break;
  case 28:
    strcpy(name, "PRINT");
    break;
  case 29:
    strcpy(name, "TRUE");
    break;
  case 30:
    strcpy(name, "FALSE");
    break;
  case 31:
    strcpy(name, "NUM");
    break;
  case 32:
    strcpy(name, "RNUM");
    break;
  case 33:
    strcpy(name, "ASSIGNOP");
    break;
  case 34:
    strcpy(name, "USE");
    break;
  case 35:
    strcpy(name, "WITH");
    break;
  case 36:
    strcpy(name, "PARAMETERS");
    break;
  case 37:
    strcpy(name, "PLUS");
    break;
  case 38:
    strcpy(name, "MINUS");
    break;
  case 39:
    strcpy(name, "MUL");
    break;
  case 40:
    strcpy(name, "DIV");
    break;
  case 41:
    strcpy(name, "AND");
    break;
  case 42:
    strcpy(name, "OR");
    break;
  case 43:
    strcpy(name, "LT");
    break;
  case 44:
    strcpy(name, "LE");
    break;
  case 45:
    strcpy(name, "GT");
    break;
  case 46:
    strcpy(name, "GE");
    break;
  case 47:
    strcpy(name, "EQ");
    break;
  case 48:
    strcpy(name, "NE");
    break;
  case 49:
    strcpy(name, "SWITCH");
    break;
  case 50:
    strcpy(name, "CASE");
    break;
  case 51:
    strcpy(name, "BREAK");
    break;
  case 52:
    strcpy(name, "DEFAULT");
    break;
  case 53:
    strcpy(name, "FOR");
    break;
  case 54:
    strcpy(name, "IN");
    break;
  case 55:
    strcpy(name, "WHILE");
    break;
  case 56:
    strcpy(name, "EPS");
    break;
  case 57:
    strcpy(name, "DOLLAR");
    break;
  }
}