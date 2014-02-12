#include <iostream>
#include "Soldier.h"
#include "Person.h"
#include "Cart_Point.h"
#include "Model.h"
using namespace std;

Soldier::Soldier(): Person('S')
//Invokes Person('S'), initializes attack_strength to 2, range to 2.0, and outputs a message
{
  attack_strength = 2;

  range = 2.0;

  cout << "    Default Soldier constructed.\n";
}

Soldier::Soldier(int in_id, Cart_Point in_loc): Person('S', in_id, in_loc)
//Invokes Person('S', in_id, in_loc), initializes attack_strength to 2, range to 2.0, and outputs a message
{
  attack_strength = 2;

  range = 2.0;

  cout << "    Soldier constructed.\n";
}

Soldier::~Soldier()
//Prints a message when the Model class deletes a Soldier object
{
  cout << "    Soldier destructed.\n";
}

void Soldier::start_attack(Person * in_target)
//If the distance to the target is less than or equal to the range, outputs a message, saves the target pointer, and sets the state to 'a' (attack). if it is too far away, outputs a message 
{
  if (is_alive())
    {
      if (cart_distance(location, in_target->get_location()) <= range)
	{
	  target = in_target;
	  state = 'a';
	  cout << 'S' << get_id() << ":Attacking.\n"; 
	}
      else 
	{
	  cout << "Target is out of range\n";
	}
    }
  else 
    {
      //If the Soldier is dead, print a message
      cout << 'S' << get_id() << ": I am dead. You do not have the ability to summon the undead.\n";
    } 
}

bool Soldier::update()
//Updates the Soldier according to its state
{
  switch (state)
    {
    
      //state = "dead": Soldier does nothing and stays in this state
    case 'x': return false;
      break;
    
      //state = "stopped": Soldier does nothing and stays in this state
    case 's': return false;
      break;

      //state = "moving to a destination": calls update_location to take a step
    case 'm': 
      //If the object has arrived, sets the state to stopped and returns true
      if (update_location())
	{
	  state = 's';
	  return true;
	}
      break;

      //state = "attack": If the target is within range and alive, the soldier attacks. If not, prints a message
    case 'a':
      //If the distance is out of range, prints a message, sets the state to stopped, and returns true
      if (cart_distance(location, target->get_location()) > range)
	{
	  cout << "Target is out of range\n";
	  state = 's';
	  return true;
	}
      //If the distange is in range, checks to see whether the target is alive
      else
	{
	  if (target->is_alive())
	    {
	      //If the target is alive, outputs a message and calls the target's take_hit function, stays in the state, and returns false
	      cout << display_code << get_id() << ":Take that!\n";
	      target->take_hit(attack_strength, this);
	      return false;
	    }
	  else
	    {
	      //If the target is dead, output a message, set the state to stopped, and return true
	      cout << display_code << get_id() << ":I win.\n";
	      state = 's';
	      return true;
	    }
	}
      break;
    }
}

void Soldier::show_status()
//Outputs "Soldier status: ", calls Person::show_status(), and outputs whether the object is attacking
{
  cout << "Soldier status: ";
  Person::show_status();
  if (state == 'a')
    {
      cout << "Attacking.\n";
    }
}

void Soldier::save(ofstream& file)
//Calls the save function for Person, then writes to the file the member variables declared in this class
{
  Person::save(file);

  if (target)
    {
      file << target->get_id() << endl;
    }
  else
    {
      file << -1 << endl;
    }
}

void Soldier::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Person::restore(file, model);

  //Sets target
  int id;
  file >> id;
  target = model.get_Person_ptr(id);

}


void Soldier::take_hit(int attack_strength, Person* attacker_ptr)
//Tells the soldier to attack the attacker
{
  Person::take_hit(attack_strength, attacker_ptr);

  this->start_attack(attacker_ptr);
}
