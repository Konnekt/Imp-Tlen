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
	//ustawia UID w³aœcieciela
	void setOwnerUID(char* UID) ;
	// ustawia czas odebrania aktualnej wiadomosci
	void setMsgTime(cTime64 time) ;
	// nadawca aktualnej wiadomosci
	void setMsgSenderUID(char* UID) ;
	// odbiorca aktualnej wiadomosci
	void setMsgReceiverUID(char* UID) ;
	// tekst aktualnie prztwarzanej wiadomosci
	void setMsgText(char* text) ;
	// true jeœli wiadomoœæ wys³ana, false jeœli odebrana
	void setMsgWasSent(bool was) ;
	//dodaje aktualn¹ wiadomoœæ
	//zwraca true jeœli wszystko posz³o dobrze
	bool addMsg(void) ;
};
