/*	Angshuman Ghosh		2017CS01


Program to block some specific signals and show the blocked or pending signals


*/


#include <iostream>
#include <set>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main(){

        int o_size = 0;

        set<int> signals;	// set of blocked signals
        set<int>::iterator it;

        sigset_t block, wait;	// signal set
        
        sigemptyset(&block);

	//	add the signals to be blocked
        
        sigaddset(&block, SIGINT);
        sigaddset(&block, SIGTERM);
        sigaddset(&block, SIGQUIT);
        
        
        sigprocmask(SIG_BLOCK, &block, NULL);	// block the signals specified in signal set
        
        
        while(1){
                
                 
                sigpending(&wait);	// fill the signal set wait with pending signals
                

		//	check for the signals that are blocked

                if(sigismember(&wait, SIGINT))
                        signals.insert(SIGINT);
                if(sigismember(&wait, SIGTERM))
                        signals.insert(SIGTERM);
                if(sigismember(&wait, SIGQUIT))
                        signals.insert(SIGQUIT);
                        
                if(o_size < signals.size()){	// print the signals when there is a new blocked signal
                        for(it = signals.begin() ; it!=signals.end() ; it++){
                                cout << ((*it == SIGINT) ? "SIGINT" : (*it == SIGTERM) ? "SIGTERM" : "SIGQUIT" ) << endl;
                        
                        }
                        
                        cout << "====================" << endl;
                }
                
                o_size = signals.size();        // update the signal size keeper var  
        
        }



}
