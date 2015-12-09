#ifndef ELLOCALIZATION_H_
#define ELLOCALIZATION_H_

#include "ELEngineDefinitions.h"
#include <cstdio>
#include <string>
#include <map>

namespace el
{
	namespace utilities
	{
		namespace localization
		{

			static const el_unsigned_int cExcelXMLRowLevel = 3;
			static const el_char * cEXCEL_XML_LEVEL_TREE[] =
			{
				"Workbook",
				"Worksheet",
				"Table",
				"Row", // Current Row Level
				"Cell",
				"Data"
			};

			class ELLocalization
			{
			private:

				// Properties
				el_string m_sfileName;
				std::map<el_string, el_string> m_map;

				// Methods
				ELLocalization(void);

#ifdef __cplusplus
	#if __cplusplus >= 201103L
				ELLocalization(ELLocalization const&) = delete;
				void operator=(ELLocalization const&) = delete;
	#else
				ELLocalization(ELLocalization const&);
				void operator=(ELLocalization const&);
	#endif
#endif
				// Loads language file into map
				el_bool loadLanguageFile(el_string);

				// Parses file
				el_bool parseXMLFile(el_string);

			public:

				// Methods
				// Get instance
				static ELLocalization& getLocalizationInstance(void)
				{
					static ELLocalization instance; // Guaranteed to be destroyed.
					return instance;				// Instantiated on first use.
				}

				// Localize a text
				const el_string localizeText(const el_string);

				// Init language
				el_bool initLanguage(el_string);

				// Write a file output if there is a valid key map
				el_bool writeOutputPlist(const el_string& name);

				// Checks if file exists
				static el_bool fileExists (const el_string& name)
				{
				    if (FILE *file = fopen(name.c_str(), "r"))
				    {
				        std::fclose(file);
				        return true;
				    }
			        return false;
				}

			};

			// Easy and convenient localization method
			#define ELLoc(text) ELLocalization::getLocalizationInstance().localizeText(text)
			#define ELLocC(text) ELLocalization::getLocalizationInstance().localizeText( el_string(text) )
		}
	}
}

#endif
