#include <functional>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "../MacroUtil.hpp"
#include "../MathUtil.hpp"
#include "../StringUtil.hpp"

//the amount of times we test each case
#define TEST_CYCLES 10
//the highest float generated by the random number generator
#define TOP_FLOAT 100000.0

//------------------------------------------------------------------------------
//                                   PROTOTYPES
//------------------------------------------------------------------------------

/**Repeats a lambda for the amount of test cycles we are using
@param f the lambda to repeat*/
void test(std::function<void ()> f);

/**Prints a title for the current test module
@param text the text of the title*/
void printTitle(std::string text);

/**Generates a random float
@return the random float*/
float generateFloat();

//------------------------------------------------------------------------------
//                                 TEST FUNCTIONS
//------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(math_util_tests) {

    //seed the random number generator
    srand(time(0));

    printTitle("Testing Math Utilities");

    //CLAMP
    //below clamp
    test([] () {

        float lowerBound = generateFloat();
        float upperBound = generateFloat();
    });
}

BOOST_AUTO_TEST_CASE(string_util_tests) {

    printTitle("Testing String Utilities");
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void test(std::function<void ()> f) {

    for (unsigned i = 0; i < TEST_CYCLES; ++i) {

        f();
    }
}

void printTitle(std::string text) {

    //generate the border
    std::string dashLine(util::str::generateRepeat("-", 80));

    //centre the text of the title
    util::str::centre(text, 80);

    //print out the title block
    std::cout << "\n" << dashLine << std::endl;
    std::cout << text << std::endl;
    std::cout << dashLine << "\n" << std::endl;
}

float generateFloat() {

    return (static_cast<float>(rand()) /
        (static_cast<float>(RAND_MAX / TOP_FLOAT))) - (TOP_FLOAT / 2.0);
}
