#include <iostream>
#include <vector>  
#include <iomanip>
using namespace std;

struct Process_Observer { //Process_Observer dung de luu thong tin process
    int remaning_burst;
    int start_time;
    int finish_time;
};

struct Process {
    int id = 0;
    string name;
    int arrival_time = 0;
    int burst_time = 0;
    Process_Observer observer;

    int turnarround_time() {
        return observer.finish_time - arrival_time;
    }
    int waiting_time() {
        return observer.finish_time - arrival_time - burst_time;
    }
    int response_time() {
        return observer.finish_time - arrival_time;
    }
};

void Nhap_sl_process(int &soluongProcess);
void Nhap_Process(vector<Process>& Job_pool, int soluongProcess);
void Long_term_scheduling(vector<Process>& Job_pool, int soluongProcess);
bool New_process_arrived();
void Push_new_process_to_ready_queue();
void SRTF(vector<Process>& Ready_queue);

int main()
{
    //Nhap
    int soluongProcess; 
    Nhap_sl_process(soluongProcess);
    vector<Process> Job_pool(soluongProcess);
    Nhap_Process(Job_pool, soluongProcess);

    // thuat toan scheduling
    Long_term_scheduling(Job_pool, soluongProcess);

    cout << "\n---DONE---" << endl;
    return 0;
}

void Nhap_Process(vector<Process>& Job_pool, int soluongProcess)
{
    for (int i = 0; i < soluongProcess; i++)
    {
        int id = i+1;
        int arrival_time, burst_time;
        string name;
        cout << "Nhap Process Name, Arrival Time, Burst Time: ";
        cin >> name >> arrival_time >> burst_time;
        Job_pool[i].id = id; // Process ID
        Job_pool[i].name = name; // Process Name
        Job_pool[i].arrival_time = arrival_time; //Arrival Time
        Job_pool[i].burst_time = burst_time; // Burst Time
        Job_pool[i].observer.remaning_burst = burst_time;
    }
}
void Nhap_sl_process(int &soluongProcess)
{
    cout << "Nhap so luong process: ";
    cin >> soluongProcess;
}
void Long_term_scheduling(vector<Process>& Job_pool, int soluongProcess)
{
    vector<Process> Ready_queue; // Khoi tao ready queue
    int system_time = 0; //t ban dau = 0

    while (!Job_pool.empty() && !Ready_queue.empty()) //Neu ca 2 empty thi da chay het process
    {
        if (New_process_arrived()) {
            Push_new_process_to_ready_queue();
        }
        SRTF(Ready_queue);
        system_time ++;
    }
}
