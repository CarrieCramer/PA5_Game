
#include <iostream>
#include "Model.h"
#include "View.h"
using namespace std;

void do_move_command(Model &model, View &view);
//Commands Miner ID to move to location (x,y)

void do_work_command(Model &model, View &view);
//Commands Miner ID1 to start mining at Gold_Mine ID2 and deposit the gold at Town_Hall ID3

void do_inspect_command(Model &model, View &view);
//Commands Inspector ID to start inspecting

void do_stop_command(Model &model, View &view);
//Commands Miner ID to stop whatever it is doing

void do_go_command(Model &model, View &view);
//Advances one time step by updating each object once

void do_run_command(Model &model, View &view);
//Advance one time step and update each object, repeating until either the update function returns true for at least one object or 5 time steps have passed

void do_list_command(Model &model, View &view);
//Lists the status of all objects using the Model's show_status function

void do_attack_command(Model &model, View &view);
//Commands Person ID1 to attack Person ID2; Checks for input errors; Only soldiers will attack another Person.

/* Save and restore commands need to be debugged
void do_save_command(Model &model);
//Saves the game in the specified filename

void do_restore_command(Model &model);
//Restores the game using the specified filename
*/


