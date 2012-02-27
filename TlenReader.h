#pragma once
#include "archreader.h"
#include <vector>

struct msg_index
{
	char userID[26];
	char fake1[6];
	double date;
	char fake2[4];
	int offset;
	int indexNumber;
};

struct msg_header
{
	double date;
	bool fromme;
	bool deleted;
	char fake1[1];
	int lenght;
	int indexNumber;
	char fake2[4];
};

class TlenReader :
	public ArchReader
{
public:
	TlenReader(void);
	~TlenReader(void);
	//przygotowuje archiwum do odczytu
	//sprawdŸ czego oczekuje konkretna implementacja!
	bool Prepare(void* params);
	//pobiera rekord z archiwum, zwraca false jesli archiwum jest juz puste
	bool getNext(void);
	//pobiera UID w³aœcieciela
	char* getOwnerUID(char* buff);
	// pobira czas odebrania aktualnej wiadomosci
	cTime64 getMsgTime(void);
	// nadawca aktualnej wiadomosci
	char* getMsgSenderUID(char* buff);
	//true dopóki nie przejrzeliœmy wszystkich
	bool msgHasReceivers();
	// odbiorcy wiadomoœci (kolejni, jako osobne ci¹gi)
	char* getMsgReceiverUID(char* buff);
	// tekst aktualnie prztwarzanej wiadomosci
	char* getMsgText(char* buff);
	// true jeœli wiadomoœæ wys³ana, false jeœli odebrana
	bool getMsgWasSent(void);
	//iloœæ wiadomoœci w archiwum, które zosta³y zignorowane (b³êdne itp)
	int getNumberOfIgnored();
protected:
	int fake_number;
	int fake_recievers;
	bool fake_wassend;
	bool is_first; // aktualnie przetwarzany rekord jest pierwszy w pliku

	int index_rozmow; //deskryptor pliku
	msg_index* chats; // tablica z strukturami opisuj¹cymi plik chats
	int chats_file_size; // wielkoœæ pliku chats.idx
	int chats_pointer; // aktualna pozycja w tablicy chats

	int rozmowy; //deskryptor pliku
	std::vector<msg_header*> chat_headers; //wypowiedzi
	std::vector<msg_header*>::iterator current_chat_header; //wypowiedzi
	std::vector<char*> chat_strings; //tresc wypowiedz
	std::vector<char*>::iterator current_chat_string; //tresc wypowiedz

	#define plik_index_rozmow L"\\chats.idx"
	#define plik_rozmow L"\\chats.dat"

	//wczytuje index wiadomoœci
	bool loadMessageIndex();
	//wczytuje pojedyncze wiadomoœci
	bool loadMessages();
	//konwertuje datê
	cTime64 BorlandTDateTimeToCTime64(double date);	
};
