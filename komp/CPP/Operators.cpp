#include <malloc.h>
#include <iostream.h>
#include "../H/Operator.h"
#include "../H/Util.h"

void operator delete(void* block)
{
   lock; //PUSHF; INTD;   // sigurnije je ovako, ali bi mozda moglo da se napravi preko lock-a (problem je u interrupt rutini kada se new-uju stvari ?)
      if( block )
      {
         free(block);

      }
   unlock; //POPF;
}

void* operator new(unsigned int size)
{
   lock; //PUSHF; INTD;   // sigurnije je ovako, ali bi mozda moglo da se napravi preko lock-a (problem je u interrupt rutini kada se new-uju stvari ?)
      void* block = malloc(size);

      if(block == nullptr) cout<<"GRESKA U ALOKACIJI"<<endl;
   unlock; //POPF;

   return block;
}

