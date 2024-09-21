add_test([=[HelloTest.BasicAssertions]=]  /home/orlab/Documents/MinhVD/PFS/tsp/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/orlab/Documents/MinhVD/PFS/tsp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)
