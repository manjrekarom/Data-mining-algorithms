/*K-means algorithm for 2D data-points using euclidean distances*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

int main()
{
	int n,k,len,index;
	vector< pair<float,float> > dpoints(100);
	vector< pair<float,float> > cpoints(100);
	vector< int > rndGen(100);
	vector< float > dist(100);
	int findC[100],exitCounter=0;
	int cpyFindC[100],cpi[100];
	cout<<"Enter no of data points: ";
	cin>>n;
	cout<<"Enter no. of clusters: ";
	cin>>k;
	cout<<"Enter X and Y co-ordinates for "<<n<<" points: "<<endl;
	for(int i=0; i<n; i++)
	{
		rndGen[i]=i;
		cin>>dpoints[i].first>>dpoints[i].second;
	}
	cout<<endl;

	
	len = n;
	
	//Generate initial random clusters
	for(int i=0; i<k; i++)
	{
		index = rand()%len;
		cpi[i] = rndGen[index];
		cpoints[i].first=dpoints[cpi[i]].first;
		cpoints[i].second=dpoints[cpi[i]].second;
		rndGen.erase(rndGen.begin()+index);
		len--;
	}
	
	cout<<"Initial cluster centres selected randomly:-"<<endl;
	
	for(int i=0; i<k; i++)
	{
		cout<<dpoints[cpi[i]].first<<" "<<dpoints[cpi[i]].second<<endl;
	}
	
	/*Main algorithm
	Keep repeating till clusters don't change anymore
	*/
	while(true)
	{
		for(int i=0; i<n; i++)
		{
			cpyFindC[i]=findC[i];
		}
		
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<k; j++)
			{
				/*Euclidean distance calculation*/
				float x = dpoints[i].first-cpoints[j].first;
				float y = dpoints[i].second-cpoints[j].second;
				float temp = x*x+y*y;
				dist[j]=x*x+y*y;
			}
			
			/*Find which intermediate cluster-point the data-point belongs*/
			int min = *min_element(dist.begin(), dist.begin()+k);
			findC[i]=min_element(dist.begin(), dist.begin()+k) - dist.begin();
		
		}
		
		/*Exit condition*/
		exitCounter=0;
		for(int i=0; i<n; i++)
		{
			if(findC[i]!=cpyFindC[i])
				break;
			exitCounter++;
		}
		if(exitCounter==n)
			break;
			
		/*Calculate new cluster-points*/
		for(int i=0; i<k; i++)
		{
			float avgX=0.0;
			float avgY=0.0;
			int nop=0;
			for(int j=0; j<n; j++)
			{
				if(findC[j]==i)
				{
					avgX=avgX+dpoints[j].first;
					avgY=avgY+dpoints[j].second;
					nop++;
				}	 	 	 
			}
			avgX=avgX/nop;
			avgY=avgY/nop;
			cpoints[i].first=avgX;
			cpoints[i].second=avgY;
		}
	}
	
	cout<<"\nFinal cluster centres:-"<<endl;
	for(int i=0; i<k; i++)
	{
		cout<<cpoints[i].first<<" "<<cpoints[i].second<<endl;
	}
	return 0;
}

/*
Example:-
Enter no of data points: 8
Enter no. of clusters: 3
Enter X and Y co-ordinates for 8 points:
2 10
2 5
8 4
5 8
7 5
6 4
1 2
4 9


Initial cluster centres selected randomly:-
2 5
8 4
1 2

Final cluster centres:-
3.66667 9
7 4.33333
1.5 3.5

Press Enter to return to Quincy....
*/

