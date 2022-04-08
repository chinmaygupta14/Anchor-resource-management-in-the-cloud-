#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
        // typedef vector<ll> vi;
        // typedef set<ll> si;
        // typedef vector<char> vc;
        // typedef set<char> sc;
        // typedef pair<ll,ll> pii;
        // typedef multiset<ll> msi;
        // typedef multiset<char> msc;
        // #define forp(i,a,b) for(ll i=a;i<b;i++)
        // #define form(i,a,b) for (ll i=a;i>=b;i--)
        // #define pb push_back
        // #define mp make_pair
       
       
        
        
       
int main(void)
{
        //   ios_base::sync_with_stdio(false); 
        //   cin.tie(NULL); cout.tie(NULL);
    
    // jobs[i][0] represent the size of the job i and the rest of the members of the vector job[i] are the preferences of the job i. similarly for machines its the capacity and preferences.
    vector<vector<int>> jobs;
    vector<vector<int>> machines;
    
    vector<int> jobSize;
    vector<int> machineCapacity;
    
    // status of the jobs and machines indicating they are free or not
    vector<bool> jobStatus(jobs.size())= {0};
    vector<bool> machineStatus(machines.size())= {0};
           
    // set of pair of job and the number of preferences left of thge particular job
    set<pair<int,int>> freeJob;
    
    // inserting the job_id and the number of preferences of it
    int numberOfJobs = jobStatus.size();
    for(int i=0;i<numberOfJobs;i++){
        freeJob.insert(make_pair(i,jobs[i].size()));
    }               
    
    int jobID;
    map<int,int> matching;
    vector<set<int>> machineMatch;
    
    // revised DA 
    while(freeJob.size()>0){
        jobID = (*freeJob.begin()).first;
        if(jobs[jobID].size() == 0) {
            freeJob.erase(freeJob.begin());
            continue;
        }
        
        int m = jobs[0];
        
        if(machineCapacity[m] >= jobSize[jobID]) {
            matching[jobID] = m;
            machineCapacity[m] -= jobSize[jobID];
            machineMatch[m].insert(jobID);
            jobStatus[jobID] = 1;
            freeJob.erase(make_pair(jobID,jobs[jobID].size()));
        }
        
        else{
            //int bestRejected;
            int preferencesSize = machines[m].size[1];
            for(auto i = --machines[m].end(); *i != jobID || machineCapacity[m] >= jobSize[jobID] ; i--){
                int jobMachine = *i;
                if(jobStatus[jobMachine] == 1){
                    jobStatus[jobMachine]=0;
                    freeJob.insert(make_pair(jobMachine,jobs[jobMachine].size()));
                    machineCapacity[m] +=jobSize[jobMachine];
                    
                }
            }
            
            if(machineCapacity[m] >= jobSize[jobID]) {
                matching[jobID] = m;
                machineCapacity[m] -= jobSize[jobID];
                //*machines[m].begin() -= *jobs[jobID].begin();
                jobStatus[jobID] = 1;
                freeJob.erase(make_pair(jobID,jobs[jobID].size()));
            }
            
            else{
                
            }
            
        }
        
        
    }
    
    //capacity
    for(int i=0;i<machines.size();i++){
        cout<<*machines[i].begin();<<" ";
        
    }
    
    // matching
    for(auto c : matching){
        cout<< c.first <<" --->" << c.second<<endl;
    }
                  
}
              
           return 0;
        }
        
        
    
        