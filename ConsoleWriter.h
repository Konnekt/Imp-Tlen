#pragma once
#include "archwriter.h"

class ConsoleWriter :
	public ArchWriter
{
public:
	ConsoleWriter(void);
	~ConsoleWriter(void);	
	//przygotowuje archiwum do zapisu
	bool Prepare(void* params) ;
	//ustawia UID w�a�cieciela
	void setOwnerUID(char* UID) ;
	// ustawia czas odebrania aktualnej wiadomosci
	void setMsgTime(cTime64 time) ;
	// nadawca aktualnej wiadomosci
	void setMsgSenderUID(char* UID) ;
	// odbiorca aktualnej wiadomosci
	void setMsgReceiverUID(char* UID) ;
	// tekst aktualnie prztwarzanej wiadomosci
	void setMsgText(char* text) ;
	// true je�li wiadomo�� wys�ana, false je�li odebrana
	void setMsgWasSent(bool was) ;
	//dodaje aktualn� wiadomo��
	//zwraca true je�li wszystko posz�o dobrze
	bool addMsg(void) ;
};
