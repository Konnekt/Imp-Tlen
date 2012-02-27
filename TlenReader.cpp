#include "StdAfx.h"
#include "TlenReader.h"

TlenReader::TlenReader(void)
{
	fake_number = -1;
	fake_recievers = 10;
	fake_wassend = true;
	is_first = true;
	index_rozmow = -1;
	chats_file_size = 0;
	chats_pointer = 0;
}

TlenReader::~TlenReader(void)
{
	if(index_rozmow != -1)
	{
		_close(index_rozmow);
	}
	if(rozmowy != -1)
	{
		_close(rozmowy);
	}
	delete chats;
	for(std::vector<msg_header*>::const_iterator i = chat_headers.begin(); i != chat_headers.end(); ++i)
	{
		delete (*i);
	}
	for(std::vector<char*>::const_iterator i = chat_strings.begin(); i != chat_strings.end(); ++i)
	{
		delete (*i);
	}
}

//przygotowuje archiwum do odczytu
//sprawd� czego oczekuje konkretna implementacja!
bool TlenReader::Prepare(void* params)
{
	int result;
	_TCHAR* dirName = *((_TCHAR**)params);
	_TCHAR msgIndexFile[300];
	_TCHAR msgFile[300];

	result = _tcscpy_s(msgIndexFile,300,dirName);
	VALIDATE_RESULT

	result = _tcscat_s(msgIndexFile,300,plik_index_rozmow);
	VALIDATE_RESULT

	result = _tcscpy_s(msgFile,300,dirName);
	VALIDATE_RESULT

	result = _tcscat_s(msgFile,300,plik_rozmow);
	VALIDATE_RESULT

#ifdef DEBUG
	 _tcprintf(L"%s\r\n",msgIndexFile);
	 _tcprintf(L"%s\r\n",msgFile);
	 _tcprintf(L"sizeof msg_index is %d\r\n",sizeof(msg_index));
	 _tcprintf(L"sizeof msg_header is %d\r\n",sizeof(msg_header));
#endif
	result = _tsopen_s(&index_rozmow, msgIndexFile , _O_BINARY | _O_RDONLY, _SH_DENYWR, _S_IREAD);
	VALIDATE_RESULT

		result = _tsopen_s(&rozmowy, msgFile , _O_BINARY | _O_RDONLY, _SH_DENYWR, _S_IREAD);
	VALIDATE_RESULT
	
	struct _stat fileInfo;
	result = _tstat(msgIndexFile, &fileInfo);
	VALIDATE_RESULT
	chats_file_size = fileInfo.st_size;

#ifdef DEBUG
		_tcprintf(L"File size is %d, this is %d msg_index'es and %d bytes sparse\r\n",
			chats_file_size,
			chats_file_size / sizeof(msg_index),
			chats_file_size % sizeof(msg_index));
#endif

	if ((chats_file_size % sizeof(msg_index)) != 0)
	{
		_tcprintf(L"Message index file size is %d, this is not a multiply of %d\r\n",
			chats_file_size,
			sizeof(msg_index)
			);
		return false;
	}

	chats = new msg_index[chats_file_size / sizeof(msg_index)];

	return loadMessageIndex();
}
//pobiera rekord z archiwum, zwraca false jesli archiwum jest juz puste
bool TlenReader::getNext(void)
{
	if (is_first)
	{
		// pocz�tek odczytu
		is_first = false;
		//przesuwa� si� po msg_headers dop�ki si� zgadza indexID? wygl�da na to, �e zmiana indexID oznacza koniec w�tku.
		//++chats_pointer;
	}
	else
	{
		//przesuwa� si� po msg_headers dop�ki si� zgadza indexID? wygl�da na to, �e zmiana indexID oznacza koniec w�tku.
		++chats_pointer;
	}

	if(chats_pointer >= chats_file_size / sizeof(msg_index))
		return false;
#ifdef DEBUG
	_tcprintf(L"Processing thread number %d out of %d with indexID %d\r\n",
		chats_pointer + 1,
		chats_file_size / sizeof(msg_index),
		chats[chats_pointer].indexNumber);
#endif
	return true;
}
//pobiera UID w�a�cieciela
char* TlenReader::getOwnerUID(char* buff)
{
	return "tescik@tescik.pl";
}
// pobira czas odebrania aktualnej wiadomosci
cTime64 TlenReader::getMsgTime(void)
{
	return BorlandTDateTimeToCTime64( chats[chats_pointer].date );
}
// nadawca aktualnej wiadomosci
char* TlenReader::getMsgSenderUID(char* buff)
{
	return chats[chats_pointer].userID;
}
//true dop�ki nie przejrzeli�my wszystkich
bool TlenReader::msgHasReceivers()
{
	if(fake_number-->0)return true;
	return false;
}
// odbiorcy wiadomo�ci (kolejni, jako osobne ci�gi)
char* TlenReader::getMsgReceiverUID(char* buff)
{
	return "inny@kolega.xxx";
}
// tekst aktualnie prztwarzanej wiadomosci
char* TlenReader::getMsgText(char* buff)
{
	return "witaj Romku!";
}
// true je�li wiadomo�� wys�ana, false je�li odebrana
bool TlenReader::getMsgWasSent(void)
{
	fake_wassend=!fake_wassend;
	return fake_wassend;
}
//ilo�� wiadomo�ci w archiwum, kt�re zosta�y zignorowane (b��dne itp)
int TlenReader::getNumberOfIgnored()
{
	return 44;
}

//wczytuje index wiadomo�ci
bool TlenReader::loadMessageIndex()
{		
	int result = _read(index_rozmow, chats, chats_file_size);

	if (result != chats_file_size)
	{
		_tcprintf(L"Unable to load whole message index file into memory\r\n");
		return false;
	}

	return loadMessages();
}

//wczytuje pojedyncze wiadomo�ci
bool TlenReader::loadMessages()
{
	msg_header* naglowek = new msg_header();
	int lastMsgId = -1;
	while(_read(rozmowy, naglowek, sizeof(msg_header)) != 0)
	{
		chat_headers.push_back(naglowek);
		char* tresc = new char[naglowek->lenght];
		_read(rozmowy, tresc, naglowek->lenght);
		chat_strings.push_back(tresc);
		//printf("read message:[%d][%d] %s\n", naglowek->indexNumber, naglowek->fromme,tresc);

		if (naglowek->indexNumber < lastMsgId)
		{
			_tcprintf(L"Message indexes are not in ascending order.\r\n");
			return false;
		}
		lastMsgId = naglowek->indexNumber;
		naglowek = new msg_header();
	}

	current_chat_header = chat_headers.begin();
	current_chat_string = chat_strings.begin();

	return true;
}

cTime64 TlenReader::BorlandTDateTimeToCTime64(double date)
{
	// don't ask me, this just works. taken from http://www.delphi-forum.de/topic_65945.html
	cTime64 result = (time_t)(86400 * ( date - 25569));
	return result;
}