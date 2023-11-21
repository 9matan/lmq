#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO
#include <unity.h>

#include "lmq/core/lmqLerp.h"

void setUp(void) {}
void tearDown(void) {}

void lmqMapValue_TestCase(const long inVal
                        , const long inMin
                        , const long inMax
                        , const long outMin
                        , const long outMax
                        , const long expectedOutVal
                        , const char* description = "")
{
    const long outVal = lmqMapValue(inVal, inMin, inMax, outMin, outMax);
    TEST_ASSERT_EQUAL_INT_MESSAGE(expectedOutVal, outVal, description);
}

void lmqMapValue_PositiveValuesEqRangesLengths()
{
    lmqMapValue_TestCase(1, 1, 2, 15, 16, 15, "Range length 1");
    lmqMapValue_TestCase(250, 245, 255, 10, 20, 15, "Range length 10");
}

void lmqMapValue_PositiveValuesNotEqRangesLengths1024And256()
{
    lmqMapValue_TestCase(1026, 1024, 2048, 256, 512, 256, "1026->256");
    lmqMapValue_TestCase(1027, 1024, 2048, 256, 512, 256, "1027->256");
    lmqMapValue_TestCase(1028, 1024, 2048, 256, 512, 257, "1028->257");

    lmqMapValue_TestCase(256, 256, 512, 1024, 2048, 1024, "256->1024");
    lmqMapValue_TestCase(257, 256, 512, 1024, 2048, 1028, "257->1028");
    lmqMapValue_TestCase(512, 256, 512, 1024, 2048, 2048, "512->2048");
}

void lmqMapValue_PositiveNegativeValuesEqRangesLengths()
{
    lmqMapValue_TestCase(-29, -40, -20, 120, 140, 131, "Range length 20");
    lmqMapValue_TestCase(0, -70, 140, -140, 70, -70, "Range length 210");
}

void lmqMapValue_PositiveNegativeValuesNotEqRangesLengths10And70()
{
    lmqMapValue_TestCase(131, 131, 201, -23, -13, -23, "131->-23");
    lmqMapValue_TestCase(137, 131, 201, -23, -13, -23, "137->-23");
    lmqMapValue_TestCase(138, 131, 201, -23, -13, -22, "138->-22");
    lmqMapValue_TestCase(144, 131, 201, -23, -13, -22, "144->-22");
    lmqMapValue_TestCase(145, 131, 201, -23, -13, -21, "145->-21");

    lmqMapValue_TestCase(-20, -23, -13, 131, 201, 152, "-20->152");
    lmqMapValue_TestCase(-14, -23, -13, 131, 201, 194, "-14->194");
}

void lmqMapValue_PositiveNegativeValuesInverseRanges()
{
    lmqMapValue_TestCase(-7, -10, 20, 20, -10, 17, "Equal ranges lengths");
    lmqMapValue_TestCase(122, 125, 100, 70, 80, 71, "Not equal ranges lengths");

    lmqMapValue_TestCase(2, 1, 2, 1, 10, 10);
}

void lmqMapValue_PositiveNegativeRangeLength1()
{
    lmqMapValue_TestCase(10, 10, 10, 56, 125, 56, "In range length 1");
    lmqMapValue_TestCase(56, 125, 100, -10, -10, -10, "Out range length 1");
}

void lmqMapValueTests()
{
    RUN_TEST(lmqMapValue_PositiveValuesEqRangesLengths);
    RUN_TEST(lmqMapValue_PositiveValuesNotEqRangesLengths1024And256);
    RUN_TEST(lmqMapValue_PositiveNegativeValuesEqRangesLengths);
    RUN_TEST(lmqMapValue_PositiveNegativeValuesNotEqRangesLengths10And70);
    RUN_TEST(lmqMapValue_PositiveNegativeValuesInverseRanges);
    RUN_TEST(lmqMapValue_PositiveNegativeRangeLength1);
}

#ifdef ARDUINO
void loop(){}

void setup()
#else // ARDUINO
int main(int argc, char **argv)
#endif // !ARDUINO
{
#ifdef ARDUINO
    Serial.begin(115200);
#endif // ARDUINO

    UNITY_BEGIN();
    
    lmqMapValueTests();

    UNITY_END();
}