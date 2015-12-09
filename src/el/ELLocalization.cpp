#include "ELLocalization.h"

#include "../tinyxml2/tinyxml2.h"

using namespace std;
using namespace el::utilities::localization;

// Constructors
ELLocalization::ELLocalization(void)
{
	// Clear data
	this->m_map.clear();
}

// Init language
el_bool ELLocalization::initLanguage(el_string sLanguage)
{
	el_string sFileName = sLanguage;

	// if no change in language
	if (sFileName == this->m_sfileName)
	{
		// Language has been initialized already
		return true;
	}

	// if language not empty and exists
	if (!sFileName.empty() && ELLocalization::fileExists(sFileName))
	{
		// Try to load language
		if (true == loadLanguageFile(sFileName))
		{
			this->m_sfileName = sFileName;

			// Language changed successfully
			return true;
		}
	}

	return false;
}

// Loads language file into map
el_bool ELLocalization::loadLanguageFile(el_string sLanguange)
{
	// Get full file name
	el_string sFileContent = sLanguange;

	// Parse XML file and insert into map
	parseXMLFile(sFileContent);

	return this->m_map.size() > 0;
}

// Parses file
el_bool ELLocalization::parseXMLFile(el_string sXMLContent)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(sXMLContent.c_str());

	if (doc.ErrorID() != 0)
	{
		EL_CC_ERROR_LOG( el_string("No localization document was opened.\nBad EXCEL XML file structure or file not found: ") + sXMLContent + el_string("\n") + doc.ErrorName() + "\n" );
		return true;
	}

	// Go into EXCEL tree
	tinyxml2::XMLElement * pParent = NULL;

	// Get first level
	el_unsigned_int iLevel = 0;
	pParent = doc.FirstChildElement(cEXCEL_XML_LEVEL_TREE[iLevel]);

	// If nothing found just leave
	if (NULL == pParent)
	{
		return false;
	}

	// Go into penultimate level
	while (NULL != pParent && iLevel < cExcelXMLRowLevel)
	{
		// Get into next level
		pParent = pParent->FirstChildElement(cEXCEL_XML_LEVEL_TREE[++iLevel]);
		
		// If we hadn't gotten to the bottom level and there is no child, exit with error
		if (NULL == pParent && iLevel < cExcelXMLRowLevel)
		{
			EL_CC_ERROR_LOG(el_string("Not a valid 'EXCEL XML' file for localization: " + sXMLContent));
			return false;
		}
	}

	// No turning back point - Cleaning current localization
	this->m_map.clear();

	// Macros for convenience
	#define CURRENT_KEY_CELL pParent->FirstChildElement(cEXCEL_XML_LEVEL_TREE[cExcelXMLRowLevel+1])
	#define CURRENT_VALUE_CELL CURRENT_KEY_CELL->NextSiblingElement()

	// Read every entry
	do 
	{
		if (NULL != CURRENT_KEY_CELL && NULL != CURRENT_VALUE_CELL && 
			NULL != CURRENT_KEY_CELL->FirstChildElement(cEXCEL_XML_LEVEL_TREE[cExcelXMLRowLevel + 2]) &&
			NULL != CURRENT_VALUE_CELL->FirstChildElement(cEXCEL_XML_LEVEL_TREE[cExcelXMLRowLevel + 2]) 
			)
		{
			// Get key and value for this ROW
			el_string sKey = CURRENT_KEY_CELL->FirstChildElement(cEXCEL_XML_LEVEL_TREE[cExcelXMLRowLevel + 2])->GetText();
			el_string sValue = CURRENT_VALUE_CELL->FirstChildElement(cEXCEL_XML_LEVEL_TREE[cExcelXMLRowLevel + 2])->GetText();
			
			// Check if key value already exists
			if (this->m_map.find(sKey) == this->m_map.end())
			{
				// if element does not exists insert into map
				this->m_map.insert(pair<el_string, el_string>(sKey, sValue));
			}
#ifdef _DEBUG
			// register a warning if element already exist
			else
			{
				el_string str = el_string("Localization file error. Two entries with the same key: ") + sKey + el_string("\n");
				EL_CC_WARNING_LOG( str.c_str() );
			}
#endif
		}

		// Move to next rwo
		pParent = pParent->NextSiblingElement();

	} while (NULL != pParent);

	// Not needed anymore
	#undef CURRENT_KEY_CELL
	#undef CURRENT_VALUE_CELL

	return true;
}

// return string corresponding to key
const el_string ELLocalization::localizeText(const el_string sKey)
{
	// resulting value pointer
	map<el_string, el_string>::iterator it = this->m_map.find(sKey);

	// if there is a value return it
	if (it != this->m_map.end())
	{
		return it->second;
	}
	// otherwise, just log the WARNING and return same string
	EL_CC_WARNING_LOG_VARS("No valid id found for localization. Key ID = %s", sKey.c_str());
	return sKey;
}

// Write a file output if there is a valid key map
el_bool ELLocalization::writeOutputPlist(const el_string& name)
{
	// if the map is valid and filled
	if ( name.length() > 0 && this->m_map.size() > 0 )
	{
		// Open file
	    if (FILE *pFile = fopen(name.c_str(), "w"))
	    {
	    	// write header
	    	el_string content = el_string() +
	    			"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
	    			"<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n" \
	    			"<plist version=\"1.0\">\n" \
	    				"<dict>\n";

	    	// write content
	    	for(map<el_string,el_string>::iterator it = this->m_map.begin(); it != this->m_map.end(); it++ )
	    	{
	    		content = content + "\t<key>" + it->first + "</key><string>" + it->second + "</string>\n";
	    	}

			// write footer
			content = content +
	    				"</dict>\n" \
				    "</plist>";

			// write to pFile
			fprintf(pFile, "%s", content.c_str());

	    	// Close pFile
	        std::fclose(pFile);
	        return true;
	    }
        return false;
	}

	return false;
}
