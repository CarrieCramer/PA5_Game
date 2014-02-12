#include <list>
#include <string>
#include "Model.h"
#include "Cart_Point.h"
#include "Miner.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"
#include "Soldier.h"
#include "Input_Handling.h"

Model::Model()
//Initializes the time to 0, creates objects on the heap, stores pointers to them, and prints a message
{
  time = 0;

  //Declares Cart_Point objects that will serve as the initial locations of the Game_Objects 
  Cart_Point p1(5,1);
  Cart_Point p2(10,1);
  Cart_Point p3(1,20);
  Cart_Point p4(10,20);
  Cart_Point p5(5,15);
  Cart_Point p6(10,15);
  Cart_Point p7(5,5);

  //Creates the objects on the heap
  Miner *m1 = new Miner(1, p1);
  Miner *m2 = new Miner(2, p2);
  Soldier *s3 = new Soldier(3, p5);
  Soldier *s4 = new Soldier(4, p6);
  Inspector *Clouseau = new Inspector(5, p7);
  Gold_Mine *g1 = new Gold_Mine(1, p3);
  Gold_Mine *g2 = new Gold_Mine(2, p4);
  Town_Hall *t1 = new Town_Hall();
  
  
  //**************DELETE THIS WHEN DONE*********************
  //Stores the pointers to the objects in the pointer arrays
  // object_ptrs[0] = m1;
  // object_ptrs[1] = m2;
  // object_ptrs[2] = g1;
  // object_ptrs[3] = g2;
  // object_ptrs[4] = t1;
  // object_ptrs[5] = s3;
  // object_ptrs[6] = s4;

  // person_ptrs[0] = m1;
  // person_ptrs[1] = m2;
  // person_ptrs[2] = s3;
  // person_ptrs[3] = s4;

  // mine_ptrs[0] = g1;
  // mine_ptrs[1] = g2;

  // hall_ptrs[0] = t1;

 //Set the number of objects, persons, mines, and halls
  // num_objects = 7;
  // num_persons = 4;
  // num_mines = 2;
  // num_halls = 1;
  //********************************************************

  //Stores the pointers to all Game_Objects in a linked list called object_ptrs
  object_ptrs.push_front(m1);
  object_ptrs.push_back(m2);
  object_ptrs.push_back(s3);
  object_ptrs.push_back(s4);
  object_ptrs.push_back(Clouseau);
  object_ptrs.push_back(g1);
  object_ptrs.push_back(g2);
  object_ptrs.push_back(t1);
  

  //Stores the pointers to all Game_Objects in a linked list called active_ptrs. If an object dies, it will be removed from this list.
  active_ptrs.push_front(m1);
  active_ptrs.push_back(m2);
  active_ptrs.push_back(s3);
  active_ptrs.push_back(s4);
  active_ptrs.push_back(Clouseau);
  active_ptrs.push_back(g1);
  active_ptrs.push_back(g2);
  active_ptrs.push_back(t1);
 

  //Stores the pointers to all Person objects in a linked list called person_ptrs
  person_ptrs.push_front(m1);
  person_ptrs.push_back(m2);
  person_ptrs.push_back(s3);
  person_ptrs.push_back(s4);
  person_ptrs.push_back(Clouseau);
  
  //Stores the pointers to all Gold_Mine objects in a linked list called mine_ptrs
  mine_ptrs.push_front(g1);
  mine_ptrs.push_back(g2);
 
  //Stores the pointers to all Town_Hall objects in a linked list called hall_ptrs
  hall_ptrs.push_front(t1);

  //Outputs a message
  cout << "    Model default constructed.\n";

  //Shows the status of all objects
  show_status();
  
}

Model::~Model()
//Deletes each object and outputs a message
{
  //Creates an iterator so that the object_ptrs list can be looped through 
  list<Game_Object*>::iterator i;

  //Loops through object_ptrs and deletes all objects
  for (i = object_ptrs.begin(); i != object_ptrs.end(); i++)
    {
      delete (*i);
    }
  
  //********DELETE***************************
  // for (int i = 0; i < num_objects; i++)
  //   {
  //     delete object_ptrs[i];
  //   }
  //*****************************************
  
  cout << "    Model destructed.\n";
}

Person *  Model::get_Person_ptr(int id)
//Searches the person_ptrs list for an object matching the supplied id, returns the pointer if found or 0 if not
{
   //Creates an iterator so that the person_ptrs list can be looped through 
  list<Person*>::iterator i;

  //Loops through person_ptrs 
  for (i = person_ptrs.begin(); i != person_ptrs.end(); i++)
    {
      if ((*i)->get_id() == id)
	{
	  return (*i); //Returns the pointer if a match is found
	}
    }
  //If the object is not found, returns 0
  return 0;

  //*****************DELETE**************************************************
  // for (int i = 0; i < num_persons; i++)   //Iterates through the array
  //   {
  //     if (person_ptrs[i]->get_id() == id)
  // 	{
  // 	  return person_ptrs[i]; //Returns the pointer if a match is found
  // 	}
  //   }  
  // //If the object is not found, returns 0
  // return 0;
  //************************************************************************
}

Gold_Mine * Model::get_Gold_Mine_ptr(int id)
//Searches the mine_ptrs list for an object matching the supplied id, returns the pointer if found or 0 if not
{
  //Creates an iterator so that the mine_ptrs list can be looped through 
  list<Gold_Mine*>::iterator i;

  //Loops through mine_ptrs 
  for (i = mine_ptrs.begin(); i != mine_ptrs.end(); i++)
    {
      if ((*i)->get_id() == id)
	{
	  return (*i); //Returns the pointer if a match is found
	}
    }
  //If the object is not found, returns 0
  return 0;

  //********************DELETE**********************************************
  // for (int i = 0; i < num_mines; i++)   //Iterates through the array elements
  //   {
  //     if (mine_ptrs[i]->get_id() == id)
  // 	{
  // 	  return mine_ptrs[i]; //Returns the pointer if a match is found
  // 	} 
  //   }
  // //If the object is not found, returns 0
  // return 0;
  //********************************************************************
}

Town_Hall * Model::get_Town_Hall_ptr(int id)
//Searches the hall_ptrs list for an object matching the supplied id, returns the pointer if found or 0 if not
{
  //Creates an iterator so that the hall_ptrs list can be looped through 
  list<Town_Hall*>::iterator i;

  //Loops through hall_ptrs 
  for (i = hall_ptrs.begin(); i != hall_ptrs.end(); i++)
    {
      if ((*i)->get_id() == id)
	{
	  return (*i); //Returns the pointer if a match is found
	}
    }
  //If the object is not found, returns 0
  return 0;

 
}

bool Model::update()
//Increments the time, iterates through the object_ptrs array and calls update() for each object, returns true if any of the update() calls returns true
{
  time++;

  //Will be incremented each time an object's update function returns true
  int test = 0;

  //Creates an iterator so that the active_ptrs list can be looped through 
  list<Game_Object*>::iterator i;

  //Loops through active_ptrs and updates all objects
  for (i = active_ptrs.begin(); i != active_ptrs.end(); i++)
    {
      if((*i)->update()) 
	{
	  test++;
	}
    }

  //Loops through active_ptrs and deletes any dead objects
  list<Game_Object*>::iterator it = active_ptrs.begin();

  while(it != active_ptrs.end())
    {
      if((*it)->is_alive() == false)
	{
	  it = active_ptrs.erase(it);
	  cout << "Dead object removed.\n";
	}
      else 
	{
	  ++it;
	}
    }

  //Returns true if any of the update() calls returned true; returns false otherwise
  if (test > 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

void Model::display(View &view)
//Generates the view display for all of the Game_Objects
{
  view.clear();

  //Creates an iterator so that the active_ptrs list can be looped through 
  list<Game_Object*>::iterator i;

  //Displays all objects in active_ptrs
  for (i = active_ptrs.begin(); i != active_ptrs.end(); i++)
    {
      view.plot(*i);
    }
  
   view.draw();
}

void Model::show_status()
//Outputs the time and the status of all of the Game_Objects by calling their show_status()function
{
  cout << "Time: " << time << endl;

  //Creates an iterator so that the object_ptrs list can be looped through 
  list<Game_Object*>::iterator i;

  //Displays all objects in active_ptrs
  for (i = object_ptrs.begin(); i != object_ptrs.end(); i++)
    {
      (*i)->show_status();
    }
}

void Model::handle_new_command(View &view)
//Called when the n TYPE ID X Y command is entered as an input, creates a new object with the input specifications and adds its pointer to the appropriate lists depending on its type
{
  //Defines variable for reading in the rest of the console input
  char type;
  int ID;
  double x, y;

  //Reads in the rest of the console input and throws an Invalid_Input exceptions if any of the inputs are invalid  
  if (!(cin >> type))
    {
      throw Invalid_Input("Please enter a valid object type!");
    }
  else if (!(cin >> ID))
    {
      throw Invalid_Input("Please enter a valid ID number!");
    }
  else if (!(cin >> x >> y))
    {
      throw Invalid_Input("Please enter a valid location!");
    }
  
  //Determines the type of the new object
  switch (type)
    {
    case 'g': //Gold_Mine
      {
      //Check if a Gold_Mine with this ID already exists
      Gold_Mine * minePtr = get_Gold_Mine_ptr(ID);
      if (minePtr)
	{
	  //Throw an Invalid_Input exception if a Gold_Mine with this ID exists
	  throw Invalid_Input("A Gold_Mine with this ID already exists!");
	}
      else 
	{
	  //Create a new Gold_Mine object
	  Cart_Point loc(x,y);
	  Gold_Mine *gNew = new Gold_Mine(ID,loc);
	  //Add its pointer to the appropriate linked lists
	  object_ptrs.push_back(gNew);
	  active_ptrs.push_back(gNew);
	  mine_ptrs.push_back(gNew);
	}
      break;
      }
    
    case 't': //Town_Hall
      {
      //Check if a Town_Hall with this ID already exists
      Town_Hall * hallPtr = get_Town_Hall_ptr(ID);
      if (hallPtr)
	{
	  //Throw an Invalid_Input exception if a Town_Hall with this ID exists
	  throw Invalid_Input("A Town_Hall with this ID already exists!");
	}
      else 
	{
	  //Create a new Town_Hall object
	  Cart_Point loc(x,y);
	  Town_Hall *tNew = new Town_Hall(ID,loc);
	  //Add its pointer to the appropriate linked lists
	  object_ptrs.push_back(tNew);
	  active_ptrs.push_back(tNew);
	  hall_ptrs.push_back(tNew);
	}
      break;
      }
    
     case 'm': //Miner
      {
      //Check if a Person with this ID already exists
      Person * personPtr = get_Person_ptr(ID);
      if (personPtr)
	{
	  //Throw an Invalid_Input exception if a Person with this ID exists
	  throw Invalid_Input("A Person with this ID already exists!");
	}
      else 
	{
	  //Create a new Miner object
	  Cart_Point loc(x,y);
	  Miner *mNew = new Miner(ID,loc);
	  //Add its pointer to the appropriate linked lists
	  object_ptrs.push_back(mNew);
	  active_ptrs.push_back(mNew);
	  person_ptrs.push_back(mNew);
	}
      break;
      }

     case 's': //Soldier
      {
      //Check if a Person with this ID already exists
      Person * personPtr = get_Person_ptr(ID);
      if (personPtr)
	{
	  //Throw an Invalid_Input exception if a Person with this ID exists
	  throw Invalid_Input("A Person with this ID already exists!");
	}
      else 
	{
	  //Create a new Soldier object
	  Cart_Point loc(x,y);
	  Soldier *sNew = new Soldier(ID,loc);
	  //Add its pointer to the appropriate linked lists
	  object_ptrs.push_back(sNew);
	  active_ptrs.push_back(sNew);
	  person_ptrs.push_back(sNew);
	}
      break;
      }

    case 'i': //Inspector
      {
      //Check if a Person with this ID already exists
      Person * personPtr = get_Person_ptr(ID);
      if (personPtr)
	{
	  //Throw an Invalid_Input exception if a Person with this ID exists
	  throw Invalid_Input("A Person with this ID already exists!");
	}
      else 
	{
	  //Create a new Inspector object
	  Cart_Point loc(x,y);
	  Inspector *iNew = new Inspector(ID,loc);
	  //Add its pointer to the appropriate linked lists
	  object_ptrs.push_back(iNew);
	  active_ptrs.push_back(iNew);
	  person_ptrs.push_back(iNew);
      	}
      break;
      }
      
    default:
      throw Invalid_Input("Please enter a valid object type!");
      break;

    }
  //Display the grid
  this->display(view);
}

list<Gold_Mine*> Model::get_Gold_Mine_list()
//Returns a copy of the mine pointers list
{
  return mine_ptrs;
}

void Model::save(ofstream& file)
//Writes the current time and catalog information into the save file, calls each object's save function
{
  file << static_cast<char>(time) << endl << static_cast<char>(active_ptrs.size()) << endl;

  //Creates an iterator so that the active_ptrs list can be looped through 
  list<Game_Object*>::iterator i;

  int counter = 0;

  //Writes the display_codes and id_nums of the objects in active_ptrs to the save file and calls save for each object
  for (i = active_ptrs.begin(); i != active_ptrs.end(); i++)
    {
      file << static_cast<char>((*i)->get_display_code()) << static_cast<char>((*i)->get_id()) << endl;
       (*i)->save(file);
      counter++;
    }

}

void Model::restore(ifstream& file)
//Deletes all existing Game_Objects and empties all lists, restores the time, Game_Objects, and lists
{
  //Clears existing objects
  list<Game_Object*>::iterator i;
  for (i = object_ptrs.begin(); i != object_ptrs.end(); i++)
    {
      delete (*i);
    }

  //Clears all lists
  object_ptrs.clear();
  active_ptrs.clear();
  person_ptrs.clear();
  mine_ptrs.clear();
  hall_ptrs.clear();

  //Counter for keeping track of file line number
  int counter = 1;
  int num_obj = 10;
  while (!file.eof())
    { 
      if (counter == 1)
	{
	  //Read in time from the first line
	  int output;
	  file >> output;
	  time = output;
	}
      else if (counter == 2)
	{
	  //Read in the number of objects from the second line
	  int output;
	  file >> output;
	  num_obj = output;
	}
      else if ((counter > 2) && (counter <= num_obj+2)) 
      	{
      	  string output;
      	  file >> output;
      	  //Read in the catalog info
      	  switch (output.at(0))
      	    {
      	    case 'M':
      	      {
      	      Miner *m1 = new Miner();
      	      m1->set_display_code('M');
      	      m1->set_id_num(output.at(1));
      	      object_ptrs.push_back(m1);
      	      active_ptrs.push_back(m1);
      	      person_ptrs.push_back(m1);
      	      break;
      	      }
      	    case 'm':
      	      {
      	      Miner *m1 = new Miner();
      	      m1->set_display_code('m');
      	      m1->set_id_num(output.at(1));
      	      object_ptrs.push_back(m1);
      	      active_ptrs.push_back(m1);
      	      person_ptrs.push_back(m1);
      	      break;
      	      }
      	    case 'S':
      	      {
      	      Soldier *s1 = new Soldier();
      	      s1->set_display_code('S');
      	      s1->set_id_num(output.at(1));
      	      object_ptrs.push_back(s1);
      	      active_ptrs.push_back(s1);
      	      person_ptrs.push_back(s1);
      	      break;
      	      }
      	    case 's':
      	      {
      	      Soldier *s1 = new Soldier();
      	      s1->set_display_code('s');
      	      s1->set_id_num(output.at(1));
      	      object_ptrs.push_back(s1);
      	      active_ptrs.push_back(s1);
      	      person_ptrs.push_back(s1);
      	      break;
      	      }
      	    case 'I':
      	      {
      	      Inspector *i1 = new Inspector();
      	      i1->set_display_code('I');
      	      i1->set_id_num(output.at(1));
      	      object_ptrs.push_back(i1);
      	      active_ptrs.push_back(i1);
      	      person_ptrs.push_back(i1);
      	      break;
      	      }
      	    case 'i':
      	      {
      	      Inspector *i1 = new Inspector();
      	      i1->set_display_code('i');
      	      i1->set_id_num(output.at(1));
      	      object_ptrs.push_back(i1);
      	      active_ptrs.push_back(i1);
      	      person_ptrs.push_back(i1);
      	      break;
      	      }
      	    case 'G':
      	      {
      	      Gold_Mine *g1 = new Gold_Mine();
      	      g1->set_display_code('G');
      	      g1->set_id_num(output.at(1));
      	      object_ptrs.push_back(g1);
      	      active_ptrs.push_back(g1);
      	      mine_ptrs.push_back(g1);
      	      break;
      	      }
      	    case 'g':
      	      {
      	      Gold_Mine *g1 = new Gold_Mine();
      	      g1->set_display_code('g');
      	      g1->set_id_num(output.at(1));
      	      object_ptrs.push_back(g1);
      	      active_ptrs.push_back(g1);
      	      mine_ptrs.push_back(g1);
      	      break;
      	      }
      	    case 'T':
      	      {
      	      Town_Hall *t1 = new Town_Hall();
      	      t1->set_display_code('T');
      	      t1->set_id_num(output.at(1));
      	      object_ptrs.push_back(t1);
      	      active_ptrs.push_back(t1);
      	      hall_ptrs.push_back(t1);
      	      break;
      	      }
      	    case 't':
      	      {
      	      Town_Hall *t1 = new Town_Hall();
      	      t1->set_display_code('t');
      	      t1->set_id_num(output.at(1));
      	      object_ptrs.push_back(t1);
      	      active_ptrs.push_back(t1);
      	      hall_ptrs.push_back(t1);
      	      break;
      	      }
      	    }
	 
      	}
      if (counter == 2 + num_obj)
	break;

      counter++;

    }

  //Goes through the pointer list in order and calls the object's restore function
  list<Game_Object*>::iterator j;
  for (j = active_ptrs.begin(); j != active_ptrs.end(); j++)
    {
      (*j)->restore(file, *this);
    }

}



//*************NOTES*********************************************************

//Maybe need to change i++ to ++i when iterating through the linked lists

//Right now my new objects created in handle_new_command may be written over if another object of the same type is added because the pointer name gNew will be overwritten 

//Might need to change get_Gold_Mine_list - currently shallow copying, maybe need a deep copy

//****************************************************************************
