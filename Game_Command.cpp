#include <fstream>
#include <string>
#include "Game_Command.h"
#include "Miner.h"
#include "Town_Hall.h"
#include "Gold_Mine.h"
#include "Model.h"
#include "View.h"
#include "Soldier.h"
#include "Input_Handling.h"
#include "Inspector.h"
#include <exception>

void do_move_command(Model &model, View &view)
//Commands Miner ID to move to location (x,y)
{
 
  //Read in the rest of the console input
  int ID;
  double x, y;
  cin >> ID >> x >> y;
      
  //Get the pointer to the supplied id_num
  Person * personPtr = model.get_Person_ptr(ID); 
 
  if (personPtr)
    {
      //Create a Cart_Point object with the x and y coordinate inputs
      Cart_Point dest(x,y);

      //Call the Person::start_moving function to tell the miner to move
      personPtr->start_moving(dest);

      model.display(view);

    }
  else 
    {
       //Throw an Invalid_Input exception if the inputted ID number is invalid
      throw Invalid_Input("Please enter valid ID number!");
    }
}

void do_work_command(Model &model, View &view)
//Commands Miner ID1 to start mining at Gold_Mine ID2 and deposit the gold at Town_Hall ID3
{
  //Read in the rest of the input commands
  int ID1, ID2, ID3;
  cin >> ID1 >> ID2 >> ID3;

  //Get the pointers to the objects with the inputted IDs
  Person * minerPtr = model.get_Person_ptr(ID1);
  Gold_Mine * minePtr = model.get_Gold_Mine_ptr(ID2);
  Town_Hall * hallPtr = model.get_Town_Hall_ptr(ID3);

  if(minerPtr && minePtr && hallPtr)
    {
      if (minerPtr->is_alive())
	{
	  //If the Miner is alive, call the Miner::start_mining function
	  minerPtr->start_mining(minePtr,hallPtr);
	}
      else 
	{
	  //If the Miner is dead, print a message
	  cout << 'M' << minerPtr->get_id() << ": I am dead. Are you kidding me? Ask a zombie to work!?!?\n";
	}
      //Display the grid
      model.display(view);
    }
  else //Throw an Invalid_Input exception if one or more of the inputs were invalid
    {
      if (!minerPtr)
	{
	  throw Invalid_Input("Please enter a valid Miner ID number!");
	}
      if (!minePtr)
	{
	  throw Invalid_Input("Please enter a valid Gold_Mine ID number!");
	}
      if (!hallPtr)
	{
	  throw Invalid_Input("Please enter a valid Town_Hall ID number!");
	}
    }
}

void do_inspect_command(Model &model, View &view)
//Commands Inspector ID to start inspecting
{
  //Read in the rest of the console input and throw an Invalid_Input exception if it is not an int
  int ID;
  if (!(cin >> ID))
    {
      throw Invalid_Input("Please enter a valid Inspector ID number!");
    }
  else
    {
      //Get the pointer to the Inspector with the inputted ID
      Person * inspectorPtr = model.get_Person_ptr(ID);

      //If the pointer is invalid, throw an Invalid_Input exception
      if (!inspectorPtr)
	{
	  throw Invalid_Input("Please enter a valid Inspector ID number!");
	}
      //If the inspector is alive, tell it to start inspecting
      else if (inspectorPtr->is_alive()) 
	{
	  inspectorPtr->start_inspecting(model);
	}
      //If the inspector is dead, print a message
      else 
	{
	  cout << 'I' << inspectorPtr->get_id() << ": I am dead. Are you kidding me? Ask a zombie to inspect!?!?\n"; 
	}
      //Display the grid
      model.display(view);
    }
}

void do_stop_command(Model &model, View &view)
//Commands Miner ID to stop whatever it is doing
{
  //Read in the rest of the console input
  int ID;
  cin >> ID;

  //Get the pointer to the Miner object with the inputted ID
  Person * minerPtr = model.get_Person_ptr(ID);

  //Call the Miner::stop function if the input is valid
  if (minerPtr)
    {
      minerPtr->stop();

      //Display the grid
      model.display(view);
    }
  else
    throw Invalid_Input("Please enter a valid Miner ID number!");
}

void do_go_command(Model &model, View &view)
//Advances one time step by updating each object once
{
  cout << "Advancing one tick.\n";

  model.update();

  //Displays current time and the status of each object
  model.show_status();

  //Display the grid
  model.display(view);
}

void do_run_command(Model &model, View &view)
//Advance one time step and update each object, repeating until either the update function returns true for at least one object or 5 time steps have passed
{
  cout << "Advancing to next event.\n";

  //Declares a counter variable to keep track of how many time steps have passed
  int count = 0;

  while (count < 5)
    {
      count++;

      bool test = model.update();
     
      if (test)
	{
	  break;
	}    
      
    }

  //Displays current time and the status of each object as well as the grid
  model.show_status();
  model.display(view);

}

void do_list_command(Model &model, View &view)
//Lists the status of all objects using the Model's show_status function
{
  model.show_status();

  //Display the grid
  model.display(view);
}

void do_attack_command(Model &model, View &view)
//Commands Person ID1 to attack Person ID2; Checks for input errors; Only soldiers will attack another Person.
{
  //Reads in the inputted ID numbers 
  int ID1, ID2;
  cin >> ID1 >> ID2;

  //Gets the pointers to the objects with the inputted IDs
  Person * personPtr1 = model.get_Person_ptr(ID1);
  Person * personPtr2 = model.get_Person_ptr(ID2);

  //If the ID numbers are valid, commands Person ID1 to attack Person ID2
  if (personPtr1 && personPtr2)
    {
      personPtr1->start_attack(personPtr2);
      
      //Displays the grid
      model.display(view);
    }
  else 
    {
      //If one or both of the ID numbers were invalid, throws an Invalid_Input exception
      throw Invalid_Input("Please enter a valid ID number!");
    }
}

//Save and restore commands need to be debugged
/*
void do_save_command(Model &model)
//Saves the game in the specified file
{
  //Reads in the file name
  ofstream f;
  string filename;
  getline(cin, filename);
  
  //Opens the specified file
  f.open(filename.c_str());

  //Calls the Model::save(ofstream&) function to write the game info to the file
  model.save(f);

  //Closes the file
  f.close();

}

void do_restore_command(Model &model)
//Restores the game using the specified file
{
  //Reads in the file name
  ifstream f;
  string filename;
  getline(cin, filename);

  //Opens the specified file
  f.open(filename.c_str());

  //Check if the specified file exists
  if (f)
    {
      //Calls the Model::restore(ifstream&) function to restore the game info
      model.restore(f);
    }
  else 
    {
      //Throws an Invalid_Input exception if the file does not exist
      throw Invalid_Input("Please enter a valid file name!");
    }
  
  //Closes the file
  f.close();
}
*/