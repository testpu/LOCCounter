#include <cppunit/CompilerOutputter.h>
#include <cppunit/XMLOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char* argv[])
{
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);

    std::ofstream output;
    if (argc > 1 && std::string("/outputter:xml") == argv[1])
    {
        if (argc > 2)
        {
            output.open(argv[2]);
            runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), output));
        }
        else
        {
            runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(), std::cerr));
        }
    }
    else
    {
        // Change the default outputter to a compiler error format outputter
        runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    }
    // Run the tests.
    bool wasSucessful = runner.run();

    output.close();
    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}