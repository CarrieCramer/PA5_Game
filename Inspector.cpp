#include <iostream>
#include <list>
#include "Inspector.h"
#include "Person.h"
#include "Cart_Point.h"
#include "Gold_Mine.h"
#include "Model.h"
using namespace std;

Inspector::Inspector(): Person('I')
//Invokes Person('I'), outputs a message
{
  current_mine = mines_to_inspect.end();
  cout << "Default Inspector constructed!\n";
}

Inspector::Inspector(int in_id, Cart_Point in_loc): Person('I', in_id, in_loc)
//Invokes Person('I', in_id, in_loc), outputs a message
{
  current_mine = mines_to_inspect.end();
  cout << "Inspector Constructed!\n";
}

Inspector::~Inspector()
//Prints a message when the model class deletes an Inspector object
{
  cout << "Inspector destructed.\n";
}

void Inspector::show_status()
//Outputs "Inspector status:", calls Person::show_status(), and displays info about the Miner-specific states of moving outbound, reporting outbound, moving inbound, reporting inbound
{
  cout << "Inspector status: ";

  Person::show_status();

  //Prints a message that depends on the current value of the state variable
  switch (state)
    {
    case 'o': cout << "    Outbound Inspecting" << endl;
      break;

    case 'r': cout << "    Doing outbound inspection" << endl;
      break;

    case 'i': cout << "    Inbound Inspecting" << endl;
      break;

    case 'R': cout << "    Doing inbound inspection" << endl;
    }

}

bool Inspector::update()
//Returns true when the Inspector arrives at a destination
{
  switch (state)
    {
//state = "stopped": Inspector does nothing and stays in this state
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

//state = "moving outbound": calls update_location to take a step
    case 'o': 
      //If the object has arrived at a Gold_Mine, sets the state to "reporting outbound" and returns true
      if (update_location())
	{
	  state = 'r';
	  return true;
	}
      break;

//state = "reporting outbound": calls report_outbound and returns true
    case 'r':
      report_outbound();
      return true;
      break;

//state = "moving inbound": calls update_location to take a step
    case 'i':
      if (update_location())
	  {
	    //If the inspector has arrived at its starting location, sets the state to "Stopped", prints a message, and returns true.
	    if ( ((this->get_location()).x == starting_location.x) && ((this->get_location()).y == starting_location.y) )
	      {
		cout << "    Inspection complete";
		state = 's';
	      }
	    else 
	      {
		//If the inspector has arrived at a Gold_Mine, sets the state to "reporting inbound" and returns true. 
		state = 'R';
	      }
	    return true;
	  }
	else
	  return false;
      break; 

//state = "reporting inbound": calls report_inbound and returns true
    case 'R':
      report_inbound();
      return true;
      break;

//state = "dead": Object stays in this state, returns false
    case 'x':
      return false;
      break;

    }
}

void Inspector::find_closest_mine()
//Loops through mines_to_inspect to find the mine closest to the Inspector, sets the current_mine iterator to point to this mine
{
 double shortest_distance = 1000000000;
 double distance;  
 list<Gold_Mine*>::iterator i;
 for (i = mines_to_inspect.begin(); i != mines_to_inspect.end(); i++)
   {
     distance = cart_distance((*i)->get_location(),this->get_location());
     if (distance < shortest_distance)
       {
	shortest_distance = distance;
	current_mine = i; //Sets the current_mine iterator to the closest mine
	}
   }
}

void Inspector::start_inspecting(Model &model)
//Tells the Inspector to start inspecting
{
  //Clears mines_to_inspect, mines_inspected, and mine_amounts
  mines_to_inspect.clear();
  mines_inspected.clear();
  mine_amounts.clear();

  //Sets state to "moving outbound"
  state = 'o';

  //Sets starting_location to the Inspector's current location
  starting_location = location;

  //Copies mine_ptrs to mines_to_inspect
  mines_to_inspect = model.get_Gold_Mine_list();
  
  //Calls find_closest_mine() to set current_mine equal to the mine closest to the Inspector 
  find_closest_mine();
  
  //Sets the Inspector's destination to current_mine
  setup_destination((*current_mine)->get_location());

  //Prints the message: "I(id_num): starting to inspect!"
  cout << "I" << get_id() << ": starting to inspect!\n";
}

void Inspector::report_outbound()
//Performs the Inspector's actions during an outbound report
{
  //Prints the amount of gold currently in the mine
  cout << "This mine contains " << (*current_mine)->get_gold_amount() << " Gold!\n";
  
  //If this is the last outbound mine, erases the current mine from mines_to_inspect, sets current_mine to point to the second to last mine inspected and calls setup_destination to prepare to move to it, sets the state to "moving inbound", prints a message
  if (mines_to_inspect.size() == 1)
    {
      list<Gold_Mine*>::iterator i = mines_to_inspect.begin();
      mines_to_inspect.erase(i);
      current_mine = mines_inspected.begin();
      setup_destination((*current_mine)->get_location());
      state = 'i';
      cout << "Heading back!\n";
    }
  else 
   {
     //Pushes the amount in the current mine to the front of mine_amounts
     mine_amounts.push_front((*current_mine)->get_gold_amount());
     //Pushes the current mine to the front of mines_inspected and removes it from mines_to_inspect
     mines_inspected.splice(mines_inspected.begin(),mines_to_inspect,current_mine);
     //Calls find_closest_mine() to set the new current_mine
     find_closest_mine();
     //Calls setup_destination to set the destination to the current mine
     setup_destination((*current_mine)->get_location());
     //sets the state to "moving outbound"
     state = 'o';
   }
}

void Inspector::report_inbound()
//Performs the Inspector's actions during an inbound report
{
  //Prints a message stating the amount of gold that has been removed from the Gold_Mine since the outbound inspection
  double amount_removed = *mine_amounts.begin() - (*mines_inspected.begin())->get_gold_amount();
  cout << "Amount of gold removed from the mine is " << amount_removed << " gold!\n";

  //Erases the current Gold_Mine from mines_inspected and sets current_mine to the next one on the stack
  current_mine = mines_inspected.erase(mines_inspected.begin());

  //Calls setup_destination to tell the inspector to move to the Gold_Mine pointed to by current_mine
  setup_destination((*current_mine)->get_location());

  //Sets the state to "moving inbound"
  state = 'i';
}

void Inspector::save(ofstream& file)
//Calls the save function for Person, then writes to the file the member variables declared in this class
{
  Person::save(file);

  //Saves the length of mines_to_inspect and mines_inspected for use in the restore function

  int size1 = mines_to_inspect.size();
  int size2 = mines_inspected.size();
  
  file << size1 << endl << size2 << endl;

  list<Gold_Mine*>::iterator i;

  for (i = mines_to_inspect.begin(); i != mines_to_inspect.end(); i++)
    {
      file << (*i)->get_id() << endl;
    }

  for (i = mines_inspected.begin(); i != mines_inspected.end(); i++)
    {
      file << (*i)->get_id() << endl;
    }

  list<double>::iterator j;

  for (j = mine_amounts.begin(); j != mine_amounts.end(); j++)
    {
      file << (*j) << endl;
    }

  file << starting_location.x << endl << starting_location.y << endl;

  if(current_mine != mines_to_inspect.end())
    {
      file << (*current_mine)->get_id() << endl;
    }

}

void Inspector::restore(ifstream& file, Model& model)
//Reads from the file into the member variables declared in this class
{
  Person::restore(file, model);
    
  //Reads in the sizes of mines_to_inspect and mines_inspected
  int size1;
  file >> size1;
  int size2;
  file >> size2;

  //Sets mines_to_inspect
  for (int i = 0; i < size1; i++)
    {
      int id;
      file >> id;
      Gold_Mine* mine_ptr = model.get_Gold_Mine_ptr(id);
      mines_to_inspect.push_back(mine_ptr);
    }

  //Sets mines_inspected
  for (int i = 0; i < size2; i++)
    {
      int id;
      file >> id;
      Gold_Mine* mine_ptr = model.get_Gold_Mine_ptr(id);
      mines_to_inspect.push_back(mine_ptr);
    }

  //Sets mine_amounts
  for (int i = 0; i < size2; i++)
    {
      int id;
      file >> id;
      Gold_Mine* mine_ptr = model.get_Gold_Mine_ptr(id);
      mines_to_inspect.push_back(mine_ptr);
    }

  //Sets starting_location
  double output;
  file >> output;
  starting_location.x = output;
  file >> output;
  starting_location.y = output;

  //Sets current_mine
  int id;
  file >> id;
  Gold_Mine* mine_ptr = model.get_Gold_Mine_ptr(id);
  
  list<Gold_Mine*>:: iterator i;
  for(i = mines_to_inspect.begin(); i != mines_to_inspect.end(); i++)
    {
      if (*i == mine_ptr)
	{
	  current_mine = i;
	}
    }

  for(i = mines_inspected.begin(); i != mines_inspected.end(); i++)
    {
      if (*i == mine_ptr)
	{
	  current_mine = i;
	}
    }

}
