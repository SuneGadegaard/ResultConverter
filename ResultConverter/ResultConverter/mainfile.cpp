#include<iostream>
#include"converter.h"

int main ( )
{
	converter conv = converter ( );

	std::string placeHolder;

	conv.setVersion ( "1.0" );

	placeHolder = "slg";

	conv.setInstanceName ( placeHolder );

	conv.setContributionName ( "Pedersen08" );
	
	conv.setObjectives ( 2 );

	std::vector<std::string> types = { "int","int" };

	conv.setObjectiveTypes ( types );
	
	std::vector<std::string> directions = { "min","min" };

	conv.setDirections ( directions );

	conv.setOptimal ( true );

	conv.setCardinality ( 2 );

	std::vector<std::vector<double>> points = { {1,1},{2,2} };
	std::vector<std::string> pointTypes = { "null" , "null" };
	conv.setPoints ( points, pointTypes );

	conv.createResultsFile ( "./results.dat" );

	conv.setValidity ( true );
	return 0;
}