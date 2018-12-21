#include<iostream>
#include<fstream>
using namespace std;

int main(){
	FILE *pFile = fopen("Sample_temp.txt", "w");
	for(int i=0; i<876; i++){
		fprintf(pFile, "%d qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVB\n", i);
	}
	fprintf(pFile, "qwertyuistr_cli: server terminated prematurely\n");
	fclose(pFile);
}
