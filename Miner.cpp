#include <iostream>
#include <math.h>
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Person.h"
#include "Game_Object.h"
#include "Model.h"
#include "Cart_Vector.h"
#include "Cart_Point.h"

using namespace std;

Miner::Miner(): Person('M')
//Invokes Person('M'), initializes amount to 0 and mine and home pointers to NULL, outputs a message
{

  //Amount of gold currently being carried
  amount = 0;

  //Pointer to the Gold_Mine to be mined
  mine = NULL;

  //A pointer to the Town_Hall where the gold will be deposited
  home = NULL;

  //Prints the message "Default Miner constructed"
  cout << "    Default Miner constructed.\n";
}

Miner::Miner(int in_id, Cart_Point in_loc): Person('M', in_id, in_loc)
//Invokes Person('M',in_id,in_loc), initializes amount to 0 and mine and home pointers to 0, outputs a message
{
  amount = 0;
  mine = NULL;
  home = NULL;

  //Prints the message "Miner constructed"
  cout << "    Miner constructed." << endl;

}

Miner::~Miner()
//Prints a message when the Model class deletes a Miner object
{
  cout << "    Miner destructed.\n";
}

void Miner::show_status()
//Outputs "Miner status:", calls Person::show_status(), and displays info about the Miner-specific states of inbound, outbound, getting gold, and depositing gold
{
  cout << "Miner status: ";
  
  Person::show_status();

  //Prints a message that depends on the current value of the state variable
  switch (state)
  {
  case 'o': cout << "   Outbound to a mine." << endl;
    break;
  
  case 'g': cout << "   Getting gold from mine." << endl;
    break;
  
  case 'i': cout << "   Inbound to home with load: " << amount << endl;  
    break;
  
  case 'd': cout << "   Depositing gold." << endl;
    break;  
  }

}

bool Miner::update()
//Returns true when the state is changed and updates the status of the object on each time unit
{
  switch (state)
    {
    
//state = "stopped": miner does nothing and stays in this state
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
    

//state = "outbound mining"
    case 'o':
      //If the object has arrived, sets the state to getting gold and returns true 
      if (update_location())
	{
	  state = 'g';
	  return true;
	}
      break;
    

//state = "getting gold"
    case 'g':
      {
      //Calls the Gold_Mine's dig_gold function
      amount = mine->dig_gold();
      //Prints the amount of gold that the miner got
      cout << display_code << Game_Object::get_id() << ": Got " << amount << " gold.\n";
      //Calls setup_destination to prepare to move to the home Town_Hall
      setup_destination(home->Game_Object::get_location());
      //Sets the state to inbound mining and returns true
      state = 'i';
      return true;
      break;
      }

//state = "inbound mining"
    case 'i':
      //If the object has arrived, sets the state to depositing gold and returns true
      if (update_location())
	{
	  state = 'd';
	  return true;
	}
      break;

     
 //state = "depositing gold"
    case 'd':
      //Prints the amount of gold to be deposited
      cout << display_code << Game_Object::get_id() << ": Deposit " << amount << " of gold.\n";
      //Deposit the gold in the town hall
      home->deposit_gold(amount);
      //Set the miner's amount to 0
      amount = 0;
      //If the Gold_Mine is depleted, set the state to 's' and print a message
      if (mine->is_empty())
	{
	  state = 's';
	  cout << display_code << Game_Object::get_id() << ": More work?" << endl;
	  return true;
	}
      //Otherwise call setup_destination to mine again, set state to 'o', print a message, and return true
      else    
	{
	  setup_destination(mine->get_location());
	  state = 'o';
	  cout << display_code << Game_Object::get_id() << ": Going back for more.\n";
	  return true;
	}
      break;

 //state = "dead"
    case 'x':
      //Object stays in this state, returns false
      return false;
      break;

    }
}

void Miner::start_mining(Gold_Mine* in_mine, Town_Hall* in_home)
//Tells the miner to start mining, which includes moving gold from the mine to home (Gold_Mine and Town_Hall objects)
{
  
  //Set the Miner's home and mine pointers to point to inputMine and inputHome
  mine = in_mine;
  home = in_home;

  //Calls setup_destination with a pointer to a Gold_Mine object as the input; changes Miner's destination to the Gold_Mine
  setup_destination(mine->get_location());

  //Sets the state to outbound
  state = 'o';

  //Prints a message that states what the miner is doing
  cout << "Miner " << Game_Object::get_id() << " mining at Gold_Mine " << mine->get_id() << " and depositing at Town_Hall " << home->Game_Object::get_id() << "." << endl;

  //Prints a response from the miner
  cout << display_code << Game_Object::get_id() << ": Yes, my lord.\n";
}

void Miner::save(ofstream& file)
//Calls the save function for Person, then writes to the file the member variables declared in this class
{
  Person::save(file);

  file << amount << endl;
  
  if (home != NULL)
    {
      file << home->get_id() << endl;
    }
  else 
    {
      file << -1 << endl;
    }

  if (mine != NULL)
    {
      file << mine->get_id() << endl;
    }
  else 
    {
      file << -1 << endl;
    }
}

void Miner::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Person::restore(file, model);

  //Sets amount
  int output;
  file >> output;
  amount = output;

  //Sets home
  int id;
  file >> id;
  home = model.get_Town_Hall_ptr(id);

  //Sets mine
  file >> id;
  mine = model.get_Gold_Mine_ptr(id);

}

void Miner::take_hit(int attack_strength, Person* attacker_ptr)
//Tells the Miner to run away from the attacker
{
  Person::take_hit(attack_strength, attacker_ptr);

  Cart_Point loc1 = (this->get_location());
  Cart_Point loc2 = (attacker_ptr->get_location());

  Cart_Vector run_to = loc2 - loc1;

  run_to = run_to*(-1.5);

  Cart_Point run_to_point = loc1 + run_to;

  this->Person::start_moving(run_to_point);
}

