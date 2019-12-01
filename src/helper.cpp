#include <helper.h>

// Initiator
Helper::Helper(CALLBACK_SIGNATURE)
{
 this->callback = callback;
}

// char * strtok ( char * str, const char * delimiters );
void Helper::SplitString(const char* str, const char* delimiters)
{
  InputCounter = 0;
  char* pos;
  pos = strtok((char*) str, delimiters);
  while (pos != NULL)
  {
    InputCounter++;
    callback(pos);
    pos = strtok(NULL, delimiters);
  }
  return;
}
