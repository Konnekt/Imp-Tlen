// imp-tlen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TlenReader.h"
#include "ConsoleWriter.h"


// folder_danych suffix_serwera numer_sieci
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc != 4)
	{
		_tcprintf(L"Error in arguments list\r\n");
		return 9;
	}
  ArchReader* myReader = new TlenReader();
  /*for(int i=0; i < argc; i++)
	  _tcprintf(L"%s\n",argv[i]);*/

  if(!myReader->Prepare(&argv[1])) 
	{	
		_tcprintf(L"Error in prepare reader\r\n");
		return 10;
	}
  ArchWriter* myWriter = new ConsoleWriter();
  if(!myWriter->Prepare(NULL)) 
	{	
		_tcprintf(L"Error in prepare writer\r\n");
		return 11;
	}

  myResult addedMsgCount = ArchImporter::Run(myReader,myWriter);

  delete myReader;
  delete myWriter;

	return 0;
}

