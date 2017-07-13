#include<iostream>
#include"converter.h"
#include"dataReader.h"


int main ( )
{
	



	

	for ( int i = 1; i <= 45; ++i ) // For all origianl instances
	{

		for ( int costStructure = 0; costStructure <= 2; ++costStructure )
		{

			// Specify the input file path
			std::string inputFile = "./cflp/" + std::to_string(i) + "_" + std::to_string(costStructure) +"_out";

			std::cout << "Inputfile : " << inputFile << std::endl;

			dataReader datRead = dataReader ( );

			datRead.setInputFile ( inputFile );

			datRead.Run ( );


			// Conversion starts here!

			converter conv = converter ( );

			std::string placeHolder;

			conv.setVersion ( "1.0" );

			placeHolder = "Gadegaard16_CFLP_Klose_p";
			if ( i < 10 )
			{
				placeHolder += std::to_string ( 0 ) + std::to_string ( i ) + "_" + std::to_string ( costStructure ) + ".raw";
			}
			else
			{
				placeHolder += std::to_string ( i ) + "_" + std::to_string ( costStructure );
			}



			conv.setInstanceName ( placeHolder );

			
			
			conv.setContributionName ( "Gadegaard16" );


			
			conv.setObjectives ( 2 );


			
			
			std::vector<std::string> types = { "float","int" };
			conv.setObjectiveTypes ( types );


			
			
			std::vector<std::string> directions = { "min","min" };
			conv.setDirections ( directions );



			conv.setOptimal ( true );


			
			conv.setCardinality ( datRead.getFrontSize ( ) );



			std::vector<std::vector<double>> points = datRead.getPoints ( );


			
			
			std::vector<std::string> pointTypes;

			for ( auto it = datRead.points.begin ( ); it != datRead.points.end ( ); ++it )
			{
				pointTypes.push_back ( "null" );
			}
			conv.setPoints ( points, pointTypes );



			conv.setValidity ( true );



			std::string comment = "Results from the paper \'A bi-objective approach to discrete cost-bottleneck location problems\' by Gadegaard, Klose, Nielsen, Annals of Operations Research, 2016.";
			conv.setComments ( comment );



			std::string machineSpecs ( "Intel Core i7-4785T 2.2 GHz, 16 GB RAM, Linux Ubuntu 64bit" );
			conv.setCPU ( datRead.getExecutionTime ( ), machineSpecs );

			std::string outputFile = "./Results/CFLP/Gadegaard16_UFLP_Klose_p";
			if ( i < 10 )
			{
				outputFile += "0" + std::to_string ( i ) + "_" + std::to_string ( costStructure ) + "_result.json";
			}
			else
			{
				outputFile += std::to_string ( i ) + "_" + std::to_string ( costStructure ) + "_result.json";
			}
			conv.createResultsFile ( outputFile );

		}
	}
	return 0;
}