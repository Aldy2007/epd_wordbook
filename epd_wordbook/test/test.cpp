#include <Arduino.h>
#include <unity.h>

void setUp(void)
{
    // 这是每个测试之前运行的代码
}

void tearDown(void)
{
    // 这是每个测试之后运行的代码
}

void test_led_builtin_pin_number(void)
{
    
}

void test_led_state_high(void)
{
  
}

void setup()
{
    UNITY_BEGIN(); // 初始化 Unity 测试框架

    RUN_TEST(test_led_builtin_pin_number); // 运行第一个测试
    RUN_TEST(test_led_state_high);         // 运行第二个测试

    UNITY_END(); // 结束 Unity 测试
}

void loop()
{
    // 空
}
