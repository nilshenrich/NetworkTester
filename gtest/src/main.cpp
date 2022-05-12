#include <gtest/gtest.h>

#include "HelperFunctions.h"

using namespace std;

// Handle SIGPIPE
void sigpipe_handler(int)
{
    // Set pipe error flag
    HelperFunctions::setPipeError();
    return;
}

int main(int argc, char **argv)
{
    // Set SIGPIPE handler
    signal(SIGPIPE, sigpipe_handler);

    // Run tests
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
