//============================================================================
// Name        : Excel.cpp
// Author      : Juan Pablo Eguiguren
// Version     :
// Copyright   : See license file for copyright info
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>

#include "el/ELLocalization.h"

using namespace el::utilities::localization;

int main ( int iArg, char * pArgs[] )
{
	const el_string cUsage = "Usage: excel-xml-to-json-plist <excel_xml_input_file> <json_plist_output_file>";

	// there must be 2 args
	if ( iArg < 3 )
	{
		EL_CC_ERROR_LOG( cUsage.c_str() );

		return EXIT_FAILURE;
	}

	// Try to read and load localization info from parameter 1
	if ( true == ELLocalization::getLocalizationInstance().initLanguage( pArgs[1] ) )
	{
		// Write the new file with Plist XML format
		if ( true == ELLocalization::getLocalizationInstance().writeOutputPlist( el_string(pArgs[2]) ) )
		{
			// Success
			std::cout << "File created successfully" << std::endl;
		}
	}


	return EXIT_SUCCESS;
}
