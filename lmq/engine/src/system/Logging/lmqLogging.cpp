#ifdef ARDUINO
#include "platform/arduino/lmqLogging.include"
#else // ARDUINO
#error "The logging is not implemented for the platform"
#endif // !ARDUINO