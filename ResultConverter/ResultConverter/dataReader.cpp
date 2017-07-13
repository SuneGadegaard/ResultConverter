#include"dataReader.h"

dataReader::dataReader ( ) : cpuTime(0)
{

}


/*********************************************************************************************************/
void dataReader::ReadData ( )
{
	std::string line;
	std::string tmp;

	// Go to line 3 to get the computation time
	for ( int i = 1; i <= 3; ++i )
	{
		std::getline ( inStream, line );
		if ( 3 == i )
		{
			std::stringstream tmpStream( line );
			tmpStream >> tmp; // Get the word Total
			tmpStream >> tmp; // Get the word time:
			tmpStream >> cpuTime;// Get the double containing the computation time!
		}
	}


	//Run down the file until we have the start of the points
	for ( ; ; )
	{
		std::getline ( inStream , line );
		if ( '=' == line.back() )
		{
			break;
		}
	}
	// Now we should be at the point where the actual points are listed!
	double anyNum;
	while ( inStream >> anyNum )
	{
		std::vector<double> p(2);
		p[0] = anyNum;
		inStream >> anyNum;
		p[1] = anyNum;

		if ( points.empty ( ) || p[0] != points.back()[0] ) // Add the point if it is the first
		{
			points.push_back ( p );
		}
		else // If the point is actually dominating the previous. If so, let it replace the previous. (weak front is saved in file)
		{
			points.back ( ) = p;
		}
	}

	frontSize = int ( points.size ( ) );
}