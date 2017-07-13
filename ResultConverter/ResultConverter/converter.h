#pragma once

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

/** \mainpage An introduction to the MOrepo converter
* \author Sune Lauth Gadegaard
* \version 1.0.0
*
* \section License
*
* Copyright 2015, Sune Lauth Gadegaard.
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* If you use the software in any academic work, please make a reference to
*
* ``An appropriate reference should go here!''
* \latexonly
* \section{Description}
*
* This software provides a "converter" that given appropritate input, generates a result file compatible witht format used on \href{https://github.com/MCDMSociety}{MOrepo}.
* The software basically consists of a single class "converter". After constructing an object of the class, the simple "set" methods should be used to set the appropriate
* entries, and finally, after setting atleast all required entries, the \texttt{createResultsFile (...)} function should be called.
* \endlatexonly 
*
* \section Compiling
* The codes were compiled using the Visual Studio 2015 compiler on a Windows 10 machine.
* The following flags were used: /W3 /Ox /std:[c++14|c++latest] 
*
*
* \latexonly
*   \section{Example of usage}
*   This section contains an example showing how the \texttt{converter} class can be used to generate a MOrepo compatible json file. In this example we assume the instance
*   is named "instance1", that the contribution is "Foo et al. 2017", and that the class dataReader has the appropriate get methods.

*   \begin{lstlisting}
*       // main.cpp
*		#include"converter.h"
*		#include"dataReader.h" // Assume you have written this yourself
*		#include<vector>
*       int main(int argc, char** argv){
*           try{
*
*				std::vector<std::string> allArgs(argv, argv + argc); // retrieve arguments
*
*               if ( argc < 2 )
*				{
*					throw std::runtime_error ( "Two few arguments. No input file was specified" );
*				}
*				else if ( argc < 3 )
*				{
*					outputFile = "./results.json";
*				}
*				else
*				{
*					outputFile = allArgs[2];
*				}
*				inputFile = allArgs[1];
*
*				dataReader dr = dataReader ( inputFile ); //Read your own result file
*
*				converter conv = converter(); // Create a converter object
*				conv.setVersion ( "1.0" );
*				conv.setInstanceName ( "instance1" );
*				conv.setContributionName ( "Foo et al. 2017" );
*				conv.setObjectives ( dr.getNumberOfObjectives ( ) );
*				conv.setObjectiveTypes ( dr.getObjectiveTypes ( ) );
*				conv.setOptimal ( dr.isItOptimal ( ) );
*				conv.setCardinality ( dr.getCardinalityOfFrontier ( ) );
*				conv.setPoints ( dr.getPoints ( ) , dr.getPointTypes ( ) );
*				conv.setValidity ( dr.getValidityOfSolution ( ) );
*				conv.createResultsFile ( outputFile );
*
*				return 0;
*			}
*			catch ( std::runtime_error& re )
*			{
*				std::cerr << re.what () << "\n";
*           }
*			catch(std::exception &e)
*			{
*               std::cerr << "Exception: " << e.what() << "\n";
*           }
*			catch(...)
*			{
*          	    std::cerr << "An unexpected exception was thrown. Caught in main.\n";
*           }
*			return 0;
*       }
*   \end{lstlisting}
* \endlatexonly
*/

class converter
{
private:
	std::ofstream outputStream;		//! Stream used for generating the output file 
	std::ifstream inputStream;		//! Stream used to read from the input file


	/** @name Required entries
	*  This groupe of variables holds the values of all the required entries in the resulting result file.
	*  If not all the required entries have been set, no result file will be generated in the end.
	*/
	///@{
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
	///@}


	/** @name Optional entries
	*  This groupe of variables holds the values of all the optional entries in the resulting result file.
	*/
	///@{
		std::string comments;			//! Contains any relevant comments. Optional
		std::string suppCard;			//! Contains information about the cardinality of supperted non--dominated points. Optional
		std::string extCard;			//! Number of extreme supported nondominated points . Optional
		std::string cpu;				//! Contains information about the running time. Optional
		std::string machineSpec;		//! Contains information about the specifications of the machine the instances have been solved on. Optional
		std::string misc;				//! An entry you may use as you like. It could e.g. contain an object with more detailed entries about the experiment. Optional
	///@}


	/** @name Numeric variables
	*  Variables used to hold nummeric values, that will eventually find its way into the results file
	*/
	///@{
		long numSuppCard;					//! Number of supported point
		long numExtCard;					//! Number of extreme supported points
		long numCard;						//! Number of non--dominated points
		int numberOfObjectives;				//! Number of objective functions
	///@}


	/*!
	 * \breif Function creating the string output for a "point"
	 *
	 * Function creating the string output for a "point" in json format.
	 * \param thePoint reference to a vector of doubles. The vector contains the non--dominated point in objective space.
	 * \param type String containing information about whether the point is extreme supported ("se"), non-extreme supported ("sne"),
	 * supported (my be extreme or non--extreme) ("s"), unsuported ("un") or if this information is unknown ("null").
	 * \param objNames reference to a vector of strings. Contains the names of the objectives, that is objNames[0]="z1", objName[1]="z2" and so forth.
	 */
	std::string pointToString ( std::vector<double>& thePoint, std::string& type, std::vector<std::string>& objNames );

public:
	/*
	 * \brief Constructor with no arguments
	 *
	 * Constructor with no arguments. Constructs an instance of the converter class. Sets up the strings used to create the results file as empty strings.
	 * It sets the version of the results file to 1.0 per default.
	 */
	converter ( );

	/*!
	 * \brief Creates a results file
	 *
	 *  Creates a results file with the path "outputFile". The file is only created if all the required entries has been set using the setMethods.
	 * \param outputFile reference to a constant string. outputFile contains the path to the results file. If no file with that path exists a new file is created. If the file exists, it will be overwritten!
	 * \param inputFile reference to a constant string. inputFile contains the path to the file you want to read from (this functionality is not yet implemented).
	 * \return If the putput file is succesfully created the function returns true, otherwise false (an exception/runtime error will be thrown)
	 */
	bool createResultsFile ( const std::string& outputFile, const std::string& inputFile = "" );

	/*!
	 * \brief Set the version of the resultfile
	 *
	 * Sets the version fo the results file using the provided string
	 * \param versionNumber reference to a constant string. If the version is 5.4 the input should be a string "5.4"
	 */
	inline void setVersion ( const std::string& versionNumber ) { version = "\t\"version\": \"" + versionNumber + "\",\n"; }

	/*!
	 * Set the name of the instance for which the result file contains information
	 * \param theInstanceName reference to a string containing the name of the instance for which the results are for.
	 */
	inline void setInstanceName ( std::string& theInstanceName ) { instanceName = "\t\"instanceName\": \"" + theInstanceName + "\",\n"; }

	/*!
	 * \brief Sets the name of the contribution.
	 *
	 * Sets the contribution name. It should be a string with the name of the contribution in which the instances and results have been published.
	 * \param constName const reference to a string. Contains the name of the constribution, e.g. "Pedersen08".
	 */
	inline void setContributionName ( const std::string& contName ) { contributionName = "\t\"contributionName\": \"" + contName + "\",\n"; }

	/*!
	 * Sets the number of objectives
	 * \param numOfObjectives integer specififying the number of objective functions of the multiobjective optimization problem.
	 */
	inline void setObjectives ( int numOfObjectives ) { objectives = "\t\"objectives\": " + std::to_string ( numOfObjectives ) + ",\n"; numberOfObjectives = numOfObjectives; }


	/*!
	 * \brief Sets the objective types
	 *
	 * Sets the objective types to either int, float, or null (if unknown).
	 * \param objTypes vector of strings containing the type of each objective. That is if the i'th objective is integral, then objType[i] = "int"
	 * \note The function setObjectives must be called before setObjectiveTypes. Otherwise a runtime error is thrown.
	 */
	void setObjectiveTypes ( std::vector<std::string>& objTypes );

	/*!
	 * \brief Sets the directions of the objective functions
	 *
	 * Sets the directions of the objective functions. The directions can either be "min" or "max".
	 * \param theDirections reference to a vector of strings. If forexample there are three objective functions where the two
	 * first are of the minimization-kind and the last is a maximization, we should specify a vector { "min" , "min" , "max" } as the function argument.
	 */
	void setDirections ( std::vector<std::string>& theDirections );

	/*!
	 * Specifies whether the solution is an optimal solution to the specific instance or not.
	 * \param itsOptimal boolean. If itsOptimal = true, it is assumed that the solutions is optimal solution, and if itsOptimal = false, it has not been verified optimal, or it is known to be suboptimal
	 */
	inline void setOptimal ( bool itsOptimal ) { if ( itsOptimal ) optimal = "\t\"optimal\": true,\n"; else optimal = "\t\"optimal\": false,\n"; }

	/*!
	 * Sets the cardinality of the non--dominated frontier
	 * \param theCardinality integer specifying the number of points on the efficient frontier.
	 */
	inline void setCardinality ( int theCardinality ) { numCard = theCardinality; cardinality = "\t\"card\": " + std::to_string ( theCardinality ) + ",\n"; }

	/*!
	 * Sets the points and the point types
	 *
	 * \param thePoints reference to a vector of vectors of doubles. thePoints[i] contains the i'th point on the frontier and thePoints[i][j] contains the j'th entry
	 * of the i'th non--dominated point.
	 * \param pointTypes reference to a vector of strings. Contains a specification of the type of each point. type can be either extreme supported ("se"),
	 * non-extreme supported ("sne"), supported (my be extreme or non--extreme) ("s"), unsuported ("un") or if this information is unknown ("null").
	 */
	void setPoints ( std::vector<std::vector<double>>& thePoints, std::vector<std::string>& pointTypes );

	/*!
	 * \brief Sets the validity of the solution to either true or false.
	 *
	 * Sets the validity of the solution to either true or false. If isValid is false, the solution might be in conflict with another solution on MOrepo.
	 * This will be sorted out eventually
	 * \param isValid boolean. If true, the solution is not in conflict with other known solutions. If false, it is in conflict with a known solution.
	 */
	inline void setValidity ( bool isValid ) { if ( isValid ) valid = "\t\"valid\": true,\n"; else valid = "\t\"valid\": false,\n"; }

	/*!
	 * Sets the comments entry
	 * \param comment reference to a string. Contains the comment that should be attached to the result file.
	 */
	inline void setComments ( std::string& comment ) { comments = "\t\"comments\": \"" + comment + "\",\n"; }

	/*!
	 * Sets the CPU information along with the specs of the machine the experiments was carried out on.
	 * \param executionTime double containing the number of seconds used to compute the efficient frontier
	 * \param machineSpecs reference to a string containing the specifics of the machine used to carry out the experiments, e.g. "Intel Core i7-4785T 2.2 GHz, 16 GB RAM, Linux Ubuntu 64bit"
	 */
	void setCPU ( double executionTime, std::string& machineSpecs );

	/*!
	 * Sets the cardinality of the set of extreme supported non--dominated solutions
	 * \param extremeCardinality integer containing the number of extreme supported non--dominated solutions.
	 */
	void setExtremeCardinality ( int extremeCardinality ) { extCard = "\t\"extCard\": " + std::to_string ( extremeCardinality ) + ",\n"; }

	/*!
	 * Sets the cardinality of the set of supported non--dominated solutions
	 * \param supportedCardinality integer containing the number of supported non--dominated solutions.
	 */
	void setSupportedCardinality ( int supportedCardinality ) { extCard = "\t\"suppCard\": " + std::to_string ( supportedCardinality ) + ",\n"; }
	
	/*!
	 * Sets the misc entry
	 * \param theMISC reference to a string containing the misc that should be attached to the result file
	 * \note This entry may be used as you like. It could e.g. contain an object with more detailed entries about the experiment.
	 */
	void setMisc ( std::string& theMISC ) { misc = "\t\"misc\": \"" + theMISC + ",\n"; }

};