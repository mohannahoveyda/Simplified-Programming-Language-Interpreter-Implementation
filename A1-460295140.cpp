#include <iostream>
#include <fstream>
using std::ofstream;
using std::cerr;
using std::endl;
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
int productcalculation(string str,unordered_map<string, int> variables){
	string currentPart=str;
	bool flag=true;
	int bank=1;
    string delimiter1="*";
    string run= "run";
	while(flag==true){
        string temp;
		if(currentPart.find(delimiter1)== -1){
           	temp=currentPart;
           	flag=false;
		}
        else {
       		temp=currentPart.substr(0,currentPart.find(delimiter1));
        }
         		
		if( (temp.front()>='a' && temp.front() <='z')|| (temp.front()>='A' && temp.front()<='z')){
        	if(variables.count(temp)==1 && temp!= run){
            	bank=bank*variables.at(temp);
            }
            else if(variables.count(temp)==0 && temp!=run){
          		bank=0;
            }
		}
        else{
            int val=stoi(temp,nullptr,10);
            bank=bank*val;
        }
        currentPart=currentPart.substr(currentPart.find(delimiter1)+1,currentPart.size());  
    }
    return bank;
}


int substraction(string str,unordered_map<string, int> variables){
	string currentPart=str;
	bool flag=true;
	int bank=0;
    string delimiter1="-";
    bool isfirst=true;
    
	while(flag==true){
        string temp;
		if(currentPart.find(delimiter1)== -1){
           	temp=currentPart;
           	flag=false;
		}
        else {
       		temp=currentPart.substr(0,currentPart.find(delimiter1));
        }
        int P=productcalculation(temp,variables);
        if(isfirst==true){
        	bank=bank+P;	
        	isfirst=false;
		}else{
			bank=bank-P;
		}
		
        currentPart=currentPart.substr(currentPart.find(delimiter1)+1,currentPart.size());  
    }
    return bank;
}




int addcalculation(string str,unordered_map<string, int> variables){
	string currentPart=str;
	bool flag=true;
	int bank=0;
    string delimiter1="+";
	while(flag==true){
        string temp;
		if(currentPart.find(delimiter1)== -1){
           	temp=currentPart;
           	flag=false;
		}
        else {
       		temp=currentPart.substr(0,currentPart.find(delimiter1));
        }
        int P=substraction(temp,variables);
		bank=bank+P;
        currentPart=currentPart.substr(currentPart.find(delimiter1)+1,currentPart.size());  
    }
    return bank;
}



string removeSpaces(string str){
str.erase(remove(str.begin(),str.end(),' '),str.end());
return str;
}

int main(){
	string line;
     int questionMark;
    string run= "run";
    unordered_map<string, int> variables;
    string variableName;
    int variableValue;
    ofstream sourceFile;
    ifstream sourceFile1;
    int i;
    string variableName1;
    string variableName2;
    sourceFile.open("in.txt");
    if(!sourceFile){
		cerr << "Error: file could not be opened"<<endl;
		exit(1);
    }
	cout << "\nEnter zabanche program:\n\n";
	////////////////////////copying in file
	do{
    	getline(cin,line);
    	sourceFile<<line<<endl;
	}while(line.compare(run)!=0);
    sourceFile.close();
    
    sourceFile1.open("in.txt");
    if(!sourceFile1){
        cerr << "Error: file could not be opened"<<endl;
        exit(1);
    }
	do{
		getline(sourceFile1,line);
		line=removeSpaces(line);
		if (line[0]=='?'){
        	int  count=0;
        	while( line [count]==' ' || line[count]=='?'){
            	count++;
           	}
			size_t pos=line.find(line[count]);
          	variableName=line.substr(pos);
         	
          	string a;
          	getline(cin,a);
		if (a==eof()){
		cout<< "\nUnexpected end of input\n";		
		}
		if (isdigit(a.at(0))==0){
		cout<< "\nError, you should enter a number as input not a character or string\n";
                return -1;
		}
          	variableValue=stoi(a,nullptr,10);
          	variables.insert(make_pair(variableName, variableValue));
    	}
		else if(line[0]=='!'){
             
           string khorujiName= line.substr(1,line.size());
	   int khorujiVal=variables[khorujiName];
 		cout<<khorujiVal<< "\n";
            
        }
        ////////Expressions
        else{
		bool flag=true;
		if(line==run){
 
		flag==false;
		}
		else{
        	
            string delimiter="=";
            int bank=1;
            string beforeEqual=line.substr(0,line.find(delimiter));
            string afterEqual=line.substr(line.find(delimiter)+1,line.size());
            int functionoutput= addcalculation(afterEqual,variables);
            if(variables.count(beforeEqual)==1){
               variables[beforeEqual]=functionoutput;
 		}
             else if(variables.count(beforeEqual)==0){
            variables.insert(make_pair(beforeEqual, functionoutput));
            }
			
		}
   } }while(line.compare(run)!=0);
    sourceFile1.close();
	return 0;
}
