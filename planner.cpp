#include <bits/stdc++.h>

using namespace std;

struct state
{

	vector <int> clear;
	vector <int> on_table;
	vector < pair<int,int> > on_top;
	int hold=0;
}inital_state,goal_state;





queue <state> st;


int main(int argc, char *argv[])
{
	char *file=argv[1];
	fstream fin ;
	fin.open(file);
	int num;
	fin>>num;
	cout<<"number of block "<<num<<endl;
	char ch;
	fin>>ch;
	cout<<ch<<endl;
	string temp;
	fin>>temp;
	cout<<temp<<endl;
	//fin>>temp;
	/*while(getline(fin, temp))
	{
	cout<<temp<<endl;
	extract_inital_state(temp);
	}*/

	//cout<<"Himanshu "<<temp<<endl;

	while(fin>>ch)
	{
		fin>>temp;
		//cout<<temp<<" "<<temp.size()<<endl;
		if(temp=="empty)")
		{
			//fin>>ch;
			break;
		}

		else if(temp=="ontable")
		{
			int k;
			fin>>k;
			inital_state.on_table.push_back(k);
			fin>>ch;
		}

		else if(temp=="clear")
		{
			int k;
			fin>>k;
			inital_state.clear.push_back(k);
			fin>>ch;

		}
		else if(temp=="on")
		{
			int k,l;
			fin>>k>>l;
			inital_state.on_top.push_back(make_pair(k,l));
			fin>>ch;
		}
	}


	fin>>temp;
	//cout<<temp<<endl;
	while(fin>>ch)
	{
		fin>>temp;
		cout<<temp<<endl;
		if(temp=="empty)")
		{
			fin>>ch;
			break;
		}

		else if(temp=="ontable")
		{
			int k;
			fin>>k;
			goal_state.on_table.push_back(k);
			fin>>ch;
		}

		else if(temp=="clear")
		{
			int k;
			fin>>k;
			goal_state.clear.push_back(k);
			fin>>ch;

		}
		else if(temp=="on")
		{
			int k,l;
			fin>>k>>l;
			goal_state.on_top.push_back(make_pair(k,l));
			fin>>ch;
		}
	}




	/*for(int i=0;i<goal_state.on_table.size();i++)
	{
		cout<<goal_state.on_table[i]<<endl;
	}*/


	return 0;
}