#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include <vector>
#include <cassert>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <queue>
#pragma warning(disable : 4200)
#pragma warning( disable: 6386)
#pragma warning(disable: 6294)
using namespace std;

vector<string> colour; //contain the color of the vertices
vector<int> d; // contain the distance of the vertices
vector<int> p; // contain the parents of the vertices

double random(double p) // pick a number depend on the probabilty and 
{                       // as a result returning the probability or 1-probability
	int k = p * 10000, Result = 0;
	int upper = 10000, lower = 1, result = 0;
	Result = (rand() % (upper - lower + 1)) + lower;
	if (Result <= k)
	{
		return p;
	}
	
	else return 1 - p;
}

vector <vector<int >> build_random_graph(int v, double p) // function to build a graph
{
	int i = 0, j = 0;
	double result = 0;
	vector <vector<int>> Main_vector(v); // vector of vetor that will contain 
										 // sub vectors = future edges
	for (i = 1; i < v; i++)
	{
		for (j = i + 1; j <= v; j++)
		{
			result = random(p); // calling the random function
			if (result == p && i != j)
			{
				Main_vector[i - 1].push_back(j); // insert vertice into aspesific loaction (-another vertic)
				Main_vector[j - 1].push_back(i); //make them "nieghbors"
			}
		}
	}
	return Main_vector;
}

void BFS_Source(vector <vector<int> > graphX, int s)
{
	// creating Queue 
	queue<int> q;

	// Pushing the node to the queue
	q.push(s);

	d[s] = 0;
	colour[s] = "green"; // changing the color to green = in process


	while (!q.empty())
	{

		int u = q.front();
		q.pop();

		for (auto i = graphX[u].begin(); i != graphX[u].end(); i++)
		{
			if (colour[*i - 1] == "white") // going to the pointer 
			{
				colour[*i - 1] = "green";
				d[*i - 1] = d[u] + 1;
				p[*i - 1] = u;


				q.push(*i - 1);
			}
		}

		colour[u] = "dark_green"; // changing the color of the node = were done running on it
	}
}

std::vector<int> BFSFull(vector <vector<int> > graphX) // BFS function
{
	colour.assign(graphX.size(), "white");
	d.assign(graphX.size(), 0);   // 0 untill we assain a different disstance by using the BFS_Source functiion 
	p.assign(graphX.size(), -1); // (-1) untill we assain his parent in the BFS_Source() function 


	for (int i = 0; i < graphX.size(); i++)
	{
		if (colour[i] == "white")
			BFS_Source(graphX, i);   // Calling to the BFSSingleSource function for all the white vertices
	}
	return d; // returning the distance vector
}

int diameter(vector<vector<int> > graphX) // This function returning the diameter
{
	vector <int> distance = BFSFull(graphX); // calling BFS
	int Max = 0;
	for (int i = 0; i < distance.size(); i++)
	{
		if (Max < distance[i])
		{
			Max = distance[i]; // checkig what is the maximum distance
		}
	}
	distance.clear();
	assert(distance.empty());
	return Max;     // return the diameter
}

int connectivity(vector<vector<int> > graphX) // This function checks if the graph is connected
{
	vector <int> connect = BFSFull(graphX); // calling the BFS function
	int counter = 0;
	for (int i = 0; i < connect.size(); i++)
	{
		if (connect[i] == 0)
			counter++;           // counting how many connected components have in the graph
		if (counter > 1)     // if theres more than 1 - the graph is not connected
		{
			connect.clear();
			assert(connect.empty());
			return 0;
		}
	}
	return 1; // 1 = connectrd
}

int Is_Isolated(vector<vector<int> > graphX) // The function checks if theres any isolated vertices
{
	for (int i = 0; i < graphX.size(); i++)
	{
		if (graphX[i].size() == 0)
		{
			return 1;  // 1 if isolated 
		}
	}
	return 0;    // 0 otherwise
}

// The function write to the file 
bool write_record_to_file(std::string file_name, std::string title, std::double_t field_1, std::double_t field_2, std::double_t field_3, std::double_t field_4, std::double_t field_5, std::double_t field_6, std::double_t field_7, std::double_t field_8, std::double_t field_9, std::double_t field_10)
{
	std::ofstream file;
	file.open(file_name, std::ios_base::app);
	file << title << ", " << field_1 << ", " << field_2 << ", " << field_3 <<
		", " << field_4 << ", " << field_5 << ", " << field_6 <<
		", " << field_7 << ", " << field_8 << ", " << field_9 << ", "
		<< field_10 << endl;
	file.close();
	return true;
}

int main()  // 1_3= 0.0069  2= 0.117
{
	int i = 0, j = 0, v = 1000, graphDiam, No_neighbor, Connected;
	double p = 0;
	double counterArray_diameter[10], counterArray2_diameter[10], counter_diameter2 = 0;
	double counter_diameter_bigger_2 = 0, counter_isolated = 0;
	double counterArray_isolated[10], counter_connectivity = 0, counterArray_connectivity[10];
	double counterArray_diameter_INF[10], counter_diameter_INF = 0;
	double counterArray1_diameter[10], counter_diameter1 = 0;
	double threshold1[10];  //0.006
	threshold1[0] = 0.001;
	threshold1[1] = 0.003;
	threshold1[2] = 0.004;
	threshold1[3] = 0.005;
	threshold1[4] = 0.0064;
	threshold1[5] = 0.0076;
	threshold1[6] = 0.008;
	threshold1[7] = 0.01;
	threshold1[8] = 0.03;
	threshold1[9] = 0.06;
	double threshold2[10]; //0.1175
	threshold2[0] = 0.06;
	threshold2[1] = 0.07;
	threshold2[2] = 0.085;
	threshold2[3] = 0.112;
	threshold2[4] = 0.115;
	threshold2[5] = 0.118;
	threshold2[6] = 0.119;
	threshold2[7] = 0.12;
	threshold2[8] = 0.125;
	threshold2[9] = 0.13;
	double threshold3[10];  //0.006
	threshold3[0] = 0.0015;
	threshold3[1] = 0.003;
	threshold3[2] = 0.0042;
	threshold3[3] = 0.0051;
	threshold3[4] = 0.0064;
	threshold3[5] = 0.0076;
	threshold3[6] = 0.0083;
	threshold3[7] = 0.01;
	threshold3[8] = 0.03;
	threshold3[9] = 0.06;
	for (int k = 0; k < 3; k++)
	{
		if (k == 0) //diameter
		{
			bool write_to_file1 = write_record_to_file("diameter.csv", "trheshold_2[]", threshold2[0],
				threshold2[1], threshold2[2], threshold2[3], threshold2[4], threshold2[5],
				threshold2[6], threshold2[7], threshold2[8], threshold2[9]);
		}
		
		if (k == 1) // connctivity
		{
			bool write_to_file2 = write_record_to_file("Is_connectivity.csv", "threshold_1[]", threshold1[0],
				threshold1[1], threshold1[2], threshold1[3], threshold1[4], threshold1[5],
				threshold1[6], threshold1[7], threshold1[8], threshold1[9]);
		}
		
		if (k == 2) //isolated 
		{
			bool write_to_file3 = write_record_to_file("Is_isolated.csv", "threshold_3[]", threshold3[0],
				threshold3[1], threshold3[2], threshold3[3], threshold3[4], threshold3[5],
				threshold3[6], threshold3[7], threshold3[8], threshold3[9]);
		}
		
		for (i = 0; i < 10; i++)
		{
			if (k == 0)
				p = threshold2[i];
			if (k == 1)
				p = threshold1[i];
			if (k == 2)
				p = threshold3[i];
			for (j = 1; j < 501; j++)
			{
				srand(time(NULL));
				std::vector<std::vector<int>> graphX(v);
				graphX = build_random_graph(v, p);
				if (k == 0)
				{
					graphDiam = diameter(graphX);
					if (graphDiam == 2)
						counter_diameter2++;
					if (graphDiam > 2)
						counter_diameter_bigger_2++;
					if (graphDiam == 1)
						counter_diameter1++;
					if (graphDiam == 0)
						counter_diameter_INF++;

				}
				if (k == 1)
				{
					Connected = connectivity(graphX);
					if (Connected == 1)
						counter_connectivity++;
				}
				if (k == 2)
				{
					No_neighbor = Is_Isolated(graphX);
					if (No_neighbor == 1)
					{
						counter_isolated++;
					}
				}
				graphX.clear();
				assert(graphX.empty());
			}
			if (k == 0)
			{
				cout << i << "->" << counter_diameter2 << endl;
				counterArray_diameter[i] = counter_diameter2 / 500;
				counterArray2_diameter[i] = counter_diameter_bigger_2 / 500;
				counterArray1_diameter[i] = counter_diameter1 / 500;
				counterArray_diameter_INF[i] = counter_diameter_INF / 500;
				counter_diameter2 = 0;
				counter_diameter_bigger_2 = 0;
				counter_diameter1 = 0;
				counter_diameter_INF = 0;

			}
			
			if (k == 1)
			{
				cout << i << " connectivity ->" << counter_connectivity << endl;
				counterArray_connectivity[i] = counter_connectivity / 500;
				counter_connectivity = 0;
			}
			
			if (k == 2)
			{
				cout << i << " isolated ->" << counter_isolated << endl;
				counterArray_isolated[i] = counter_isolated / 500;
				counter_isolated = 0;
			}
		}
		
		if (k == 0)
		{
			bool write_to_file1 = write_record_to_file("diameter.csv", "diameter = 2", counterArray2_diameter[0],
				counterArray_diameter[1], counterArray_diameter[2],
				counterArray_diameter[3], counterArray_diameter[4],
				counterArray_diameter[5], counterArray_diameter[6],
				counterArray_diameter[7], counterArray_diameter[8],
				counterArray_diameter[9]);
			write_to_file1 = write_record_to_file("diameter.csv", "diameter > 2", counterArray2_diameter[0],
				counterArray2_diameter[1], counterArray2_diameter[2],
				counterArray2_diameter[3], counterArray2_diameter[4],
				counterArray2_diameter[5], counterArray2_diameter[6],
				counterArray2_diameter[7], counterArray2_diameter[8],
				counterArray2_diameter[9]);
			write_to_file1 = write_record_to_file("diameter.csv", "diameter = 1", counterArray1_diameter[0],
				counterArray1_diameter[1], counterArray1_diameter[2],
				counterArray1_diameter[3], counterArray1_diameter[4],
				counterArray1_diameter[5], counterArray1_diameter[6],
				counterArray1_diameter[7], counterArray1_diameter[8],
				counterArray1_diameter[9]);
			write_to_file1 = write_record_to_file("diameter.csv", "diameter = INF ", counterArray_diameter_INF[0],
				counterArray_diameter_INF[1], counterArray_diameter_INF[2],
				counterArray_diameter_INF[3], counterArray_diameter_INF[4],
				counterArray_diameter_INF[5], counterArray_diameter_INF[6],
				counterArray_diameter_INF[7], counterArray_diameter_INF[8],
				counterArray_diameter_INF[9]);
		}
		
		if (k == 1)
		{
			bool write_to_file2 = write_record_to_file("Is_connectivity.csv", "connectivity ", counterArray_connectivity[0],
				counterArray_connectivity[1], counterArray_connectivity[2],
				counterArray_connectivity[3], counterArray_connectivity[4],
				counterArray_connectivity[5], counterArray_connectivity[6],
				counterArray_connectivity[7], counterArray_connectivity[8],
				counterArray_connectivity[9]);
		}
		
		if (k == 2)
		{
			bool write_to_file3 = write_record_to_file("Is_isolated.csv", "isolated ", counterArray_isolated[0],
				counterArray_isolated[1], counterArray_isolated[2],
				counterArray_isolated[3], counterArray_isolated[4],
				counterArray_isolated[5], counterArray_isolated[6],
				counterArray_isolated[7], counterArray_isolated[8],
				counterArray_isolated[9]);
		}
	}
}