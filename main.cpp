#include <iostream>
#include <cmath>
#include <exception>
#include <limits>
#include "Game_Object.h"
#include "Person.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"
#include "Model.h"
#include "Game_Command.h"
#include "Soldier.h"
#include "Input_Handling.h"

using namespace std;

int main()
{
  //Declares a View object and sets up a clear grid
  View view;
  view.clear();

  //Declares a Model object
  Model model;

  //Displays the initial grid
  model.display(view);

  //Declares a variable that will receive the commands inputted by the user
  char command;

  //Main program loop
  while (command != 'q')
    {

    //Prompts user to enter a single character command 
    cout << "Enter command: ";
    cin >> command;

    //Try block handles commands
    try{
        
      //Calls the function that corresponds to the inputted command
      switch (command)
	{
	case 'm':
	  do_move_command(model, view);
	  break;
	case 'w':
	  do_work_command(model, view);
	  break;
	case 's':
	  do_stop_command(model, view);
	  break;
	case 'g':
	  do_go_command(model, view);
	  break;
	case 'r':
	  do_run_command(model, view);
	  break;
	case 'l':
	  do_list_command(model, view);
	  break;
	case 'a':
	  do_attack_command(model, view);
	  break;
	case 'n': 
	  model.handle_new_command(view);
	  break;
	case 'i':
	  do_inspect_command(model, view);
	  break;
	case 'q':
	  cout << "Terminating program.\n";
	  break;
	/* Save and restore commands need to be debugged
	case 'S':
	  do_save_command(model);
	  break;
	case 'R':
	  do_restore_command(model);
	  break;
	*/ 
	default:
	  throw Invalid_Input("Please enter a valid command!");
	  break;
	}
    }//End try block
    
    //Catch block handles an Invalid_Input exception
    catch (Invalid_Input& except) {
      
      //Prints an error message
      cout << "Invalid input - " << except.msg_ptr << endl;
      
      //Ignores the rest of the user input (up to 1000 characters) and goes to the next line
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      
    }//End catch block
    
     

    }//End while loop

  return 0;
}

//****************TODO*******************************************************

//Decide what to do when an object has an ID num greater than 9; maybe make a third dimension of the grid

//Whenever i throw an exception i get a warning: deprecated conversion from string constant to char*

//Change any other error messages in the classes to throws

//Check notes in Model.cpp

//***************************************************************************




