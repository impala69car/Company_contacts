#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <set>
using namespace std;
typedef map<string,string> data_map;
struct earlier:binary_function<string,string, bool>
{
	bool operator()(const string& name1, const string name2) const {
		return dates[name1]<dates[name2];
	}
	static data_map dates;
	static data_map places;
};
data_map earlier::dates;
data_map earlier::places;

typedef multiset<string,earlier> date_ordered_mset;
typedef map<string, date_ordered_mset> relation_map;
void output_tree(const string& name,relation_map& personal,data_map& places,data_map& dates, int indentation_level=0)
{
	for(int k=0; k!=indentation_level;++k)
	{
		cout<<" ";
	}
	cout<< name << " ("<<places[name]<< " " << dates[name] << ")" <<endl;
	date_ordered_mset L=personal[name];
	date_ordered_mset::const_iterator j;
	for(j=L.begin();j!=L.end(); ++j)
	{
		output_tree(*j,personal,places,dates,indentation_level+1);
	}
}
void get_chunck(istream& in, string& s,char terminator = '\t')
{
	s.erase(s.begin(),s.end());
	s.reserve(20);
	string::value_type ch;
	while (in.get(ch)&& ch!=terminator)
	{
		s.insert(s.end(),ch);
	}
}
int main()
{
	string file_name;
	file_name = "contacts.txt";
	ofstream fout(file_name);
	fout<<"Brain Kernighan (USA 1969)"<<endl;
	fout<<"	Monsanta( )"<<endl;
	fout<<"		bioingener ( )"<<endl;
	fout<<"Sam Kernighan (USA 1975)"<<endl;
	fout<<"	Monsanta( )"<<endl;
	fout<<"		ingener ( )"<<endl;
	fout<<"Bob Kronn (USA 1960)"<<endl;
	fout<<"	FreshBody( )"<<endl;
	fout<<"		salor ( )"<<endl;
	fout<<"Peter Parker (USA 1960)"<<endl;
	fout<<"	Avengers( )"<<endl;
	fout<<"		spiderman ( )"<<endl;
	fout.close();
	cout<<"Brain Kernighan (USA 1969)"<<endl;
	cout<<"	Monsanta( )"<<endl;
	cout<<"		bioingener ( )"<<endl;
	cout<<"Sam Kernighan (USA 1975)"<<endl;
	cout<<"	Monsanta( )"<<endl;
	cout<<"		ingener ( )"<<endl;
	cout<<"Bob Kronn (USA 1960)"<<endl;
	cout<<"	FreshBody( )"<<endl;
	cout<<"		salor ( )"<<endl;
	cout<<"Peter Parker (USA 1960)"<<endl;
	cout<<"	Avengers( )"<<endl;
	cout<<"		spiderman ( )"<<endl;
	ifstream ifs(file_name.c_str());
	if(!ifs.is_open())
	{
		cout<<"Not open!"<<endl;
		exit(1);
	}
	relation_map companys,personal;
	string name, company,job,place,date;
	while (true)
	{
		if(ifs.peek()=='#')
		{
			get_chunck(ifs,name,'\n');
			continue;
		}
		get_chunck(ifs,name);
		if(!ifs) break;
		get_chunck(ifs,company);
		get_chunck(ifs,job);
		get_chunck(ifs,place);
		get_chunck(ifs, date, '\n');
		earlier::places[name] = place;
		earlier::dates[name] = date;
		if(company=="?")
		{
			company="---";
		}
		personal[company].insert(name);
		companys[name].insert(company);
	}
	date_ordered_mset& roots = personal["---"];
	date_ordered_mset& roots2 = personal["---"];
	relation_map::iterator i;
	date_ordered_mset::iterator j;
	bool any_company;
	cout<<"Vvedite nomer zaprosa"<<endl;
	int num;
	cin>>num;
	if(num==1)
	{
	}
	else if(num==2)
	{
		for(i = companys.begin();i!=companys.end();++i)
		{
			any_company=false;
			for(j=i->second.begin();j!=i->second.end();++j)
			{
				if(*j==string("---") || companys.find(*j)!=companys.end())
				{
					any_company=true;
				}
			}
			if(any_company)
			{
				string first_company = *i->second.begin();
				if(find(roots.begin(),roots.end(),first_company)==roots.end())
				{
					roots.insert(first_company);
				}
			}
		}
		for(j=roots.begin();j!=roots.end();++j)
		{
			output_tree(*j,personal,earlier::places,earlier::dates);
		}
	}
	return 0;
}