#include"converter.h"

converter::converter ( ):
	version ( "\t\"version\": \"1.0\",\n" ),
	instanceName ( " " ),
	contributionName ( " " ),
	objectives ( " " ),
	objectiveType ( " " ),
	direction ( " " ),
	optimal ( " " ),
	cardinality ( " " ),
	points ( " " ),
	valid ( " " ),
	comments ( " " ),
	suppCard ( " " ),
	extCard ( " " ),
	cpu ( " " ),
	machineSpec ( " " ),
	misc ( " " )
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


			// Now that we know that all required fields are there, we can start creating the file
			// Start by opening the output file
			outputStream.open ( "./results.dat", std::ofstream::out );

			// If the stream is not working correctly, throw a runtime error
			if ( !outputStream )
			{
				throw std::runtime_error ( "The output file used in createResultsFile is not working properly. The process is therefore terminated.\n" );
			}

			outputStream << "{\n"
				<< version
				<< instanceName
				<< contributionName
				<< objectives
				<< objectiveType
				<< direction
				<< optimal
				<< cardinality
				<< points
				<< valid
				<< "}";


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

/*********************************************************************************************************/
void converter::setObjectiveTypes ( std::vector<std::string>& objTypes )
{
	try
	{
		if ( objTypes.size ( ) != size_t ( numberOfObjectives ) )
		{
			throw std::runtime_error ( "The number of \"types\" handed to the function does not match the number of objectives" );
		}
		objectiveType = "\t\"objectiveType\": [";
		for ( auto it = objTypes.begin ( ); it != objTypes.end ( ); ++it )
		{
			if ( std::next ( it ) == objTypes.end ( ) )
			{
				objectiveType += "\"" + *it + "\"";
			}
			else
			{
				objectiveType += "\"" + *it + "\", ";
			}
		}
		objectiveType += "],\n";

	}
	catch ( std::runtime_error &re )
	{
		std::cerr << "Runtime error in setObjectiveTypes in the converter class : " << re.what ( ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << "Exception in setObjctiveTypes in the converter class : " << e.what ( ) << std::endl;
	}
}

/*********************************************************************************************************/
void converter::setDirections ( std::vector<std::string>& theDirections )
{
	try
	{
		if ( theDirections.size ( ) != size_t ( numberOfObjectives ) )
		{
			throw std::runtime_error ( "The number of \"directions\" handed to the function does not match the number of objectives" );
		}

		direction = "\t\"objectiveType\": [";
		for ( auto it = theDirections.begin ( ); it != theDirections.end ( ); ++it )
		{
			if ( std::next ( it ) == theDirections.end ( ) )
			{
				direction += "\"" + *it + "\"";
			}
			else
			{
				direction += "\"" + *it + "\", ";
			}
		}
		direction += "],\n";
	}
	catch ( std::runtime_error &re )
	{
		std::cerr << "Runtime error in setDirections in the converter class : " << re.what ( ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << "Exception in setDirections in the converter class : " << e.what ( ) << std::endl;
	}
}

/*********************************************************************************************************/
void converter::setPoints ( std::vector<std::vector<double>>& thePoints, std::vector<std::string>& pointTypes )
{
	// Check if there is any points to be added to the results file
	if ( thePoints.empty() )
	{
		throw std::runtime_error ( "There is no points to be added to the results file. The process is therefore terminated!\n" );
	}
	// Check if all the points is of the right dimensions
	for ( auto it = thePoints.begin ( ); it != thePoints.end ( ); ++it )
	{
		if ( it->size ( ) != numberOfObjectives )
		{
			throw std::runtime_error ( "Not all of the points you want to insert into the results file has the dimension as was provided by the funciton setObjectives" );
		}
	}
	
	// Allocate memory in a vector of strings for the names of the objectives. That is *objName.begin()="z1", *std::next(objName.begin())="z2" and so forth.
	std::vector<std::string> objNames;
	for ( auto it = 1; it <= numberOfObjectives; ++it )
	{
		objNames.push_back ( "\"z" + std::to_string(it) + "\": " );
	}

	
	points = "\t\"points\": [\n";
	
	auto typeIterator = pointTypes.begin ( );
	for ( auto it = thePoints.begin ( ); it != thePoints.end ( ); ++it )
	{
		points += pointToString ( *it, *typeIterator, objNames );
		if ( std::next ( it ) == thePoints.end ( ) ) points += "\n";
		else points += ",\n";
	}

	points += "\t]\n";
}

/*********************************************************************************************************/
std::string converter::pointToString ( std::vector<double>& thePoint, std::string& type, std::vector<std::string>& objNames )
{
	try
	{
		auto pointIt = thePoint.begin ( );
		auto nameIt = objNames.begin ( );
		std::string pointString;

		//Start by indenting properly and adding the opening curly bracket
		pointString = "\t\t{\n";
		for ( ; pointIt != thePoint.end ( ) && nameIt != objNames.end ( ); ++pointIt, ++nameIt )
		{
			pointString += "\t\t\t" + *nameIt + ": " + std::to_string(*pointIt) + ",\n";
		}
		pointString += "\t\t\t\"type\": \"" + type + "\",\n";
		pointString += "\t\t}";
		return pointString;
	}
	catch ( std::runtime_error& re )
	{
		std::cerr << "Runtime error in pointString in the converter class : " << re.what ( ) << std::endl;
	}
	catch ( std::exception& e )
	{
		std::cerr << "Exception error in pointString in the converter class : " << e.what ( ) << std::endl;
	}
}