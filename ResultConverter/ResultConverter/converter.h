#pragma once

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

class converter
{
private:
	std::ofstream outputStream;
	std::ifstream inputStream;

	// Required entries
	std::string version;			//! Contains information about the version of the results format. Current version is 1.0. Required
	std::string instanceName;		//! Contains information about the instance name for which the results are obtained. Required
	std::string contributionName;	//! Contains the name of the contribution. Required
	std::string objectives;			//! Contains the number of objectives. Required
	std::string objectiveType;		//! Contains the type of objectives. Required
	std::string direction;			//! Contains the directions of the objectives. Required
	std::string optimal;			//! Contains information about whether the solution is known to optimal or not. Required
	std::string cardinality;		//! Contains information about the cardinality of the solution. Required
	std::string points;				//! Contains a list of all the points on the current best known approximation of the efficient frontier of the MOOP.
	std::string valid;				//! Contains information about whether the results are considered valid or not. If they are in conflict with other results, valid is false. Required

	//Optional entries
	std::string comments;			//! Contains any relevant comments. Optional
	std::string suppCard;			//! Contains information about the cardinality of supperted non--dominated points. Optional
	std::string extCard;			//! Number of extreme supported nondominated points . Optional
	std::string cpu;				//! Contains information about the running time. Optional
	std::string machineSpec;		//! Contains information about the specifications of the machine the instances have been solved on. Optional
	std::string misc;				//! An entry you may use as you like. It could e.g. contain an object with more detailed entries about the experiment. Optional
	
	
	
	

	double executionTime;
	long numSuppCard;
	long numExtCard;
	long numCard;
	int numberOfObjectives;

	std::string pointToString ( std::vector<double>& thePoint, std::string& type, std::vector<std::string>& objNames);
public:
	/*
	 * \brief Constructor with no arguments
	 *
	 * Constructor with no arguments. Constructs an instance of the converter class. Sets up the strings used to create the results file
	 */
	converter ( );

	bool createResultsFile (const std::string& outputFile, const std::string& inputFile = "" );


	inline void setVersion ( const std::string& versionNumber ) { version = "\t\"version\": \"" + versionNumber + "\",\n";}

	inline void setInstanceName ( std::string& theInstanceName ) { instanceName = "\t\"instanceName\": \"" + theInstanceName +"\",\n"; }

	/*
	* \brief Sets the name of the contribution.
	*
	* Sets the contribution name. It should be a string with the name of the contribution in which the instances and results have been published.
	* \param constName const reference to a string. Contains the name of the constribution, e.g. "Pedersen08".
	*/
	inline void setContributionName ( const std::string& contName ) { contributionName = "\t\"contributionName\": \"" + contName + "\",\n"; }
	inline void printContributionName ( ) { std::cout << contributionName; }

	
	inline void setObjectives ( int numOfObjectives ) { objectives = "\t\"objectives\": " + std::to_string ( numOfObjectives ) + ",\n"; numberOfObjectives = numOfObjectives; }
	inline void printObjectives ( ) { std::cout << objectives; }

	/*
	 * \brief Sets the objective types
	 *
	 * Sets the objective types to either int, float, or null (if unknown). 
	 * \param objTypes vector of strings containing the type of each objective. That is if the i'th objective is integral, then objType[i] = "int"
	 * \note The function setObjectives must be called before setObjectiveTypes. Otherwise a runtime error is thrown.
	 */
	void setObjectiveTypes ( std::vector<std::string>& objTypes );

	void setDirections ( std::vector<std::string>& theDirections );

	inline void setOptimal ( bool itsOptimal ) { if ( itsOptimal ) optimal = "\t\"optimal\": true,\n"; else optimal = "\t\"optimal\": false,\n"; }

	inline void setCardinality ( int theCardinality ) { numCard = theCardinality; cardinality = "\t\"card\": " + std::to_string ( theCardinality ) + ",\n"; }

	/*
	 * Sets the points and the point types
	 */
	void setPoints ( std::vector<std::vector<double>>& thePoints, std::vector<std::string>& pointTypes );

	inline void setValidity ( bool isValid ) { if ( isValid ) valid = "\t\"valid\": true,\n"; else valid = "\t\"valid\": false,\n"; }
};