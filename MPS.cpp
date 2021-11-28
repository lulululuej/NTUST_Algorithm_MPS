#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include<vector>
#include<algorithm>

using namespace std;

vector < vector<int> > chord;
vector < vector<int> > Case;

//Sorting the first endpoint
bool sortrow( const vector<int>& v1, const vector<int>& v2){
    return v1[0] < v2[0];
}

int x=0;
void findChord(int i,int j,int *endpointOf){
	int k;
	while(j-i>1){
		//case2
		if(Case[i][j]==2){
			k=endpointOf[j];
			chord[x][0]=k;
			chord[x][1]=j;
			//cout << chord[x][0] << ' ' << chord[x][1] << endl;
			x++;
			findChord(k,j-1,endpointOf);
			j=k-1;
		}
		//case3
		else if(Case[i][j]==3){
			k=endpointOf[j];
			chord[x][0]=k;
			chord[x][1]=j;
			//cout << chord[x][0] << ' ' << chord[x][1] << endl;
			x++;
			findChord(i+1,j-1,endpointOf);
			j=i-1;
		}
		else{
			j--;
		}
	}
}

int main(int argc, char **argv)
{ 
	vector < vector<int> > sleep;
	sleep.resize(1000);
	for(int i=0; i < 1000; ++i)
	{
		sleep[i].resize(1000);
	} 
		
    if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
    //    system("pause");
        exit(1);
    }

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in); 
    if(!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    // parse the input file
    cout << "======================" << endl;
    cout << "        Parser        " << endl;
    cout << "======================" << endl;

    char buffer[100];

    fin >> buffer;
    int numChord = atoi(buffer);

    cout << "#Chords:" << numChord << endl;
    int endpointOf[numChord]; //記錄每個點的對面的點是誰

    for(int i = 0; i < numChord / 2; ++i)
    {
    	fin >> buffer;
    	int point1 = atoi(buffer);
    	fin >> buffer;
    	int point2 = atoi(buffer);
    	cout << "Chord(" << point1 << "," << point2 << ")" << endl;
        
        endpointOf[point1] = point2;
        endpointOf[point2] = point1;
        //cout << "point1:" << endpointOf[point2] << " point2:" << endpointOf[point1] <<endl;
    }

    vector < vector<int> > mps;
    mps.resize(numChord);
    Case.resize(numChord);
	
	for(int i=0; i < numChord; ++i){
        mps[i].resize(numChord);
		Case[i].resize(numChord);
	} 

    for(int i = 0; i < numChord; i++){
        for(int j = 0 ; j < numChord; j++){
            if (i == j){
                mps[i][j] = 0 ;
                //cout << "index" << i << j << "=" << mps[i][j] << endl;
            }
        }
    }

    for(int diff = 1; diff < numChord; diff++){
        int i = 0;
        int j = i + diff;
        while (j != numChord)
        {
            int k = endpointOf[j];
            if (k < i || k > j){
                mps[i][j] = mps[i][j-1];
            }
            else if (k > i && k < j){
                if(mps[i][j-1] >= mps[i][k-1]+1+mps[k+1][j-1]){
                    mps[i][j] = mps[i][j-1];
                }
                else{
                    mps[i][j] = mps[i][k-1] + 1 + mps[k+1][j-1];
                    Case[i][j] = 2;
                }
            }
            else if (k == i){
                Case[i][j] = 3;
                if(diff == 1){
                    mps[i][j] = 1;
                }
                else{
                    mps[i][j] = mps[i+1][j-1] + 1;
                }
            }
            i++;
            j++;
        }
    }

    cout << "max planer set :" << mps[0][numChord-1] << endl;
    chord.resize(mps[0][numChord-1]);
	for(int i = 0; i < mps[0][numChord-1]; i++){
		chord[i].resize(2);
	} 
		
	findChord(0, numChord-1, endpointOf);

    sort(chord.begin(), chord.end(), sortrow);

    //cout << "After Sorting :" << endl;
    //for(int i = 0; i < mps[0][numChord-1]; i++){
    //    for(int j = 0; j < 2; j++){
    //        cout << chord[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    // open the output file
    fstream fout;
    fout.open(argv[2],fstream::out);
    if(!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
	    exit(1);
    }

    // output something to the output file
    fout << mps[0][numChord-1] << endl;
    for(int i = 0; i < mps[0][numChord-1] ; i++){
		for(int j = 0; j < 2; j++){
			fout << chord[i][j] << " ";
		}
		fout << endl;
	}
    //system("pause");
    return 0;
}

