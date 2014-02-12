#include "Person.h"
#include "Model.h"
#include <math.h>
#include <ctype.h>

Person::Person()
//Initializes the speed to 5 and outputs a message
{
  speed = 5;

  health = 5;
  
  cout << "    Person default constructed.\n";
}

Person::Person(char in_code): Game_Object(in_code)
//Invokes Game_Object(in_code) and initializes speed to 5, outputs a message
{
  speed = 5;

  health = 5;
  
  cout << "    Person constructed.\n";
}

Person::Person(char in_code, int in_id, Cart_Point in_loc): Game_Object(in_code, in_id, in_loc)
//Invokes Game_Object(in_code, in_id, in_loc) and initializes the speed to 5, outputs a message
{
  speed = 5;

  health = 5;

  cout << "    Person constructed.\n";
}

Person::~Person()
//Prints a message when the Model class deletes a Person object
{
  cout << "    Person destructed.\n";
}

void Person::start_moving(Cart_Point dest)
//Tells the Person to start moving
{
  //Check if the Person is alive, and if not, ignore the command and print a message
  if (is_alive())
    {
      //Calls the setup_destination function to change the object's destination
      setup_destination(dest);

      //Sets the state to "moving"
      state = 'm';

      //Prints message "Moving (id) to (destination)."
      cout << "Moving " << Game_Object::get_id() << " to " << destination << endl;

      //Prints message "(display_code)(id): On my way."
      cout << display_code << Game_Object::get_id() << ": On my way.\n";
    }
  else 
    {
      cout << display_code << get_id() << ": I am dead. I may move but you just cannot see me.\n";
    }
}

void Person::stop()
//Tells the person to stop moving or mining by setting the state to stopped
{
  state = 's';

  //Prints a message
  cout << "Stopping " << Game_Object::get_id() << ".\n";
  cout << display_code << Game_Object::get_id() << ": All right.\n";
}

void Person::show_status()
//Calls Game_Object::show_status, outputs the information in this class for the moving and stopped state (speed, destination, delta)
{
  Game_Object::show_status();

   switch (state)
     {
     case 's': cout << endl << "    Stopped." << endl;
       break;
  
     case 'm': cout << "moving at speed of " << speed << " towards " << destination << " at each step of " << delta << endl;
       break;

     case 'x': cout << "moving at speed of " << speed << " towards " << destination << " at each step of " << delta << " is dead.\n";
       break;

     }
}

void Person::start_mining(Gold_Mine* in_mine, Town_Hall* in_home)
//Just prints the message "Sorry, I can't work a mine"
{
  cout << display_code << get_id() << ":Sorry, I can't work a mine.\n";
}

void Person::start_inspecting(Model &model)
//Just prints the message "Sorry, I can't inspect"
{
  cout << display_code << get_id() << ":Sorry, I can't inspect.\n";
}

bool Person::update_location()
//Updates the object's location while it is moving
{
  //If the object is within one step of its destination, sets the location to the destination, print a message, and returns true
  if ( (fabs(destination.x - location.x) <= fabs(delta.x)) && (fabs(destination.y -location.y) <= fabs(delta.y)) )
    {
      location = destination;
      cout << display_code << Game_Object::get_id() << ": I'm there!" << endl;
      return true;
    }
  
  //If the object isn't within one step of its destination, adds delta to the location, prints a message, and returns false to indicate that the object hasn't arrived 
  else 
    {
      location = location + delta;
      cout << display_code << Game_Object::get_id() << ": step...\n";
      return false;
    }
}

void Person::setup_destination(Cart_Point dest)
//Sets up the object to start moving to a destination
{
  //Sets the destination to the inputted object 
  destination = dest;

  //Calculates delta value
  Cart_Vector v;
  v = destination-location;
  delta = v*(speed/cart_distance(destination,location));
  
}

bool Person::is_alive()
//Returns true if the state is not 'x', false if it is 'x'
{
  if (state != 'x')
    {
      return true;
    }
  else 
    {
      return false;
    }
}

void Person::take_hit(int attack_strength, Person* attacker_ptr)
//Subtracts the attack_strength from the health. If the new value of health is less than or equal to zero, prints a message and sets the state to 'x'. Otherwise, prints a different message and leaves the state unchanged.
{
  health = health - attack_strength;

  if (health <= 0)
    {
      cout << display_code << get_id() << ":Ahhhh, I am dying.\n";
      
      state = 'x';
    }
  else
    {
      if (health < 3)
	{
	  char newCode = tolower(static_cast<int>(this->get_display_code()));
	  this->set_display_code(static_cast<int>(newCode));
	}
      
      

      cout << display_code << get_id() << ":Ouch!\n";
    }
}

void Person::start_attack(Person * target)
//Outputs a message: "I can't attack."
{
  cout << display_code << get_id() << ":I can't attack.\n";
}

void Person::save(ofstream& file)
//Calls the save function for Game_Object, then writes to the file the member variables declared in this class
{
  Game_Object::save(file);

  file << health << endl << destination.x << endl << destination.y << endl << delta.x << endl << delta.y << endl; 
}

void Person::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Game_Object::restore(file, model);

  //Sets health
  int output;
  file >> output;
  health = output;

  //Sets destination
  double output2;
  file >> output2;
  destination.x = output2;
  file >> output2;
  destination.y = output2;
  
  //Sets delta
  file >> output;
  delta.x = output;
  file >> output;
  delta.y = output;
}
