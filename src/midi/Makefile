default_sources = app.cpp easylogging++.cpp logging.cpp tests/tests.cpp 
current_sources := $(default_sources) tests/02-midi/01-primitives/05-time-tests.cpp
current_objects := $(patsubst %.cpp, %.o, $(current_sources))
current_deps := $(current_objects:.o=.d)

current_tests.out: $(current_objects)
	g++ -o current_tests.out $(current_objects)

-include $(current_deps)

%.o: %.cpp
	g++ -I. -DTEST_BUILD -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< 

clean:
	$(RM) $(current_objects)
	$(RM) $(current_deps)
	$(RM) current_tests

autorun:
	entr -s 'date; sleep 0.5; ./current_tests' <<< current_tests

define cumul_sources
	$(default_sources) \
	io/endianness.cpp \
	io/vli.cpp \
	tests/01-io/01-endianness-tests.cpp \
	tests/01-io/02-read-to-tests.cpp \
	tests/01-io/03-read-tests.cpp \
	tests/01-io/04-read-array-tests.cpp \
	tests/01-io/05-read-variable-length-integer-tests.cpp \
	tests/02-midi/01-primitives/01-channel-tests.cpp \
	tests/02-midi/01-primitives/02-channel-show-tests.cpp
	tests/02-midi/01-primitives/03-instruments-tests.cpp \
	tests/02-midi/01-primitives/04-note-number-tests.cpp \
	tests/02-midi/01-primitives/05-time-tests.cpp
endef

cumul_objects := $(patsubst %.cpp, %.o, $(cumul_sources))
cumul_deps := $(cumul_objects:.o=.d)

cumul_tests.out: $(cumul_objects)
	g++ -o cumul_tests.out $(cumul_objects)

.PHONY: autorun clean
