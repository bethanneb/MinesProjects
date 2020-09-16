/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Read the complete assignment instructions before beginning.  Also look
// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete several methods, and add any others as needed for your
// solution.

/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
*/
void maze_solver::_read_maze(istream& in) {
    string symbol;
    in >> _rows >> _columns; //read in number of rows and columns
    maze = new char [(_rows*_columns) + 1]; //declares a char pointer that contains each character of the maze
    int i = 0;
    while (!in.eof()) { //while the end of the file has not been reached
        in >> maze[i]; //read in each character to the char pointer
        i++;
    }
    maze[i] = 0; //set this to zero because in the string library there is always a zero at the end of the string
                //this is something that the string library does and makes things like str.length() possible
                //also how char arrays are used in c, because there are no strings, but useful and simpler in this case
}


/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {
    for (int r = 0; r < _rows; r++) { //print out each row
        string str = ""; //declares an empty string
        for (int c = 0; c < _columns; c++) { //for each column in that row
            str+= maze[(r*_columns) + c]; //add the current row to str
        }
        cout << str << endl; //print the current row in the loop
    }
}

/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {
    //use the rows and columns as x and y points
    //ex. 1,1
    //check each row, column point for if it is a #, ., o, or a *
    for (int i = 0; i < _rows*_columns; i++) { //for the number of chars in the maze char pointer //counts top to bottom in .txt file
        if (maze[i] == _start) {        //if the beginning of the maze char pointer is either a '*' or an 'o' depending on if we are using a stack or a queue
            _current.x = i % _columns; //find the remainder to find which column it should be, ex. 6 % 5 = 1 so column 1(second column)
            _current.y = i / _columns; //divide by columns so that it can find rows, ex. 6 / 5 = 1.something but rounds down to 1 (second row)
            //cout << _current.x << " is x and " << _current.y << " is y" << endl;
            break; //break the loop once it finds the '*' or the 'o'
        }
    }
}

//determines where we start depending on if the user chooses a stack or a queue
//pops the next point off the stack or pulls the next point off of a queue
point maze_solver::_nextPoint() {
    if (_use_stack) { //if we're using a stack then start from the top and keep popping off the top because LIFO (last in first out)
        point rc = s.top(); //assigns the point to the top of the stack
        s.pop(); //then removes the point
        return rc; //return the next point
    }
    //else, if we're are using a queue then start from the front and keep popping off the front because FIFO (first in first out)
    point rc = queue.front(); //if we're using a queue then assign the point to the front of the queue
    queue.pop(); //remove the point
    return rc; //return the next point
}

//if user chooses to use a stack then pushes point to top of stack
//if user chooses to use a queue then pushes point to the front of the queue
void maze_solver::_pushPoint(point p) {
    if (_use_stack) { //if we use a stack
        s.push(p); //push the point onto the stack
    }
    else { //otherwise, we are using a queue
        queue.push(p); //so push the point onto the queue
    }
}

/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 Notes:

 - Your initial point should have been pushed/enqueued in the _initialize()
   method.

 - Set the _no_more_steps variable to true when there are no more reachable
   points, or when the maze was successfully solved.

 - Set the _goal_reached variable to true if/when the maze was successfully
   solved.

 - You should write an '@' over every location you have previously visited,
   *except* for the start and goal positions - they should remain 'o' and '*',
   respectively.

 - Since the run() method will call _print_maze() in between calls to _step(),
   you probably want to try to make progress on each call to step.  On some
   mazes, depending on your approach, it may be possible to add the same
   point multiple times to your stack or queue - i.e., if a point is reachable
   from multiple other points.  When this happens, your code will work, but
   it may make very slow progress.  To fix the problem, simply run a loop to
   remove any already visited points from your stack or queue at the beginning
   or end of _step().

 - There are many approaches to dealing with invalid/unreachable points; you
   can choose to add them and then remove them next time you get into _step(),
   you can choose to not add them in the first place, etc.

 - It is strongly recommended that you make helper methods to avoid code
   duplication; e.g., a function to detect that a point is out of bounds is
   a real help on the mazes with no walls.  You can also think about pulling
   out methods that do the actual acting on stacks/queues - this will reduce
   code duplication, since everything is identical between the two except
   for whether you use your stack or queue.  E.g., you could have methods
   named "_push", "_pop", "_next" which use the appropriate data structure.
*/

void maze_solver::_step() {
    point left;
    left.x = _current.x - 1; //row minus 1 so it's the spot to the left of the current point
    left.y = _current.y;
    point right;
    right.x = _current.x + 1; //row plus 1 so it's the spot to the right of the current point
    right.y = _current.y;
    point up;
    up.x = _current.x;
    up.y = _current.y - 1; //column minus 1 so it's the spot beneath the current point
    point down;
    down.x = _current.x;
    down.y = _current.y + 1; //column plus 1 so it's the spot above the current point
    //to access starter point use current.x and current.y
    //start at starting point
    //if a point is valid, push it to either the stack or the queue
    if (_is_valid(up)) {
        _pushPoint(up);
    }
    if (_is_valid(down)) {
        _pushPoint(down);
    }
    if (_is_valid(right)) {
        _pushPoint(right);
    }
    if(_is_valid(left)) {
        _pushPoint(left);
    }
    if (!_havePoints()) {
        _no_more_steps = true;
        return;
    }
    while (_havePoints()) { //while the stack s is not empty
        point q = _nextPoint(); //the next point is assigned to the next point returned from the function
        //makes it so if a point is to the left or right of a current point and also at the end of the loop that it is
        //not processed from the stack, it is just popped off
        char c = _charAt(q); //find out what character is at the top point of the stack
        if (c == _end) { //if c is a '*' or an 'o' depending on if we use a stack or a queue BUG?
            _goal_reached = true; //then the goal is reached
            _no_more_steps = true; //then there are no more steps
            break;
        }
        if (c == '.') { //if we have not reached the end of the maze
            _current.x = q.x; //then assign the current point to the next point for both x and y
            _current.y = q.y;
            maze[(_current.y * _columns) + _current.x] = '@'; //change that char to an '@' at the current point in the maze
            break;
        }
    }
    //some directions I wrote for myself:
    //if there is a * in the stack then the goal was reached because otherwise there wouldn't be star in the stack
    //because at some point there was no way to reach that star because there were invalid points all around it
    //if I go there change current point to that point and change the . to an @
    //change the periods to @ signs as user steps through
}

bool maze_solver::_is_valid(point p) {
    //if it's not #, o, or an @ and its not less than or greater than or equal to the number of rows and columns, then return true, otherwise return false
    if ((p.y < 0) || (p.y >= _rows)) {
        return false;
    }
    if ((p.x < 0) || (p.x >= _columns)) {
        return false;
    }
    char currentChar = _charAt(p);
    if (currentChar == '#') {
        return false;
    }
    if (currentChar == 'o') {
        return false;
    }
    if (currentChar == '@') {
        return false;
    }
    return true;
}

//returns the char that is at the point passed to it in the maze
char maze_solver::_charAt(point p) {
    return maze[(p.y*_columns)+p.x];
}

//checks if either the stack or the queue is empty
bool maze_solver::_havePoints() {
    if (!s.empty()) {
        return true;
    }
    if (!queue.empty()) {
        return true;
    }
    return false;
}

/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	_use_stack = use_stak;
    _start = 'o';
    _end = '*';
	_do_pause = pause;

	_no_more_steps = false;
	_goal_reached = false;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		_maze_name = infile;
	} else {
		_maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);

	_read_maze(fin);

	fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached 
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize(); //initializes the starting points of the maze

	cout << "Solving maze '" << _maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	_print_maze();
	cout << endl;
	_pause();

	// main loop
	while (!_no_more_steps) {
		_step();
		cout << endl;
		_print_maze();
		cout << endl;
		_pause();
	}

	// final output to user
	cout << "Finished: ";
	if (_goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
	if (!_do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
}

