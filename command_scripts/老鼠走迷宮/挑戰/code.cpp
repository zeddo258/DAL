//*******************************************************/
// Exercise 02: Path finding in a Maze by WuYH@CYCU 2019/09
//*******************************************************/
//#define DEBUG
//#define SHOW
#define QUIZ

#include <iostream>                                     //cin, cout
#include <cstdlib>                                      //system
#include <string>	                                    //string type
#include <cstdio>                                       //fscanf
#include <cstring>                                      //strcpy
#include <new>	                                        //new
#include <vector>	                            		//vector

using namespace std;

typedef enum {Fun1, Fun2} Modes;                        // denote each mission
typedef enum {Copy = -1,
                Right, Down, Left, Up} Moves;           // denote the direction of each move

//*** CoXY object: 2D coordinate (Y, X) *****************/
class CoXY {
    int y;                                              // Y coordinate
    int x;                                              // X coordinate
public:
    CoXY(): y(0), x(0)
    {   }; //end CoXY default constructor

    CoXY(int py, int px)                                // a coordinate (py, px)
    {   y = py;
        x = px;
    }   //end CoXY constructor

    CoXY(const CoXY& pt): y(pt.y), x(pt.x)              // copy a coordinate
    {   }   //end CoXY copy constructor

//*******************************************************/
// setXY(py, px): set up the coordinate (py, px)
// getX(pt): get the X coordinate of pt
// getY(pt): get the Y coordinate of pt
// nextXY(dir): get the coordinate after the move toward dir
// match(pt): check if the coordinate is the same as pt
// inRange(maxLimit): check if the coordinate is in the range
//*******************************************************/
    void setXY(const int py, const int px)              // set up the coordinate (py, px)
    {   y = py;
        x = px;
    } //end CoXY::setXY

    int getX() const                                    // get the X coordinate of pt
    {   return x;   } //end CoXY::getX

    int getY() const                                    // get the Y coordinate of pt
    {   return y;   } //end CoXY::getY

    CoXY nextXY(Moves dir) const
    {   CoXY    pt(y,x);                                // create a copy of the coordinate (y, x)

        switch (dir)                                    // get the coordinate after the move toward dir
        {   case Right: pt.x++;
                        break;
            case Down:  pt.y++;
                        break;
            case Left:  pt.x--;
                        break;
            case Up:    pt.y--;
                        break;
            default:    ;                               //just a copy at the same coordinate
        } //end switch
        return pt;
    } //end CoXY::nextXY

    bool match(const CoXY& pt) const                    // check if it is the same as pt
    {   if ((y == pt.y) && (x == pt.x))
            return true;
        return false;
    } //end CoXY::match

    bool inRange(const CoXY& maxLimit) const
    {   if ((y >= 0) && (y < maxLimit.y)
            && (x >= 0) && (x < maxLimit.x))
            return true;                                // if it is in the range of (0,0) and maxLimit
        return false;                                   // out of range
    } //end CoXY::inRange
}; //end CoXY class
//*******************************************************/

//*** Maze object: a matrix/maze ************************/
class Maze {
    #define LIMIT   coMax.getX() * coMax.getY() + 1
    typedef enum {
        symO = 'O',                                     // Obstacle
        symE = 'E',                                     // Empty cell
        symG = 'G',                                     // Goal
        symV = 'V',                                     // Visited cell
        symR = 'R' } Symbols;                           // cell on the route

//*** StackR object: a route ***************************/
class   stackR
{   typedef struct sN							        // node type used in stackR
    {   CoXY        p;                                  // the coordinate of a cell
        Moves       first, prev;                        // directions of the first move and the previous move
        int         numG;                               // required number of goals to find
        struct sN   *next;    						    // link to the next node
    }   stackNode;
    stackNode       *topPtr;                            // implemented stackR as a linked list
public:
    stackR(): topPtr(NULL)
    {	} //end stackR initializer

//*******************************************************/
// isEmpty(): check if it is empty or not
// getTop(pt, first, prev): get the top of stackR
// pop(): remove the top of stackR
// pop(pt, first, prev): get the top of stackR and then remove it
// push(pt, first, prev): set pt as a new top of stackR
// copyStack(aStack): deep copy of a stackR object
//*******************************************************/
    bool isEmpty()  const
    {   return topPtr == NULL;  }  //end stackR::isEmpty

    void getTop(CoXY& pt, Moves& first, Moves& prev, int& numG)    // get the top of stackR
    {	if (isEmpty())
            cout << endl << "Try to retrieve from an empty stack!" << endl;
        else
        {   pt = topPtr->p.nextXY(Copy);                // nextXY(Copy): just a copy of the coordinate
            first = topPtr->first;                      // get the direction of the first move
            prev = topPtr->prev;                        // get the direction of the previous move
            numG = topPtr->numG;                        // get the required number of goals to find
        } // end else
    }	// end stackR::getTop

    void pop()                                          // remove the top of stackR
    {	if (isEmpty())
            cout << endl << "Try to remove the top of an empty stack!" << endl;
        else
        {	stackNode *tempPtr = topPtr;

            topPtr = topPtr->next;                      // set a new top of stackR
            tempPtr->next = NULL;
            delete tempPtr;
            tempPtr = NULL;
        } // end else
    }	// end stackR::pop

    void pop(CoXY& pt, Moves& first, Moves& prev, int& numG)
    {   getTop(pt, first, prev, numG);                  // get the top of stackR
        pop();                                          // remove the top of stackR
    }	// end stackR::pop

    void push(const CoXY& pt, const Moves& first, const Moves& prev, int& numG)    // set pt as a new top of stackR
    {   try
        {	stackNode *newPtr = new stackNode;          // create a new node

            newPtr->p = pt.nextXY(Copy);                // nextXY(Copy): just a copy of the coordinate
            newPtr->first = first;                      // set the direction of the first move
            newPtr->prev = prev;                        // set the direction of the previous move
            newPtr->numG = numG;                        // set the required number of goals to find
            newPtr->next = topPtr;
            topPtr = newPtr;                            // set a new top of stackR
        } // end try
        catch (std::bad_alloc& ba)					    // unable to allocate space
        {   std::cerr << endl << "bad_alloc on stack caught: " << ba.what() << endl;
        }   // end catch
    }	// end stackR::push

    ~stackR()
    {   while (!isEmpty())                              // clear up the entire stackR
            pop();
        topPtr = NULL;
    }   // end destructor

    void copyStack(const stackR& obj)                   // deep copy of a stackR object
    {   while (!isEmpty())                              // clear up the entire stackR
            pop();
        if (!obj.isEmpty())
        {   stackNode *newPtr = new stackNode; 	        // create a new node

            topPtr = newPtr;                            // set up the top of stackR
            newPtr->p = obj.topPtr->p.nextXY(Copy);     // nextXY(Copy): just a copy of the coordinate
            newPtr->first = obj.topPtr->first;          // copy the direction of the first move
            newPtr->prev = obj.topPtr->prev;            // copy the direction of the previous move
            newPtr->numG = obj.topPtr->numG;            // copy the required number of goals to find
            for (stackNode *oldPtr = obj.topPtr->next; oldPtr != NULL; oldPtr = oldPtr->next)
            {   newPtr->next = new stackNode;           // append a new node
                newPtr = newPtr->next;
                newPtr->p = oldPtr->p.nextXY(Copy);     // nextXY(Copy): just a copy of the coordinate
                newPtr->first = oldPtr->first;          // copy the direction of the first move
                newPtr->prev = oldPtr->prev;            // copy the direction of the previous move
                newPtr->numG = oldPtr->numG;            // copy the required number of goals to find
            }  // end for
            newPtr->next = NULL;                        // the end of linked list
        } //end else
    } //end stackR:copyStack
};	//end stackR class
//*******************************************************/

    char    **mArray;                                   // pointer array to record a 2D maze
    CoXY    coMax, coBegin;                             // upper bounds on the coordinates, the starting cell
    int     numGoal;                                    // total number of goals
    int     **sArray;                                   // pointer array to record the steps in a 2D maze

//*******************************************************/
// nextMove(dir): get the next direction in a predefined order
// getSymbol(pt): get the symbol on cell pt
// setSymbol(pt, val): put symbol val into cell pt
// setRoute(route): put symbol 'R' into each cell of a route
//*******************************************************/

#ifdef DEBUG
    Moves nextMove(Moves dir)                           // get the next direction in a counter-clockwise order
    {   switch (dir)
        {   case Copy:  return Right;                   // initial move...
            case Right: return Up;                      // 1st direction
            case Up:  return Left;                      // 2nd direction
            case Left:  return Down;                    // 3rd direction
            case Down:    return Right;                 // 4th direction
        } //end switch
        return Right;
    } //end nextMove
#else
    Moves nextMove(Moves dir)                           // get the next direction in a clockwise order
    {   switch (dir)
        {   case Copy:  return Right;                   // initial move...
            case Right: return Down;                    // 1st direction
            case Down:  return Left;                    // 2nd direction
            case Left:  return Up;                      // 3rd direction
            case Up:    return Right;                   // 4th direction
        } //end switch
        return Right;
    } //end nextMove
#endif  // DEBUG

    char getSymbol(const CoXY& pt)                      // get the symbol on cell pt
    {   if (mArray != NULL)
            return mArray[pt.getY()][pt.getX()];
        return 'X';
    } //end Maze::setSymbol

    void setSymbol(const CoXY& pt, Symbols val)         // put symbol val into cell pt
    {   if (mArray != NULL)
            mArray[pt.getY()][pt.getX()] = val;
    } //end Maze::setSymbol

    void initStep()                                     // initialize the step array
    {   if (sArray == NULL)                             // initialize a maze to store the steps
        {   sArray = new int * [coMax.getY()];          // prepare a series of pointers for rows
            for (int i = 0; i < coMax.getY(); i++)
            {   sArray[i] = new int [coMax.getX()];     // one row
                for (int j = 0; j < coMax.getX(); j++)
                    sArray[i][j] = LIMIT;
            } //end for
        } //end if
    } //end Maze::initStep

    void setStep(const CoXY& pt, int val)               // set the step size into cell pt
    {   if (sArray != NULL)
            sArray[pt.getY()][pt.getX()] = val;
    } //end Maze::setStep

    int getStep(const CoXY& pt)                         // get the step size on cell pt
    {   if (sArray != NULL)
            return sArray[pt.getY()][pt.getX()];
		return 'X';
    } //end Maze::getStep

    void setRoute(stackR route)                         // put symbol 'R' into each cell of a route
    {   CoXY    pt;
        Moves   non1, non2;
        int     non3;

        route.pop(pt, non1, non2, non3);
        setSymbol(pt, symG);                            // put symbol 'R' into cell pt
        while (!route.isEmpty())
        {   route.pop(pt, non1, non2, non3);
            setSymbol(pt, symR);                        // put symbol 'R' into cell pt
            if (pt.match(coBegin))                      // repeat it until the starting cell
                break;
        } //end while
    } //end Maze::setRoute

public:
    Maze(): mArray(NULL), coMax(-1,-1), coBegin(0,0), numGoal(1), sArray(NULL)
    {   }   //end Maze initializer

    Maze(const Maze& src): coMax(src.coMax), coBegin(src.coBegin), numGoal(src.numGoal)
    {   if (src.mArray != NULL)                         // deep copy of a Maze object
        {   mArray = new char * [coMax.getY()];         // prepare a series of pointers
            for (int i = 0; i < coMax.getY(); i++)
            {   mArray[i] = new char [coMax.getX() + 1];    // each line is ended by an extra '\0'
                strcpy(mArray[i], src.mArray[i]);       // copy the maze line by line
            } //end for
        } //end if
        if (src.sArray != NULL)                         // deep copy of a Maze object
        {   sArray = new int * [coMax.getY()];          // prepare a series of pointers
            for (int i = 0; i < coMax.getY(); i++)
            {   sArray[i] = new int [coMax.getX()];     // each line
                for (int j = 0; j < coMax.getX(); j++)
                    sArray[i][j] = src.sArray[i][j];    // copy the maze line by line
            } //end for
        } //end if
    }   //end Maze copy constructor

    ~Maze()
    {   if (mArray != NULL)
        {   for (int i = 0; i < coMax.getY(); i++)
                delete [] mArray[i];                    // remove the maze line by line
            delete [] mArray;                           // remove the set of pointers
            mArray = NULL;
        } //end if
        if (sArray != NULL)
        {   for (int i = 0; i < coMax.getY(); i++)
                delete [] sArray[i];                    // remove the maze line by line
            delete [] sArray;                           // remove the set of pointers
            sArray = NULL;
        } //end if
    } //end Maze destructor

//*******************************************************/
// load(fileName, fun): read a file to create a maze
// show(fun): show on screen a maze, including its size
// save(fileName): save the maze as a file
// clr(): clear up the maze
//*******************************************************/
    bool load(string fileName, Modes fun)               // read a file to create a maze
    {   FILE    *infile = NULL;                         // a file handle
        bool    success = false;                        // read a file successfully or not

        fileName = "input" + fileName + ".txt";
        infile = fopen(fileName.c_str(), "r");		    // open the file
        if (infile == NULL)
            cout << endl << fileName << " does not exist!" << endl;
        else
        {   int arg1 = 0, arg2 = 0;

            fscanf(infile,"%d %d", &arg1, &arg2);
            numGoal = 1;
            if (fun == Fun2)
                numGoal = getM(1,100);
            coMax.setXY(arg2, arg1);                    // the number of lines & columns in the maze
            if ((coMax.getY() > 0) && (coMax.getX() > 0))
            {   int     line = 0;
                char    *temp = new char [coMax.getX() + 1]; // buffer to keep one line

                mArray = new char * [coMax.getY()];     // prepare a series of pointers
                while (fscanf(infile, "%s", temp) != EOF)
                {   mArray[line] = new char [coMax.getX() + 1];  // each line is ended by an extra '\0'
                    strcpy(mArray[line++], temp);       // load the maze line by line
                } //end while
                if (line == coMax.getY())
                    success = true;                     // the number of lines is correct
                delete [] temp;							// DEBUG 
            } //end if
            fclose(infile);							    // close the file
        } //end else
        if (success)
            initStep();
        return success;
    } //end Maze::load

//********************************************************************************************************************/
// Given M, generate all Fibonacci Series with indexes 1, 2, ..., M by loop.
//********************************************************************************************************************/
int getM(int minM, int maxM)                                            // get a number from user
{   // lower bound of M, upper bound of M, return a qualified number
    int     temp;
    string  inputS;                                                     // input string
    bool    isNum;                                                      // whether it is a number

    do
    {   cout << endl << "Number of G (goals): ";
        cin >> inputS;
        isNum = true;
        for (int i = 0; (i < inputS.length()) && (isNum); i++)
            if ((inputS[i] > '9') || (inputS[i] < '0'))                 // ASCII code in ['1'~'9']
                isNum = false;
        if (!isNum)                                                     // repeat it until getting a number
            continue;
        temp = strtoul(inputS.c_str(), NULL, 10);                       // string to a decimal number
        if ((temp >= minM) && (temp <= maxM))                           // in the range of two bounds
            break;
        else
            cout << endl << "### The number must be in [" << minM << "," << maxM << "] ###" << endl;
    } while (true);   // end do-while
    return temp;										                // exit only if it succeeds
}   // end getM

    void show(Modes fun) const                          // show on screen a maze
    {   if (mArray == NULL)
            return;
        if (fun == Fun2)                                // if it's mission 2
        {   cout << endl << coMax.getY() << " " << coMax.getX();
            cout << " " << numGoal << endl;             // show the maze size and the number of goals
        }   // end if
        for (int i = 0; i < coMax.getY(); i++)
            cout << mArray[i] << endl;                  // display the maze line by line
        cout << endl;
#ifdef DEBUG
         for (int i = 0; i < coMax.getY(); i++) {
	        for (int j = 0; j < coMax.getX(); j++)
            	cout << "\t" << sArray[i][j];                  // display the maze line by line
        	cout << endl;
    	}	// end for
#endif
    } //end Maze::show

    void save(string fileName) const                    // save the maze as a file
    {   FILE		*outfile = NULL;                    // a file handle

        if (mArray != NULL)
        {   fileName = "output" + fileName + ".txt";
            outfile = fopen(fileName.c_str(), "w");	    // open the file
            if (outfile == NULL)
                cout << endl << fileName << " cannot be created!" << endl;
            else
            {   for (int i = 0; i < coMax.getY(); i++)  // save the maze line by line as a file
                    fprintf(outfile, "%s\n", mArray[i]);
                fprintf(outfile, "\n");
                fclose(outfile);		                // close the file
            } //end inner else
        }   // end outer if
    } //end Maze::save

    void clr()                                          // clear up the maze
    {   if (mArray != NULL)
        {   for (int i = 0; i < coMax.getY(); i++)
                delete [] mArray[i];                    // remove the maze line by line
            delete [] mArray;                           // remove the set of pointers
            mArray = NULL;
        } //end if
        if (sArray != NULL)
        {   for (int i = 0; i < coMax.getY(); i++)
                delete [] sArray[i];                    // remove the maze line by line
            delete [] sArray;                           // remove the set of pointers
            sArray = NULL;
        } //end if
    } //end Maze::clr

//*******************************************************/
// findGoals(vM): find a route on the maze
//*******************************************************/
    bool findGoals(Maze& vM)                            // path finding for one or more goals
    {   stackR  		aStack;
        CoXY    		pt(coBegin), newP;
        vector<CoXY>	goalS;
        Moves   		pre = Right, cur = Copy;
        int             numGold = numGoal;              // old number of goals to find

        vM.setSymbol(pt, symV);                         // set the starting point visited on vMaze
        setSymbol(pt, symR);                            // put the starting point into the route on aMaze
        while (true)
        {	if (pre == cur)                             // tried every direction but failed
            {   if  (numGoal == numGold)                // no new goal is found from this point
                    setSymbol(pt, symE);                // exclude the last point from the route
                if (aStack.isEmpty())                   // no more route to try ...
                    return false;
                aStack.pop(pt, pre, cur, numGold);      // backtracking to the previous point of the route
            }   // end outer-if
            else
            {   if (cur == Copy)                        // If it is the first move, try to continue the previous direction
                {	cur = pre;
                    numGold = numGoal;
                }   // end if
                newP = pt.nextXY(cur);                  // the next point
                if (newP.inRange(coMax))
                {   if (getSymbol(newP) == symG)        // reach the goal: terminate the entire loop
                    {   aStack.push(pt, pre, nextMove(cur), numGold);
                        setSymbol(newP, symR);          // trick: prevent repeatedly counting on the same goal
                      	goalS.push_back(newP);			// memorize the goals
                        if (!(--numGoal))
                        {   setSymbol(newP, symG);      // trick: recover the last goal (only work for the case of one single goal)
                            while (!goalS.empty())
        					{	pt = goalS.back();
								setSymbol(pt, symG);	// recover G
								goalS.pop_back();
							}	// end while
                            return true;                // a successful route is got!
                        }
                        else                            // not all goals yet...
                        {   pre = cur;                  // first try to continue the previous direction
                            cur = Copy;
                            pt.setXY(newP.getY(), newP.getX());
                            continue;                   // extend the route by moving to the next point
                        }   // end else
                    }   // end inner-if
                    else if (vM.getSymbol(newP) == symE)
                    {   aStack.push(pt, pre, nextMove(cur), numGold);
                        vM.setSymbol(newP, symV);       // set visited on vMaze
                        setSymbol(newP, symR);          // append a node to the route on aMaze
                        pre = cur;                      // first try to continue the previous direction
                        cur = Copy;
                        pt.setXY(newP.getY(), newP.getX());
#ifdef  SHOW
                        vM.show(Fun1);
                        system("pause");
#endif // SHOW
                        continue;                       // extend the route by moving to the next point
                    }   // end inner-else-if
                } //end middle-if
                cur = nextMove(cur);                    // try the next direction
            }   // end outer-else
        } //end while
    } //end findGoals

//*******************************************************/
// shortestPath(vM): find the shortest path to one goal on the maze
//*******************************************************/

    int shortestPath(Maze& vM, stackR& minR)            // shortest path finding for multiple goals
    {   stackR  curR;                                   // current path, shortest path
        Maze    tM(vM);                                 // a temporary maze
        CoXY    pt(coBegin), newP, dest;
        Moves   pre = Right, cur = Copy;
        int     curL = 1, minL = LIMIT, unused=0;       // current path length, shortest path length

        vM.setSymbol(pt, symV);                         // set the starting point visited on vMaze
        tM.setSymbol(pt, symR);                         // put the starting point into the route on tMaze
        tM.setStep(pt, curL);                           // put the starting point into the route on sMaze
        while (true)
        {   if (pre == cur)                             // tried every direction but failed
            {   tM.setSymbol(pt, symE);                 // exclude the last point from the route
                curL--;                                 // current path length minus 1
                if (curR.isEmpty())                     // no more route to try ...
                    break;
                curR.pop(pt, pre, cur, unused);         // backtracking to the previous point of the route
            }   // end outer-if
            else
            {   if (cur == Copy)                        // 1st move: continue the previous direction
                    cur = pre;
                    // cur = Right;						// Simplified: always start at Right
                newP = pt.nextXY(cur);                  // the next point
                if ((newP.inRange(coMax)) && ((curL + 1) < minL))
                {   if (tM.getSymbol(newP) == symG)     // reach the goal: terminate the entire loop
                    {   curR.push(pt, pre, nextMove(cur), unused);    // append a node to the current path
                        minL = ++curL;                  // new shortest path length
                        minR.copyStack(curR);           // update the shortest path
                        minR.push(newP, pre, nextMove(cur), unused);   // append the goal to the shortest path
#ifdef  SHOW
                        vM.show(Fun1);
                        tM.show(Fun1);
                        //tM.showSteps();
                        system("pause");
#endif // SHOW

                        continue;                       // back to the previous point before the goal
                    }   // end inner-if
                    else if ((vM.getSymbol(newP) == symE) ||
                             ((vM.getSymbol(newP) == symV) && ((curL + 1) < tM.getStep(newP))))
                    {   vM.setSymbol(newP, symV);       // set the current point visited on vMaze
                        curR.push(pt, pre, nextMove(cur), unused);    // append a node to the current path
                        curL++;                         // increment the current path length
                        tM.setSymbol(newP, symR);       // set the symbol of the current point on tMaze
                        tM.setStep(newP, curL);         // set the symbol of the current point on sMaze
                        pre = cur;                      // first try to continue the previous direction
                        cur = Copy;
                        pt.setXY(newP.getY(), newP.getX());
#ifdef  SHOW
                        vM.show(Fun1);
                        tM.show(Fun1);
                        //tM.showSteps();
                        system("pause");
#endif // SHOW
                        continue;                       // extend the route by moving to the next point
                    }   // end inner-else-if
                } //end middle-if
                cur = nextMove(cur);                    // try the next direction
            }   // end outer-else
        } //end while
        // vM.show(Fun1);
        // tM.show(Fun1);
		tM.clr();                                       // release the space occupied by tMaze
        if (!minR.isEmpty())                            // a shortest path exists:
            setRoute(minR);                             // set the symbols for the shortest path
        else
            minL = 0;
        return minL;
    } //end Maze::shortestPath

    int shortestPath(Maze& vM)                          // shortest path finding for one goal
    {   stackR    unusedR;                              // unused route

        return shortestPath(vM, unusedR);               // overloading
    }   //end shortestPath
}; //end Maze class
//*******************************************************/


//*******************************************************/
// Path finding for one or more goals in a maze
//*******************************************************/
int main(void)
{   char command = 0;							        // user command

    do
    {   Maze    aMaze;                                  // a matrix
        string  fileName;                               // a file name
        Modes   mode = Fun1;                            // default: one goal

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
#ifdef QUIZ
        cout << endl << "* 3. Shortest path *";
#endif // QUIZ
        cout << endl << "********************";
#ifdef QUIZ
        cout << endl << "Input a command(0, 1, 2, 3): ";
#else
        cout << endl << "Input a command(0, 1, 2): ";
#endif // QUIZ
        cin >> command;	    					        // get the command
        if ((command == '1') || (command == '2'))
        {   if (command == '2')
                mode = Fun2;                            // one or more goals
            cout << endl << "Input a file number: ";
            cin >> fileName;

            if (aMaze.load(fileName, mode))	            // load the original matrix
            {   Maze    vMaze(aMaze);		            // a copy to keep the visited cells
                bool    success = aMaze.findGoals(vMaze);   // find a path to one or more goals

                mode = Fun1;                            // reset to default
                vMaze.show(mode);                       // show on screen the visited cells
                if (success)                            // to check if the goal is reached or not
                    aMaze.show(mode);                   // show on screen the route to reach the goal
                vMaze.clr();				            // clear up the copy
            } //end inner-if
            aMaze.clr();						        // clear up the original matrix
        }   //end outer-if
#ifdef QUIZ
        else if (command == '3')	                    // '3': find the shortets path
        {   cout << endl << "Input a file number: ";
            cin >> fileName;

            if (aMaze.load(fileName, mode))	            // load the original matrix
            {   Maze    vMaze(aMaze);		            // a copy to keep the visited cells
                int     minL = 1;

                minL = aMaze.shortestPath(vMaze);       // find the shortest path to one goal
				vMaze.show(mode);                       // show on screen the visited cells
                if (minL > 1)                           // to check if the goal is reached or not
                {   aMaze.show(mode);                   // show on screen the route to reach the goal
                    cout << endl << "Shortest path length = " << minL << endl;
                }   //end inner-if
                else
                    cout << endl << "### There is no path to find a goal! ### " << endl;
                system("pause");
                vMaze.clr();				            // clear up the copy
            } //end inner-if
            aMaze.clr();						        // clear up the original matrix
        }   // end outer else-if
#endif // QUIZ
        else if (command == '0')	                    // '0': stop the program
            break;
        else
            cout << endl << "Command does not exist!" << endl;
    } while (true);
    system("pause");							        // pause the execution
    return 0;
}	// end of main
//*******************************************************/
