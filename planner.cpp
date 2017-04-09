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


struct compare1  
 {  
 bool operator()(pair <state,int> l, pair <state,int> r)  
  {  
   return l.second >= r.second;
   }  
 };


 struct compare2  
 {  
 bool operator()(pair <action,int> l, pair <action,int> r)  
  {  
   return l.second >= r.second;
   }  
 };


 struct compare3  
 {  
 bool operator()(pair <vector <action>,int > l, pair <vector <action>,int > r)  
  {  
   return l.second >= r.second;
   }  
 };
queue <state> q;
queue <action> act;
queue <vector <action> > list_ac;

priority_queue <pair <state,int> ,vector <pair <state,int> >, compare1 > pq;
priority_queue < pair <action,int> ,vector <pair <action,int> > ,compare2 > pact;
priority_queue < pair <vector <action>,int >, vector <pair <vector <action>,int > >,compare3 > p_list_ac;
int counter_numb=0;
int count_index=0;
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

void display (action p)
{
	if(p.type==1)
	{
		cout<<"action(pick block "<<p.num1<<" )"<<endl;
	}
	else if(p.type==2)
	{
		cout<<"action(unstack block "<<p.num1 <<" block "<<p.num2<<" )"<<endl;
	}
	else if(p.type==3)
	{
		cout<<"action(release block "<<p.num1<<" )"<<endl;
	}
	else if(p.type==4)
	{
		cout<<"action(stack block "<<p.num1 <<" block "<<p.num2<<" )"<<endl;	
	}
}


int get_heuristics(state st)
{
	int total = 1+goal_state.clear.size()+goal_state.on_table.size()+goal_state.on_top.size();
	//cout<<"Total =" <<total<<endl;
	//output_data_2(st,0);
	for(int i=0;i<st.clear.size();i++)
	{
		for(int j=0;j<goal_state.clear.size();j++)
		{
			if(st.clear[i]==goal_state.clear[j])
			{
				total=total-1;
			}
		}
	}
	//cout<<"CleAR"<<endl;
	for(int i=0;i<st.on_table.size();i++)
	{
		for(int j=0;j<goal_state.on_table.size();j++)
		{
			if(st.on_table[i]==goal_state.on_table[j])
			{
				total=total-1;
			}
		}
	}
	//cout<<"Ontable"<<endl;
	for(int i=0;i<st.on_top.size();i++)
	{
		for(int j=0;j<goal_state.on_top.size();j++)
		{
			if(st.on_top[i]==goal_state.on_top[j])
			{
				total=total-1;
			}
		}
	}
	//cout<<"Top"<<endl;
	if(st.hold==goal_state.hold)
	{
		total--;
	}
	//cout<<total<<" H "<<endl;
		return total;
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

	//cout<<"############################"<<endl;
	while(act.size()>0)
	{
		counter_numb++;
		//cout<<"SIZE= "<<q.size()<<" "<<act.size()<<endl;
		struct state tmp=q.front();
		struct action ac=act.front();
		q.pop();
		act.pop();
		

		//output_data(tmp,ac);
		if(is_goal_state(tmp)==1)
		{
			//output_data_1(ac,10000);
			//output_data_2(tmp,10000);

			vector <action> ans;
			//list_ac.pop();
			ans=list_ac.front();

			//cout<<"****-----LIST OF ACTION that is BFS ans ---****"<<endl;
			cout<<"Size_ans= "<<ans.size()<<endl;

			for(int i=0;i<ans.size();i++)
			{
				//output_data_1(ans[i],101010);
				display(ans[i]);
			}
			cout<<"Number of Nodes Expaned = "<<counter_numb<<endl;
			return;
		}
		get_action(tmp,1);
		//cout<<"##################################"<<endl;
	}

	
		
}



/********** BEGINING OF A STAR SEARCH ***************/
/****************************************************/

int effect_star_action_4(state st,int num1,int num2,int depth)
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
	//q.push(cpy);
	int val=get_heuristics(cpy)+depth;
	//cout<<"HHH VAL == "<<val<<endl;
	pq.push(make_pair(cpy,val));
	return val;
}
int effect_star_action_1(state st,int num,int depth)
{
	struct state cpy;
	cpy.hold=num;
	//cout<//<"Cool"<<endl;
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
	//q.push(cpy);
	//cout<<"Find"<<endl;
	int val=get_heuristics(cpy)+depth;
	//cout<<"HHH VAL == "<<val<<endl;
	pq.push(make_pair(cpy,val));
	return val;
}

int effect_star_action_2(state st, int num1, int num2,int depth)
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
	//q.push(cpy);
	int val=get_heuristics(cpy)+depth;
	//cout<<"HHH VAL == "<<val<<endl;
	pq.push(make_pair(cpy,val));
	return val;


}

int effect_star_action_3(state st,int num,int depth)
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
	//q.push(cpy);
	int val=get_heuristics(cpy)+depth;
	//cout<<"HHH VAL == "<<val<<endl;
	pq.push(make_pair(cpy,val));
	return val;

}

void get_star_action(state st,int index,int depth)
{
	pair <vector <action>,int> ele;
	if(index==1)
	{
		ele=p_list_ac.top();
		p_list_ac.pop();
	}


	if(st.hold!=0)
	{
		//cout<<"Himanshu12"<<endl;
		for(int i=0;i<st.clear.size();i++)
		{
			struct action temp;
			temp.type=4;
			temp.num1=st.hold;
			temp.num2=st.clear[i];
			
			//output_data_1(temp,4);
			int k=effect_star_action_4(st,st.hold,st.clear[i],depth);
			pact.push(make_pair(temp,k));
			if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
			}
			else
			{
				vector <action> v;
				v=ele.first;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
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
		int k=effect_star_action_3(st,temp.num1,depth);
		//output_data_1(temp,3);
		if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
			}
			else
			{
				vector <action> v;
				v=ele.first;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}
		
		//int k=effect_star_action_4(st,st.hold,st.clear[i]);
			pact.push(make_pair(temp,k));
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
					//act.push(temp);
					//output_data_1(temp,1);
					int k=effect_star_action_1(st,st.clear[i],depth);
					//cout<<"Print"<<endl;
					if(index==0)
					{
					vector <action> v;
					v.push_back(temp);
					p_list_ac.push(make_pair(v,k));
					}
					else
					{
					vector <action> v;
					v=ele.first;
					v.push_back(temp);
					p_list_ac.push(make_pair(v,k));
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
					}
					//cout<<"hello"<<endl;
					//int k=effect_star_action_4(st,st.hold,st.clear[i]);
					pact.push(make_pair(temp,k));
				}
			}
		}

		//cout<<"found"<<endl;
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
					//act.push(temp);
					//output_data_1(temp,2);
					int k=effect_star_action_2(st,temp.num1,temp.num2,depth);
					if(index==0)
			{
				vector <action> v;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
			}
			else
			{
				vector <action> v;
				v=ele.first;
				v.push_back(temp);
				p_list_ac.push(make_pair(v,k));
				/*for(int c=0;c<list_ac.front().size();c++)
				{
					cout<<list_ac.front()[c].type<<" | "<<v[c].type<<endl;
				}*/
			}
					
					//int k=effect_star_action_4(st,st.hold,st.clear[i]);
					pact.push(make_pair(temp,k));
				}
			}
		}


	}
}





void A_star(state st)
{
	//cout<<"Himanshu"<<endl;
	get_star_action(st,0,0);
	//cout<<"HIII"<<endl;
	//cout<<"############################"<<endl;
	
	int counter =1;
	while(pact.size()>0 )
	{

		//output_actions(pact);
		counter_numb++;
		pair <state,int> tmp=pq.top();
		pair <action,int> ac=pact.top();
		pq.pop();
		pact.pop();
		
		//cout<<"H vaal = "<< tmp.second<<endl;
		//output_data_1(ac.first,300);
		//output_data_2(tmp.first,300);
		if(is_goal_state(tmp.first)==1)
		{
			output_data_1(ac.first,10000);
			output_data_2(tmp.first,10000);

			pair <vector <action>,int> ans;
			//list_ac.pop();
			ans=p_list_ac.top();

			//cout<<"****-----LIST OF ACTION that is ans ---****"<<endl;
			cout<<"Size_ans= "<<ans.first.size()<<endl;

			for(int i=0;i<ans.first.size();i++)
			{
				//output_data_1(ans.first[i],101010);
				display(ans.first[i]);
			}
			cout<<"Number of Nodes Expaned = "<<counter_numb<<endl;
			return;
		}
		get_star_action(tmp.first,1,counter);
		counter++;

		//cout<<"#################################"<<endl;
		//cout<<"Tolanit"<<endl;
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
