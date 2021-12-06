#include "dlist.h"
#include <iostream>
using namespace std;

struct _member{
    string name;
    int duration;
    
    _member(string name, int duration){
        this->name = name;
        this->duration = duration;
    }
};

class _agent{
    const string int2Status[4] = {"platinum", "gold", "silver", "regular"};
    Dlist<_member> memberList[4];
    int currTime, nextFreeTime;
public:
    _agent(){
        currTime = -1;
        nextFreeTime = -1;
    }

    void inputClient(string name, string status, int duration){
        cout << "Call from " << name << " a " << status << " member" << endl;
        for (int i = 0; i < 4; ++i){
            if (status == int2Status[i]){
                _member* member = new _member(name, duration);
                memberList[i].insertBack(member);
                return;
            }
        }
        cout << "Error in inputClient, status not found" << endl;
    }

    bool tick(){
        currTime++;
        // cout << "Starting tick #" << currTime << endl;
        if (currTime <= nextFreeTime)
            return false;
        for (int i = 0;i < 4; ++i)
            if (!memberList[i].isEmpty()){
                _member* member = memberList[i].removeFront();
                cout << "Answering call from " << member->name << endl;
                nextFreeTime = currTime + member->duration;
                delete member;
                return false;
            }
        return true;
    }
};

int main(){
    int n, t, currTime = 0, duration;
    string name, status;
    _agent agent;
    cin >> n;
    cout << "Starting tick #" << currTime << endl;
    while (n){
        n--;
        cin >> t;
        while (t > currTime){
            agent.tick();
            currTime++;
            cout << "Starting tick #" << currTime << endl;
        }
        cin >> name >> status >> duration;
        agent.inputClient(name, status, duration);
    }
    while (!agent.tick()){
        currTime++;
        agent.tick();
        cout << "Starting tick #" << currTime << endl;
    }
}