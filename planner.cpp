#include <bits/stdc++.h>

using namespace std;

struct state
{

	vector <int> clear;
	vector <int> on_table;
	vector < pair<int,int> > on_top;
	int hold;
}inital_state,goal_state;



struct action
{
	int type;
	int num1;
	int num2;
};

queue <state> q;
queue <action> act;
queue <vector <action> > list_ac;

priority_queue <pair <state,int> > pq;
priority_queue < pair <action,int> > pact;
queue < pair <vector <action>,int > > p_list_ac;


int get_heuristics(state st)
{
	int total = 1+goal_state.clear.size()+goal_state.on_table.size()+goal_state.on_top.size();

	for(int i=0;i<st.clear.size();i++)
	{
		for(int j=0;goal_state.clear.size();j++)
		{
			if(st.clear[i]==goal_state.clear[j])
			{
				total=total-1;
			}
		}
	}

	for(int i=0;i<st.on_table.size();i++)
	{
		for(int j=0;goal_state.on_table.size();j++)
		{
			if(st.on_table[i]==goal_state.on_table[j])
			{
				total=total-1;
			}
		}
	}

	for(int i=0;i<st.on_top.size();i++)
	{
		for(int j=0;goal_state.on_top.size();j++)
		{
			if(st.on_top[i]==goal_state.on_top[j])
			{
				total=total-1;
			}
		}
	}

	if(st.hold==goal_state.hold)
	{
		total--;
	}

	return total;
}

void output_data_2(state st,int num)
{
	cout<<"-------------NEXT STATE ------------"<<num<<"\n";
	cout<<st.hold<<endl;
	for(int i=0;i<st.clear.size();i++)
	{
		cout<<st.clear[i]<<" ";
	}
	cout<<endl;

	for(int i=0;i<st.on_table.size();i++)
	{
		cout<<st.on_table[i]<<" ";
	}
	cout<<endl;

	for(int i=0;i<st.on_top.size();i++)
	{
		cout<<st.on_top[i].first<<" , "<<st.on_top[i].second<<" | ";
	}
	cout<<endl;


	cout<<"-----------------------------\n";
}

void output_data_1(action ac,int num)
{
	cout<<"------- ACTION ------------ "<<num<<endl;
	cout<<ac.type<<endl;
	cout<<ac.num1<<endl;
	cout<<ac.num2<<endl;
	cout<<"--------------------------------------"<<endl;
}

void effect_action_4(state st,int num1,int num2)
{
	struct state cpy;
	cpy.hold=0;
	for(int i=0;i<st.clear.size();i++)
	{
		if(st.clear[i]==num2)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(st.clear[i]);
		}
	}

	cpy.clear.push_back(num1);

	for(int i=0;i<st.on_table.size();i++)
	{
		cpy.on_table.push_back(st.on_table[i]);
	}

	for(int i=0;i<st.on_top.size();i++)
	{
		cpy.on_top.push_back(st.on_top[i]);
	}
	cpy.on_top.push_back(make_pair(num1,num2));
	//output_data_2(cpy,4);
	q.push(cpy);
}
void effect_action_1(state st,int num)
{
	struct state cpy;
	cpy.hold=num;
	for(int i=0;i<st.clear.size();i++)
	{
		if(st.clear[i]==num)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(st.clear[i]);
		}
	}

	for(int i=0;i<st.on_table.size();i++)
	{
		if(st.on_table[i]!=num)
		cpy.on_table.push_back(st.on_table[i]);
	}

	for(int i=0;i<st.on_top.size();i++)
	{
		if(st.on_top[i].first!=num)
		cpy.on_top.push_back(st.on_top[i]);
	}
	//output_data_2(cpy,1);
	q.push(cpy);
}

void effect_action_2(state st, int num1, int num2)
{
	struct state cpy;
	cpy.hold=num1;
	for(int i=0;i<st.clear.size();i++)
	{
		if(st.clear[i]==num1)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(st.clear[i]);
		}
	}

	cpy.clear.push_back(num2);

	for(int i=0;i<st.on_table.size();i++)
	{
		cpy.on_table.push_back(st.on_table[i]);
	}

		for(int i=0;i<st.on_top.size();i++)
	{
		if(st.on_top[i]!=make_pair(num1,num2))
		cpy.on_top.push_back(st.on_top[i]);
	}

	//output_data_2(cpy,2);
	q.push(cpy);


}

void effect_action_3(state st,int num)
{
	struct state cpy;
	cpy.hold=0;

	for(int i=0;i<st.on_table.size();i++)
	{
		cpy.on_table.push_back(st.on_table[i]);
	}

	cpy.on_table.push_back(num);

	for(int i=0;i<st.clear.size();i++)
	{
		
			cpy.clear.push_back(st.clear[i]);
		
	}

	cpy.clear.push_back(num);

	for(int i=0;i<st.on_top.size();i++)
	{
		cpy.on_top.push_back(st.on_top[i]);
	}
	//output_data_2(cpy,3);
	q.push(cpy);

}

void get_action(state st,int index)
{
	vector <action> ele;
	if(index==1)
	{
		ele=list_ac.front();
		list_ac.pop();
	}


	if(st.hold!=0)
	{
		//cout<<"Himanshu"<<endl;
		for(int i=0;i<st.clear.size();i++)
		{
			struct action temp;
			temp.type=4;
			temp.num1=st.hold;
			temp.num2=st.clear[i];
			act.push(temp);
			//output_data_1(temp,4);
			effect_action_4(st,st.hold,st.clear[i]);

			if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				list_ac.push(v);
			}
			else
			{
				vector <action> v;
				v=ele;
				v.push_back(temp);
				list_ac.push(v);
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}

		}


		struct action temp;
		temp.type=3;
		temp.num1=st.hold;
		temp.num2=0;
		act.push(temp);
		//output_data_1(temp,3);
		if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				list_ac.push(v);
			}
			else
			{
				vector <action> v;
				v=ele;
				v.push_back(temp);
				list_ac.push(v);
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}
		effect_action_3(st,temp.num1);
	}

	else
	{
		//cout<<"Tolani"<<endl;
		for(int i=0;i<st.clear.size();i++)
		{
			for(int j=0;j<st.on_table.size();j++)
			{
				if(st.on_table[j]==st.clear[i])
				{
					struct action temp;
					temp.type=1;
					temp.num1 = st.clear[i];
					temp.num2 = 0;
					act.push(temp);
					//output_data_1(temp,1);
					if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				list_ac.push(v);
			}
			else
			{
				vector <action> v;
				v=ele;
				v.push_back(temp);
				list_ac.push(v);
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}
					effect_action_1(st,st.clear[i]);
				}
			}
		}


		for(int i=0;i<st.on_top.size();i++)
		{
			for(int j=0;j<st.clear.size();j++)
			{
				struct action temp;
				if(st.on_top[i].first==st.clear[j])
				{
					
					temp.type=2;
					temp.num1=st.on_top[i].first;
					temp.num2=st.on_top[i].second;
					act.push(temp);
					//output_data_1(temp,2);
					if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				list_ac.push(v);
			}
			else
			{
				vector <action> v;
				v=ele;
				v.push_back(temp);
				list_ac.push(v);
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}
					effect_action_2(st,temp.num1,temp.num2);
				}
			}
		}


	}
}

int  is_goal_state(state st)
{
	for(int i=0;i<goal_state.clear.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.clear.size();j++)
		{
			if(goal_state.clear[i]==st.clear[j])
			{
				flag=1;
				break;
			}
		}

		if(flag==0)
		{
			return 0;
		}
	}

	for(int i=0;i<goal_state.on_top.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.on_top.size();j++)
		{
			if(goal_state.on_top[i]==st.on_top[j])
			{
				flag=1;
				break;
			}
		}

		if(flag==0)
		{
			return 0;
		}
	}

	for(int i=0;i<goal_state.on_table.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.on_table.size();j++)
		{
			if(goal_state.on_table[i]==st.on_table[j])
			{
				flag=1;
				break;
			}
		}

		if(flag==0)
		{
			return 0;
		}
	}

	if(st.hold!=goal_state.hold)
	{
		return 0;
	}

	return 1;

}



void BFS(state st)
{
	get_action(st,0);
	//cout<<"Size= "<<q.size()<<" "<<act.size()<<endl;
	while(!act.empty())
	{
		//cout<<"SIZE= "<<q.size()<<" "<<act.size()<<endl;
		struct state tmp=q.front();
		struct action ac=act.front();
		q.pop();
		act.pop();
		

		//output_data(tmp,ac);
		if(is_goal_state(tmp)==1)
		{
			output_data_1(ac,10000);
			output_data_2(tmp,10000);

			vector <action> ans;
			//list_ac.pop();
			ans=list_ac.front();

			cout<<"****-----LIST OF ACTION that is ans ---****"<<endl;
			cout<<"Size_ans= "<<ans.size();

			for(int i=0;i<ans.size();i++)
			{
				output_data_1(ans[i],101010);
			}
			return;
		}
		get_action(tmp,1);
	}
		
}


void A_star(state st)
{

	get_action(st,0);
	while(!pact.empty())
	{
		pair <state,int> tmp=pq.front();
		pair <action,int> ac=pact.front();
		pq.pop();
		pact.pop();
		

		//output_data(tmp,ac);
		if(is_goal_state(tmp.first)==1)
		{
			output_data_1(ac.first,10000);
			output_data_2(tmp.first,10000);

			pair <vector <action>,int> ans;
			//list_ac.pop();
			ans=list_ac.front();

			cout<<"****-----LIST OF ACTION that is ans ---****"<<endl;
			cout<<"Size_ans= "<<ans.first.size();

			for(int i=0;i<ans.first.size();i++)
			{
				output_data_1(ans.first[i],101010);
			}
			return;
		}
		get_action(tmp,1);
	}
	
}



int main(int argc, char *argv[])
{
	char *file=argv[1];
	fstream fin ;
	fin.open(file);
	int num;
	char task;
	fin>>num;
	//cout<<"number of block "<<num<<endl;
	char ch;
	fin>>ch;
	task=ch;
	//cout<<ch<<endl;
	string temp;
	fin>>temp;
	//cout<<temp<<endl;
	inital_state.hold=0;
	goal_state.hold=0;
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
		//cout<<temp<<endl;
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

	if(task=='f')
	{
	BFS(inital_state);
	}
	else if (task=='a')
	{
		A_star(inital_state);
	}

	return 0;
}
