#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(void)
{
        //   ios_base::sync_with_stdio(false); 
        //   cin.tie(NULL); cout.tie(NULL);
    
    // jobs[i][0] represent the size of the job i and the rest of the members of the vector job[i] are the preferences of the job i. similarly for machines its the capacity and preferences.
    
    
    int nojobs,nomachines;
   
    
    
    cout<<"enter the number of jobs:- "<<endl;
    cin>>nojobs;
    vector<int> jobSize(nojobs,0) ;
    vector<vector<int>> jobs(nojobs);
    int mID,mpr;
    for(int i=0;i<nojobs;i++){
        cout<<"enter the size of the job "<<i<<endl;
        cin>>jobSize[i];
        cout<<"enter the number of preferences of job "<< i<< " "<<endl;
        cin>>mpr;
        cout<<"enter the preferences of the job "<<i<<" "<<endl;
        for(int j=0;j<mpr;j++){
            cin>>mID;
            jobs[i].push_back(mID);
        }
    }
    
    cout<<"enter the number of machines:- "<<endl;
    cin>>nomachines;
    int jID,jpr;
    vector<vector<int>> machines(nomachines);
    vector<int> machineCapacity(nomachines,0);
    
    for(int i=0;i<nomachines;i++){
        cout<<"enter the size of the machine "<<i<<endl;
        cin>>machineCapacity[i];
        cout<<"enter the number of preferences of machine "<< i<< endl;
        cin>>jpr;
        cout<<"enter the preferences of the machine "<<i<<endl;
        for(int j=0;j<jpr;j++){
            cin>>jID;machines[i].push_back(jID);
        }
    }
    
    
    // status of the jobs and machines indicating they are free or not
    vector<bool> jobStatus(nojobs,0);
    vector<bool> machineStatus(nomachines,0);

    // set of pair of job and the number of preferences left of thge particular job
    set<int> freeJob;
    vector<int> jobPreferences(nojobs);
    
    // inserting the job_id and the number of preferences of it
   
    for(int i=0;i<nojobs;i++){
        freeJob.insert(i);
         jobPreferences[i] = jobs[i].size();
    }
    
    int jobID;
    map<int,int> matching;
    
    int x=0;
    // revised DA 
    while(freeJob.size()>0){
        jobID = *freeJob.begin();
        if(jobPreferences[jobID] == 0) {
            freeJob.erase(freeJob.begin());
            continue;
        }
        int in=0;
        while(jobs[jobID][in] == -1 )in++;
        int m = jobs[jobID][in];
        
        if(machineCapacity[m] >= jobSize[jobID]) {
            matching[jobID] = m;
            machineCapacity[m] -= jobSize[jobID];
            
            jobStatus[jobID] = 1;
            freeJob.erase(jobID);
        }
        
        
        else{
            int i=machines[m].size()-1;
            int bestRejected = machines[m][i];
            for(; i>0 && machines[m][i] != jobID && machineCapacity[m]<jobSize[jobID] ;i--){
                if(jobStatus[i] ==1 ){
                    jobStatus[i] == 0;
                    freeJob.insert(i);
                    machineCapacity[m] += jobSize[i]; 
                    jobPreferences[i]--;
                    for(int j=0;j<jobs[i].size();j++){
                        if(jobs[i][j] == m) jobs[i][j]=-1;
                    }
                    
                    for(int mac=0; mac<machines[m].size();mac++){
                        if(machines[m][mac] == jobID) machines[m][mac] = -1;
                    }
                   
                }
            }
            
            if(machineCapacity[m] >= jobSize[jobID]){
                matching[jobID] = m;
                machineCapacity[m] -= jobSize[jobID];
                
                jobStatus[jobID] = 1;
                freeJob.erase(jobID);
            }
            
            else{
                jobPreferences[jobID]--;
                    for(int j=0;j<jobs[jobID].size();j++){
                        if(jobs[jobID][j] == m) jobs[jobID][j]=-1;
                    }
                    
                    // for(int mac=0; mac<machines[m].size();mac++){
                    //     if(machines[m][mac] == jobID) machines[m][mac] = -1;
                    // }
            }
            
        }
        
        x++;
        cout<<"iteration :- "<< x <<endl;
         //capacity
        for(int i=0;i<machines.size();i++){
            cout<<machineCapacity[i]<<" ";
        }
        cout<<endl;
        // matching
        for(auto c : matching){
            cout<< c.first <<" --->" << c.second<<endl;
        }
    }
    
    //capacity
    for(int i=0;i<machines.size();i++){
        cout<<machineCapacity[i]<<" ";
    }
    cout<<endl;
    // matching
    for(auto c : matching){
        cout<< c.first <<" --->" << c.second<<endl;
    }
                  

              
           return 0;
        }
        
        
    
        
