#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <iostream>
#include "Cart_Point.h"
using namespace std;

class Model;

class Game_Object 
{
 public:

  Game_Object();
  //Initializes display_code to " ", state to 's', id_num to 0, and outputs a message

  Game_Object(char in_code);
  //Initializes display_code, sets remaining initial values, outputs a message

  Game_Object(char in_code, int in_id, Cart_Point in_loc);
  //Initializes display_code, id_num, & location, sets remaining initial values and outputs a message

  virtual ~Game_Object();
  //Prints a message when the Model class deletes a Game_Object

  Cart_Point get_location();
  //Returns a Cart_Point object with the coordinates of the object

  virtual int get_id();
  //Returns the id_num of the object

  virtual int get_display_code();
  //Returns the display_code of the object

  virtual void set_id_num(int id);
  //Sets the id_num

  virtual void set_display_code(char code);
  //Sets the dispaly_code

  virtual void show_status();
  //Outputs the display_code, id_num, and location contained in the class

  void drawself(char * ptr);
  //Puts the display_code at the character pointed to by ptr, and the ASCII character for the id_num in the next character

  virtual bool update() = 0;
  //Pure virtual update function

  virtual bool is_alive();
  //Always returns true

  virtual void save(ofstream& file);
  //Writes the member variables declared in the object to a save file

  virtual void restore(ifstream& file, Model& model);
  //Reads from the file into the member variables declared in this class

 protected:

  Cart_Point location;
  //This object's current coordinates

  char display_code;
  //Code letter to identify what kind of object this is in the output

  char state;
  //A character identifying the state of the object

 private:

  int id_num;
  //ID number to identify this particular object in the output
  
};

#endif
