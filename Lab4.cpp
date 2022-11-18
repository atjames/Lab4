#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const string inputfileName = "input.txt";

// Lab 4 by Andrew James
// It's important that the .txt file has the same exact structure as the example given.
// If it starts at anything other than P1 the program will crash.
// Program can take any number of processes, just ensure it at P1. 

void schedule(vector<string> Procs, vector<double> CPU, double numofProcs, double Q)
{
    int time = 0;
    vector<double> BurstTime = CPU;
    double total_turn_around_time = 0, total_wait_time = 0, tp = 0;;
    vector<double> wait_time;

    while (1)
    {
        bool isDone = true; // true if all process are completed
        for (int i = 0; i < numofProcs; i++)
        {

            if (BurstTime.at(i) > 0)
            {
                cout << Procs.at(i) << " running." << endl;
                isDone = false;
                if (BurstTime.at(i) > Q)
                {
                    time = time + Q; // set current time for each quantum run
                    BurstTime.at(i) = BurstTime.at(i) - Q; // subtract time from burst
                }
                else
                {   
                    cout << Procs.at(i) << " completed!" << endl;
                    //calulcate time it takes process to run
                    time = time + BurstTime.at(i);
                    wait_time.push_back(time - CPU.at(i));
                    BurstTime.at(i) = 0;
                }

            }

        }

        if (isDone == true) // exit loop if all process done
        {
            break;
        }
    }

    for (int i = 0; i < CPU.size(); i++)
    {
        total_wait_time += wait_time.at(i);
    }


    for (int i = 0; i < CPU.size(); i++)
    {
        total_turn_around_time += (CPU.at(i) + wait_time.at(i));
        tp += CPU.at(i);
    }


    cout << "\nCompleting calculations...\n" << endl;

    cout << "Total Turn Around Time: " << total_turn_around_time << endl;
    cout << "Total Average Turn Around Time: " << (total_turn_around_time / numofProcs) << endl;
    cout << "Total Wait Time: " << total_wait_time << endl;
    cout << "Total Average Wait Time: " << (total_wait_time / numofProcs) << endl;
    cout << "Throughput: " << (tp / numofProcs) << endl;

}


double returnasDouble(string x) // method to convert string to double
{
    double returnValue = 0;

    stringstream convertodouble(x);
    convertodouble >> returnValue;

    return returnValue;
}


int main() {

    ifstream file(inputfileName);
    string line;
    vector<string> items;
    string item;
    double NumOfProcs = 0, Q = 0;

    vector<string> Processes; // two vectors to hold Procceses and CPU_BURST. They will be used in parallel. 
    vector<double> CPU_BURST;


    while (getline(file, line)) // tokenize input file. seperator is a space.
    {
        stringstream linestream(line);
        while (getline(linestream, item, ' '))
        {
            items.push_back(item);
        }
    }

    int index = 0;
    for (string x : items)  // looping though the items vector that holds all our tokens and initlizing our variables.
    {
        if (x == "NumofProc:") {
            NumOfProcs = returnasDouble(items.at(index + 1));
        }
        if (x == "Q") {
            Q = returnasDouble(items.at(index + 2));
        }

        if (x == "P1")
        {
            for (int i = index; i < items.size(); i += 2) // iterate over items. increment by +2 so we move to each new line. Store each process and CPU_BURST in their respective vectors. 
            {
                Processes.push_back(items.at(i));
                CPU_BURST.push_back(returnasDouble(items.at(i + 1)));
            }
            break;
        }

        index++;

    }

    schedule(Processes, CPU_BURST, NumOfProcs, Q);
    return 0;


}

