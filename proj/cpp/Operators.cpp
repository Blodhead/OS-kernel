#include <malloc.h>
#include <iostream.h>
#include "../H/Operator.h"
#include "../H/Util.h"
#include "../H/System.h"
#include "../H/Lock.h"

void operator delete(void* block)
{
	Lock::lock(); //PUSHF; INTD;   // sigurnije je ovako, ali bi mozda moglo da se napravi preko lock-a (problem je u interrupt rutini kada se new-uju stvari ?)
      if( block )
      {
         free(block);
         System::couter--;
      }
    Lock::unlock(); //POPF;
}

void* operator new(unsigned int size)
{
	Lock::lock(); //PUSHF; INTD;   // sigurnije je ovako, ali bi mozda moglo da se napravi preko lock-a (problem je u interrupt rutini kada se new-uju stvari ?)
      void* block = malloc(size);
      System::couter++;
      if(block == nullptr) cout<<"GRESKA U ALOKACIJI"<<endl;
    Lock::unlock(); //POPF;

   return block;
}

