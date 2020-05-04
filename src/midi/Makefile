current_files = tests/02-midi/01-primitives/02-channel-show-tests.cpp

current:
	g++ -I. -DTEST_BUILD app.cpp easylogging++.cpp logging.cpp tests/tests.cpp $(current_files)

autorun:
	entr -s 'date; sleep 0.5; ./a.out' <<< a.out

cumul_tests:
	g++ -I. -DTEST_BUILD app.cpp easylogging++.cpp logging.cpp tests/tests.cpp \

io/endianness.cpp
io/vli.cpp

tests/01-io/01-endianness-tests.cpp
tests/01-io/02-read-to-tests.cpp
tests/01-io/03-read-tests.cpp
tests/01-io/04-read-array-tests.cpp
tests/01-io/05-read-variable-length-integer-tests.cpp
		tests/02-midi/01-primitives/01-channel-tests.cpp \
		tests/02-midi/01-primitives/02-channel-show-tests.cpp
