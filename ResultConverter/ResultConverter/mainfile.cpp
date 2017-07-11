#include<iostream>
#include"converter.h"

int main ( )
{
	converter conv = converter ( );
	conv.setContributionName ( "Pedersen08" );
	conv.printContributionName ( );
	conv.setObjectives ( 2 );
	conv.printObjectives ( );
	return 0;
}