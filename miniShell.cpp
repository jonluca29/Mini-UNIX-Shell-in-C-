#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

// Split a line into words on whitespace.
static std::vector<std::string> parse(const std::string& line) {
    std::vector<std::string> args;
    std::istringstream iss(line);
    std::string word;
    while (iss >> word){
	    args.push_back(word);
    }
    return args;
}

// Returns true if the command was a built-in and has been handled.
static bool run_builtin(const std::vector<std::string>& args) {
    if (args[0] == "exit") {
        std::cout << "Shell exited\n";
        exit(0);
    }
    
    if (args[0] == "cd") {
	const char* dir;
	if (args.size() > 1){
    		dir = args[1].c_str();
	}
	else{
    		dir = getenv("HOME");	
	}
       
	if (dir == nullptr || chdir(dir) != 0){
		perror("cd");
	}
        
	return true;
    }
    return false;
}

static void run_external(const std::vector<std::string>& args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Child: build a null-terminated argv and replace this process.
        std::vector<char*> argv;
	for (size_t i = 0; i < args.size(); i++){
		argv.push_back(const_cast<char*>(args[i].c_str()));
	}
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        perror(argv[0]);  // only reached if exec failed
        _exit(127);
    }

    // Parent: wait for the child so it doesn't become a zombie.
    int status;
    waitpid(pid, &status, 0);
}

int main() {
    std::string line;

    while (true) {
        std::cout << "mini-shell> " << std::flush;

        if (!std::getline(std::cin, line)) {  // Ctrl+D
            std::cout << "\nShell exited\n";
            break;
        }

        std::vector<std::string> args = parse(line);
        if (args.empty()) continue;	// equivalent to the user pressing enter with an empty command line

        if (run_builtin(args)) continue;
        run_external(args);
    }
    return 0;
}
