// SPIKES - Spiky Mazes https://www.spoj.com/problems/SPIKES/
// #backtracking
// Jarmtin is interested in cultures and the history behind them. 
// Of course this interest has a reason: as he studies the choivans’ 
// past he discovers the hidden entrances of mazes he knows contain 
// valuable information.  However there is a catch: the mazes contain spiky traps!
// Jarmtin is quite the agile type, but there is a limit to everyone,
// thus he will only be able to avoid a number of traps.
// This motivates the question can he make it through the mazes?



 

// Input

// The first line of a test case contains three integers n, m and j. 
// n (2<=n<=40) the number of rows, 
// m (2<=n<=40) the width of each row
// j (0<=j<=20) the number of times Jarmtin can avoid spikes. 

// Then n lines containing m characters; 
// The character ‘x’ will be used for the place of the treasure, 
// ‘@’ for an entrance (which is also an exit), 
// ‘#’ for walls,
//  ‘.’ for a safe walking tile and ‘s’ for spikes. 
// Note that you cannot walk into walls and the maze is completely surrounded by walls outside what you can see. 
// There is always at least one entrance/exit and always an x where the treasure is.

 

// Output

// You should output “SUCCESS” if Jarmtin can make it in and out alive, and “IMPOSSIBLE” if there is no way you can make it out alive.


#include <iostream>
#include <string>


class mazeProblem{
    private:
        static const char 
        TREASURE = 'x',
        DOOR = '@',
        WALL = '#',
        SAFE = '.',
        SPIKES = 's';


        char ** maze;
    public:
    int n, m, j;

    mazeProblem(int n, int m, int j){
        this->n = n;
        this->m = m;
        this->j = j;

        maze = new char*[n];

        for(int ii=0; ii< n; ii++){
            maze[ii] = new char[m];
        }
    }

    ~mazeProblem(){
        delete[] maze;
    }

    friend std::ostream &operator<<( std::ostream &output, const mazeProblem &problem ) { 
        const int m = problem.m;
        const int n = problem.n;
        
        
        for (size_t ii = 0; ii < m; ii++)
        {
            for (size_t jj = 0; jj < n; jj++)
            {
                output << problem.maze[ii][jj];
            }
            output << std::endl;
        }
        return output;            
    }

    friend std::istream &operator>>( std::istream  &input, mazeProblem &problem ) { 
        const int m = problem.m;
        const int n = problem.n;
        
        for(int jj = 1; jj < n; jj++){
            std::string token;
            std::cin >> token;
            std::cout << token << std::endl;
            problem.maze[jj][0] = mazeProblem::WALL;
            problem.maze[jj][m] = mazeProblem::WALL;

            for(int ii = 1; ii < m; ii++){
                problem.maze[jj][ii] = token[ii-1];
            }
        }

        memset(problem.maze[0], mazeProblem::WALL, m);
        memset(problem.maze[n], mazeProblem::WALL, m);
        return input;            
    }

    bool solvable(){
        return false;
    }

    bool solvable(const int x, const int y){
        if(x < 0 || x >= m) return false;
        if(y < 0 || y >= n) return false;

        if(maze[x][y] == WALL || maze[x][y] == SPIKES && !(j > 0) ){
            return false;
        }



        return true;
    }

};


int main(){
    int m, n, j;

    std::cin >> n >> m >> j;

    mazeProblem problem(n,m,j);

    std::cin >> problem;

    std::cout << problem;

    if(problem.solvable()){
        std::cout << "SUCCESS" << std::endl;
    }
    else{
        std::cout << "IMPOSSIBLE" << std::endl;
    }
}