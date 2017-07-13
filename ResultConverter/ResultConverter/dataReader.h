#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include<vector>
#include<sstream>


class  dataReader
{
private:
	std::ifstream inStream;

	int frontSize;
	double cpuTime;
	


	void ReadData ( );


public:
	dataReader ( );
	

	void setInputFile ( std::string& inputFile ) 
	{
		inStream.open ( inputFile );
		if ( !inStream ) throw std::runtime_error ( "Could not open the input file. The process is terminated" );
	}

	void Run ( ) { ReadData ( ); }


	double getExecutionTime ( ) { return cpuTime; }
	int getFrontSize ( ) { return frontSize; }
	std::vector<std::vector<double>> getPoints ( ) { return points; }


	std::vector<std::vector<double>> points;
};