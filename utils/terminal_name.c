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
  switch (t)
  {
  case 0:
    strcpy(name, "DECLARE");
    break;
  case 1:
    strcpy(name, "ID");
    break;
  case 2:
    strcpy(name, "COLON");
    break;
  case 3:
    strcpy(name, "SEMICOL");
    break;
  case 4:
    strcpy(name, "LIST");
    break;
  case 5:
    strcpy(name, "OF");
    break;
  case 6:
    strcpy(name, "VARIABLES");
    break;
  case 7:
    strcpy(name, "JAGGED");
    break;
  case 8:
    strcpy(name, "ARRAY");
    break;
  case 9:
    strcpy(name, "INTEGER");
    break;
  case 10:
    strcpy(name, "R1");
    break;
  case 11:
    strcpy(name, "SQOP");
    break;
  case 12:
    strcpy(name, "NUM");
    break;
  case 13:
    strcpy(name, "SQCL");
    break;
  case 14:
    strcpy(name, "SIZE");
    break;
  case 15:
    strcpy(name, "VALUES");
    break;
  case 16:
    strcpy(name, "CURLOP");
    break;
  case 17:
    strcpy(name, "CURLCL");
    break;
  case 18:
    strcpy(name, "EPS");
    break;
  case 19:
    strcpy(name, "REAL");
    break;
  case 20:
    strcpy(name, "BOOLEAN");
    break;
  case 21:
    strcpy(name, "ELIP");
    break;
  case 22:
    strcpy(name, "EQUALS");
    break;
  case 23:
    strcpy(name, "PLUS");
    break;
  case 24:
    strcpy(name, "MINUS");
    break;
  case 25:
    strcpy(name, "MUL");
    break;
  case 26:
    strcpy(name, "DIV");
    break;
  case 27:
    strcpy(name, "OR");
    break;
  case 28:
    strcpy(name, "AND");
    break;
  case 29:
    strcpy(name, "PROGRAM");
    break;
  case 30:
    strcpy(name, "BROP");
    break;
  case 31:
    strcpy(name, "BRCL");
    break;
  case 32:
    strcpy(name, "COMMA");
    break;
  }
}