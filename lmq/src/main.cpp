#ifdef ARDUINO
#include "platform/main_arduino.include"
#else // ARDUINO
#error "The entry point is not implemented for the platform"
#endif // !ARDUINO