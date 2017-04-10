#include <bits/stdc++.h>

using namespace std;

struct state
{

	vector <int> clear;
	vector <int> on_table;
	vector < pair<int,int> > on_top;
	int hold=0;
}inital_state,goal_state;



struct action
{
	int type;
	int num1;
	int num2;
};
int number_block;

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

	if(st.hold!=goal_state.hold )
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

/************************** GOAL STACK PLANING STARTS HERE ***************************/

/***********node type ******************/

/** 1 == conjunct ***/
/*** 2 == action ****/
/**** 3 == predicate ****/



/***************************************/



struct node 
{
	int type ;
	action a;
	state s;
	int id;

};


stack <node> stk;

state current_state ;

queue <action> answer;

void add_on_stack(state st)
{
	//cout<<"Tolaniht "<<endl;
	for(int i=0;i<st.on_table.size();i++)
	{
		node temp;
		temp.type=3;
		//temp.s.hold=0;
		temp.s.on_table.push_back(st.on_table[i]);
		temp.id=1;
		stk.push(temp);
	}

	for(int i=st.on_top.size()-1;i>=0;i--)
	{
		node temp;
		temp.type=3;
		//temp.s.hold=0;
		temp.s.on_top.push_back(st.on_top[i]);
		temp.id=1;
		stk.push(temp);
	}

	for(int i=0;i<st.clear.size();i++)
	{
		node temp;
		temp.type=3;
		//temp.s.hold=0;
		temp.s.clear.push_back(st.clear[i]);
		temp.id=1;
		stk.push(temp);
	}

	if(st.hold >=0 && st.hold<=number_block)
	{
	node temp;
	temp.s.hold=st.hold;
	temp.type=3;
	temp.id=1;
	stk.push(temp);
	}

}

int  is_subgoal_state(state st,state subgoal)
{
	for(int i=0;i<subgoal.clear.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.clear.size();j++)
		{
			if(subgoal.clear[i]==st.clear[j])
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

	for(int i=0;i<subgoal.on_top.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.on_top.size();j++)
		{
			if(subgoal.on_top[i]==st.on_top[j])
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

	for(int i=0;i<subgoal.on_table.size();i++)
	{
		int flag=0;
		for(int j=0;j<st.on_table.size();j++)
		{
			if(subgoal.on_table[i]==st.on_table[j])
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

	if(st.hold!=subgoal.hold && subgoal.hold!=0)
	{
		return 0;
	}

	return 1;

}


void goal_effect_action_4(int num1,int num2)
{
	struct state cpy;
	cpy.hold=0;
	for(int i=0;i<current_state.clear.size();i++)
	{
		if(current_state.clear[i]==num2)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(current_state.clear[i]);
		}
	}

	cpy.clear.push_back(num1);

	for(int i=0;i<current_state.on_table.size();i++)
	{
		cpy.on_table.push_back(current_state.on_table[i]);
	}

	for(int i=0;i<current_state.on_top.size();i++)
	{
		cpy.on_top.push_back(current_state.on_top[i]);
	}
	cpy.on_top.push_back(make_pair(num1,num2));

	current_state=cpy;
	//output_data_2(cpy,4);
	//q.push(cpy);
}
void goal_effect_action_1(int num)
{
	struct state cpy;
	cpy.hold=num;
	for(int i=0;i<current_state.clear.size();i++)
	{
		if(current_state.clear[i]==num)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(current_state.clear[i]);
		}
	}

	for(int i=0;i<current_state.on_table.size();i++)
	{
		if(current_state.on_table[i]!=num)
		cpy.on_table.push_back(current_state.on_table[i]);
	}

	for(int i=0;i<current_state.on_top.size();i++)
	{
		if(current_state.on_top[i].first!=num)
		cpy.on_top.push_back(current_state.on_top[i]);
	}
	//output_data_2(cpy,1);
	current_state=cpy;
}

void goal_effect_action_2(int num1, int num2)
{
	struct state cpy;
	cpy.hold=num1;
	for(int i=0;i<current_state.clear.size();i++)
	{
		if(current_state.clear[i]==num1)
		{
			continue;
		}
		else
		{
			cpy.clear.push_back(current_state.clear[i]);
		}
	}

	cpy.clear.push_back(num2);

	for(int i=0;i<current_state.on_table.size();i++)
	{
		cpy.on_table.push_back(current_state.on_table[i]);
	}

		for(int i=0;i<current_state.on_top.size();i++)
	{
		if(current_state.on_top[i]!=make_pair(num1,num2))
		cpy.on_top.push_back(current_state.on_top[i]);
	}

	//output_data_2(cpy,2);
	current_state=cpy;


}

void goal_effect_action_3(int num)
{
	struct state cpy;
	cpy.hold=0;

	for(int i=0;i<current_state.on_table.size();i++)
	{
		cpy.on_table.push_back(current_state.on_table[i]);
	}

	cpy.on_table.push_back(num);

	for(int i=0;i<current_state.clear.size();i++)
	{
		
			cpy.clear.push_back(current_state.clear[i]);
		
	}

	cpy.clear.push_back(num);

	for(int i=0;i<current_state.on_top.size();i++)
	{
		cpy.on_top.push_back(current_state.on_top[i]);
	}
	//output_data_2(cpy,3);
	current_state=cpy;
}


void apply_action(action a)
{
	answer.push(a);

	if(a.type==1)
	{
		goal_effect_action_1(a.num1);
	}
	else if(a.type==2)
	{
		goal_effect_action_2(a.num1,a.num2);
	}
	else if(a.type==3)
	{
		goal_effect_action_3(a.num1);
	}
	else
	{
		goal_effect_action_4(a.num1,a.num2);
	}

	//output_data_2(current_state,1000);

}

int check_predicate(state st)
{
	for(int i=0;i<st.clear.size();i++)
	{
		for(int j=0;j<current_state.clear.size();j++)
		{
			if(st.clear[i]==current_state.clear[j])
			{
				return 1;
			}
		}
	}

	for(int i=0;i<st.on_table.size();i++)
	{
		for(int j=0;j<current_state.on_table.size();j++)
		{
			if(st.on_table[i]==current_state.on_table[j] )
			{
				return 1;
			}
		}
	}

	for(int i=0;i<st.on_top.size();i++)
	{
		for(int j=0;j<current_state.on_top.size();j++)
		{

			if(st.on_top[i]==current_state.on_top[j] )
			{
				//out<<current_state.on_top[j].first<<" H "<<current_state.on_top[j].second<<endl;
				return 1;
			}
		}
	}



	if(st.clear.size()==0 && st.on_top.size()==0 && st.on_table.size()==0 && st.hold==current_state.hold)
	{
		return 1;
	}

	


	return 0;

}





void Goal_stack()
{
	while(!stk.empty())
	{
		node p=stk.top();
		//if(is_subgoal_state(goal_state,current_state)==1)
			//break;
		
		/*if(p.id==1)
		{
			output_data_2(p.s,20);

		}
		else if(p.id==0)
		{
			output_data_1(p.a,10);
		}*/
		//cout<<"Type = "<<p.type<<endl;
		if(p.type==1)
		{
			int k=is_subgoal_state(current_state,p.s);
			//output_data_2(current_state,420);
			//output_data_2(p.s,520);
			if(k==1 && p.s.hold==0 && current_state.hold>0 && current_state.hold<=number_block )
			{
				k=0;
			}

			if(k==0)
			{
				//cout<<"himanshu"<<endl;
				//cout<<p.type<<endl;
				add_on_stack(p.s);

			}
			else if (k==1)
			{
				//cout<<"Subgoal done"<<endl;
				stk.pop();
			}
		}
		else if(p.type==2)
		{
			apply_action(p.a);
			stk.pop();
		}
		else if(p.type==3)
		{
			int k=check_predicate(p.s);

			if(k==1)
			{
				//cout<<"Done"<<endl;
				stk.pop();
			}
			else if(k==0)
			{
				//cout<<"Remaining"<<endl;
				//output_data_2(current_state,50);
				stk.pop();
				add_on_stack(p.s);
		
				if(p.s.on_table.size()==1)
				{
					node temp;
					temp.a.type=3;
					temp.a.num1=p.s.on_table[0];
					temp.type=2;
					stk.push(temp);
					temp.id=0;
					int num=p.s.on_table[0];

					node temp1;
					temp1.type=1;
					temp1.s.hold=num;
					temp1.id=1;
					stk.push(temp1);
				}

				else if(p.s.hold>0 && p.s.hold<=number_block)
				{
					node temp;
					int num=p.s.hold;
					int flag=0;
					for(int i=0;i<current_state.on_table.size();i++)
					{
						if(num==current_state.on_table[i])
						{
							flag=1;
							break;
						}
					}

					if(flag==1)
					{
						temp.a.type=1;
						temp.a.num1=num;
						temp.a.num2=0;
						temp.type=2;
						temp.id=0;
						stk.push(temp);

						node temp1;
						temp1.type=1;
						temp1.s.hold=0;
						temp1.id=1;
						temp1.s.clear.push_back(num);
						temp1.s.on_table.push_back(num);
						stk.push(temp1);

					}

					else
					{
						temp.a.type=2;
						temp.a.num1=num;
						temp.type=2;
						int n;
						for(int i=0;i<current_state.on_top.size();i++)
						{
							if(current_state.on_top[i].first==num)
							{
								n=current_state.on_top[i].second;
							}
						}
						temp.a.num2=n;
						temp.id=0;
						stk.push(temp);

						node temp1;
						temp1.type=1;
						temp1.s.clear.push_back(num);
						temp1.s.hold=0;
						temp1.id=1;
						temp1.s.on_top.push_back(make_pair(num,n));
						stk.push(temp1);
						

					}



				}

				else if(p.s.clear.size()==1)
				{
					node temp;
					temp.a.type=2;
					temp.type=2;
					int num=p.s.clear[0];
					int n;
					for(int i=0;i<current_state.on_top.size();i++)
					{
						if(current_state.on_top[i].second==num)
						{
							n=current_state.on_top[i].first;
							break;
						}
					}
					temp.a.num1=n;
					temp.a.num2=num;
					temp.id=0;
					stk.push(temp);


					node temp1;
					temp1.type=1;
					temp1.id=1;
					temp1.s.clear.push_back(n);
					temp1.s.on_top.push_back(make_pair(n,num));
					temp1.s.hold=0;
					stk.push(temp1);


				}

				else if(p.s.on_top.size()==1)
				{
					node temp;
					temp.a.type=4;
					temp.type=2;
					pair <int,int> num=p.s.on_top[0];
					temp.a.num1=num.first;
					temp.a.num2=num.second;
					temp.id=0;
					stk.push(temp);

					node temp1;
					temp1.type=1;
					temp1.s.clear.push_back(num.second);
					temp1.s.hold=num.first;
					temp1.id=1;
					stk.push(temp1);

				}

				else if(p.s.hold==0)
				{
					node temp;
					temp.a.type =3;
					temp.type=2;
					temp.a.num2=0;
					temp.a.num1=current_state.hold;
					temp.id=0;
					stk.push(temp);

				}


			
			
		}

		//stk.pop();
	}


	}//end of while

	cout<<"No of Actions  =  "<<answer.size()<<endl;
	while(!answer.empty())
	{
		action a=answer.front();
		answer.pop();
		display(a);
	}
}









/************* MAIN FUCNTION ***************************************************/



int main(int argc, char *argv[])
{
	char *file=argv[1];
	fstream fin ;
	fin.open(file);
	
	char task;
	fin>>number_block;
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
	else if(task=='g')
	{
		node temp;
		temp.type=1;
		temp.id=1;
		temp.s=goal_state;
		stk.push(temp);
		current_state=inital_state;
		

		Goal_stack();
	}

	return 0;
}
