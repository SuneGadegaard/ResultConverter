#include"converter.h"

converter::converter ( ):
	version ( "" ),
	instanceName ( "" ),
	contributionName ( "" ),
	objectives ( "" ),
	objectiveType ( "" ),
	direction ( "" ),
	optimal ( "" ),
	cardinality ( "" ),
	points ( "" ),
	valid ( "" ),
	comments ( "" ),
	suppCard ( "" ),
	extCard ( "" ),
	cpu ( "" ),
	machineSpec ( "" ),
	misc ( "" )
{
	try
	{

	}
	catch ( std::exception &e )
	{
		std::cerr << "Exception in constructor of converter class : " << e.what ( ) << std::endl;
	}
}


bool converter::createResultsFile ( const std::string& inputFile, const std::string& outputFile )
{
	try
	{
		if ( outputFile.empty ( ) )
		{
			/* 
			 * We can just output whatever values we have gotten from the set-functions
			 * We must however check if all the required entries have been filled out
			 */
			if ( version.empty ( ) || instanceName.empty ( ) || contributionName.empty ( ) || objectives.empty ( )
				|| objectiveType.empty ( ) || direction.empty ( ) || optimal.empty ( ) || cardinality.empty ( )
				|| points.empty ( ) || valid.empty ( ) )
			{
				throw std::runtime_error ( "Atleast one of the required entries was empty. The results file will not be created and the process terminates" );
			}



		}
	}
	catch ( std::runtime_error &re )
	{
		std::cerr << "Runtime error in createResultsFile in the converter class : " << re.what ( ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << "Exception in createResultsFile in the converter class : " << e.what ( ) << std::endl;
	}
}