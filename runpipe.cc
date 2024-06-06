#include <iostream>
#include <vector>
#include <sstream>    // to tokenize user input
#include <cstring>    // for argv
#include <unistd.h>   // for fork, exec, pipe, etc.
#include <sys/wait.h> // for wait

using namespace std;

vector<char*> split_command(const string& command);

void execute_commands(vector<string>& commands);

int main() {
    string input;
    cout << "Enter a command string: ";
    getline(cin, input);  // Get the entire line of input from the user

    const string pipe_delim = "|";
    vector<string> commands;
    size_t start = 0, end = 0;
    /* the following takes a user inputted string like  "cat numbers.txt |./ops + 30 |./ops / 2 |./ops le 20",
    and turns it into vector commands[["cat numbers.txt"],["./ops + 30"],["./ops / 2"],[./ops le 20]] using "|" as the delimeter
    */
    while ((end = input.find(pipe_delim, start)) != string::npos) {
        commands.push_back(input.substr(start, end - start));
        start = end + pipe_delim.length();
    }
    commands.push_back(input.substr(start));

    execute_commands(commands);

    return 0;
}

/*Function to split a command string into arguments. 
the execv functions take their arguements as an array of pointers -> arguements 
rather than explicit declaration as in the execlp functions. - see [Robbins & Robbins] Unix Systems Programming - Ch 3.5 (pg 78-79)


Function construction: 
Each command must be a pointer in an array argv[*0], argv[*1], argv[*2] etc,
so return type must be an array(vector) of pointers. " vector<char*> "
the function must take a constant call by reference parameter as not to modify it.

 1. declare array of pointers to be returned and used as arguements in exec "vector<char*> argv"
 2. to tokenize the user inputted string, we use the stringstream class which lets us treat strings as streams
    "string arg" is where each section of "command" separated by whitespace will be stored.
 3. while(stringstream is still reading strings separated by whitespace), 
    create a pointer array to store each segment(command) + 1 space for the NULL termination
 4. convert the string into a c-string which is needed for argv (strcpy)
 5. push the pointer array arguement onto the argv vector as a single index which points to the command
    Now when exec calls argv[i] it will contain all the elements which would have been explicitly declared in
    an execlp function EXCEPT the NULL terminator
 6. push back the nullptr to NULL terminate the arguement - ESSENTIAL
 7. return the pointer array/vector argv

        Example: the while loop in main takes user inputted string "cat numbers.txt |./ops + 30 |./ops / 2 |./ops le 20",
        and turns it into vector commands[["cat numbers.txt"],["./ops + 30"],["./ops / 2"],[./ops le 20]]

        if split_command(const string& command) takes vector commands[0] as its parameter ("cat numbers.txt"),
        it turns it into argv[[*arg_cstr]] which is a pointer to ["cat","numbers.txt", NULL]. execv functions need POINTERS to arguements,
        not explicit arguements like execlp functions. Therfore, if it were argv[["cat","numbers.txt", NULL]], it would NOT work
*/
vector<char*> split_command(const string& command) {
    vector<char*> argv;//----------------------------- 1.
    stringstream ss(command);//----------------------- 2.
    string arg;
    while (ss >> arg) {//----------------------------- 3.
        char *arg_cstr = new char[arg.size() + 1];  
        strcpy(arg_cstr, arg.c_str());//-------------- 4.
        argv.push_back(arg_cstr);//------------------- 5.
    }
    argv.push_back(nullptr);//------------------------ 6.
    return argv;//-------------------------------------7.
}

/*Function to execute commands.

Function Construction:
nothing to be returned so return type is void.
takes call by reference parameter to a vector of strings. 
This vector comes post parsing, using "|" as the delimeter, from the loop in main.
If user inputted string "cat numbers.txt |./ops + 30 |./ops / 2 |./ops le 20",
the parameter would be vector commands[["cat numbers.txt"],["./ops + 30"],["./ops / 2"],[./ops le 20]]

 1. initialize integer to the number of commands to be executed
 2. initialize 2 sets of (2x)pipes, each set with an input/read(0) and output/write(1)
 3. open loop to iterate (num_commands) times
 4. for each command, like [cat numbers.txt], split_command into argv[*arguement] - see split_command function above for mechanics
 5. mostly as a helper operation, print to screen what commands are running, exclude the nullptr by stopping at argv.size()-1
 6. Because the last command uses STDOUT_FILENO not a pipe, we check each command except the last one for pipe errors.
    perror("pipe") if to let us know what went wrong, then exit    
 7. Assuming command has been split, and no pipe errors exist, fork() to create a child process
    if the pid < 0, there was an forking error -> exit
 8. If child process is NOT the first command, set STDIN_FILENO = prev_pipefd,
    If child process is NOT the last command, set STDOUT_FILENO = pipefd,
    the first command will use STDIN while the last will use STDOUT. This mechanism provides a chain of communication,
    allowing each process the ability to recieve input/read from a previous process or STDIN
    and communicate its output/write to the next process or STDOUT
                STDIN == P == P == P == STDOUT
 9. execvp command given from argv[*arguement] - NOTE, execvp is near identical to execv EXCEPT, 
    the first parameter of execvp is *file while execv is *path, otherwise both take pointer arrays as arguements -see [Robbins and Robbins] pg.78
    perror if necessary then exit
 10.Parent process closes its end of the pipes and step by step deletes each arguement pointer array after its use to free memory from the heap
    then WAIT(NULL) for child process to complete. ESSENTIAL

*/
void execute_commands(vector<string>& commands) {
    int num_commands = commands.size();//----------------------------------------- 1.
    int pipefd[2], prev_pipefd[2];//---------------------------------------------- 2. 

    for (int i = 0; i < num_commands; ++i) {//------------------------------------ 3.
        vector<char*> argv = split_command(commands[i]);//------------------------ 4.

        // cout << "Executing command: ";//------------------------------------------ 5.
        // for (size_t j = 0; j < argv.size() - 1; ++j) { 
        //     cout << argv[j] << " "; 
        // }
        // cout << endl;

        if (i < num_commands - 1) {//--------------------------------------------- 6.
            if (pipe(pipefd) == -1) { // could also be < 0 like in pipes.c
                perror("pipe"); 
                exit(EXIT_FAILURE); 
            }
        }

        pid_t pid = fork();//----------------------------------------------------- 7. 
        if (pid == -1) { 
            perror("fork"); 
            exit(EXIT_FAILURE); 
        } else if (pid == 0) { // Child process
            if (i > 0) {//-------------------------------------------------------- 8. 
                dup2(prev_pipefd[0], STDIN_FILENO); 
                close(prev_pipefd[0]); 
                close(prev_pipefd[1]);
            }

            if (i < num_commands - 1) { 
                close(pipefd[0]); 
                dup2(pipefd[1], STDOUT_FILENO); 
                close(pipefd[1]); 
            }

            execvp(argv[0], argv.data());//---------------------------------------- 9.
            perror("execvp");
            exit(EXIT_FAILURE);
        } else { // Parent process
            if (i > 0) {//--------------------------------------------------------- 10.
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }

            if (i < num_commands - 1) {
                prev_pipefd[0] = pipefd[0];
                prev_pipefd[1] = pipefd[1];
            }

            for (char* arg : argv) {
                delete[] arg;
            }

            wait(NULL); // Wait for child process to finish
        }
    }
}