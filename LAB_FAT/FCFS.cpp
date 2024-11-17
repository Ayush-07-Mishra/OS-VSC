#include<iostream>
#include<vector>
#include<string>

using namespace std;

void FCFS(vector<int> &request, int head){
    int seekTime = 0;
    int n = request.size();
    for(int i =0;i<n;i++){
        cout << "move from " << head << " to " << request[i] << " with seek " << abs(head - request[i]) << endl;
        seekTime += abs(head - request[i]);
        head = request[i];
    }

    cout << "Total seek time: " << seekTime << endl;
}

int main(){
    int n, head;
    cout << "Enter the number of requests: ";
    cin >> n;
    vector<int> request;
    for(int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        request.push_back(temp);
    }
    cout << "Enter the initial head position: ";
    cin >> head;
    FCFS(request, head);
    return 0;
}