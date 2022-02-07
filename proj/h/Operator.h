#ifndef H_OPERATOR_H_
#define H_OPERATOR_H_

class Operator{

   public:
   void* far operator new(unsigned int size);
   void far operator delete(void* block);
   };


#endif /* H_OPERATOR_H_ */
