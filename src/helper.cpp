#include <helper.h>

// Initiator
Helper::Helper(CALLBACK_SIGNATURE)
{
  this->callback = callback;
}

/*
void Helper::SplitString(const char *str, const char *delimiters)
{
  InputCounter = 0;
  char *pos;
  pos = strtok((char *)str, delimiters);
  while (pos != NULL)
  {
    InputCounter++;
    callback(pos);
    pos = strtok(NULL, delimiters);
  }
  return;
}
*/

void Helper::SplitStream(fs::File &stream)
{
  InputCounter = 0;
  char buffer[INPUTBUFFER];
  size_t bytesRead = 0;

  bytesRead = stream.readBytesUntil('\n', buffer, INPUTBUFFER);
  while (bytesRead != 0)
  {
    buffer[bytesRead] = '\0';
    InputCounter++;
    callback(buffer);
    bytesRead = stream.readBytesUntil('\n', buffer, INPUTBUFFER);
  }
  return;
}
