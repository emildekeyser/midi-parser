default_sources = app.cpp easylogging++.cpp logging.cpp tests/tests.cpp 
current_sources := $(default_sources) \
	tests/02-midi/05-notes/02-channel-note-collector-tests.cpp

current_objects := $(patsubst %.cpp, %.o, $(current_sources))
current_deps := $(current_objects:.o=.d)

current_tests.out: $(current_objects)
	g++ -o current_tests.out $(current_objects)

-include $(current_deps)

%.o: %.cpp
	g++ -I. -DTEST_BUILD -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< 

autorun:
	entr -s 'date; sleep 0.5; ./current_tests.out' <<< current_tests.out

define cumul_sources
	$(default_sources) \
	io/endianness.cpp \
	io/vli.cpp \
	tests/01-io/01-endianness-tests.cpp \
	tests/01-io/02-read-to-tests.cpp \
	tests/01-io/03-read-tests.cpp \
	tests/01-io/04-read-array-tests.cpp \
	tests/01-io/05-read-variable-length-integer-tests.cpp \
	midi/time.cpp \
	tests/02-midi/01-primitives/01-channel-tests.cpp \
	tests/02-midi/01-primitives/02-channel-show-tests.cpp \
	tests/02-midi/01-primitives/03-instruments-tests.cpp \
	tests/02-midi/01-primitives/04-note-number-tests.cpp \
	tests/02-midi/01-primitives/05-time-tests.cpp \
	midi/chunk-header.cpp \
	tests/02-midi/02-chunk-headers/01-chunk-header-tests.cpp \
	tests/02-midi/03-mthd/01-mthd-tests.cpp \
	midi/mthd.cpp \
	tests/02-midi/03-mthd/02-read-mthd-tests.cpp \
	midi/mtrk.cpp \
	tests/02-midi/04-mtrk/01-mtrk-auxiliary-tests.cpp \
	tests/02-midi/04-mtrk/02-mtrk-event-receiver-tests.cpp \
	midi/read-mtrk.cpp \
	tests/02-midi/04-mtrk/03-mtrk-empty-tests.cpp \
	tests/02-midi/04-mtrk/04-mtrk-meta-tests.cpp \
	tests/02-midi/04-mtrk/05-mtrk-sysex-tests.cpp \
	tests/02-midi/04-mtrk/06-mtrk-note-off-tests.cpp \
	tests/02-midi/04-mtrk/07-mtrk-note-on-tests.cpp \
	tests/02-midi/04-mtrk/08-mtrk-polyphonic-tests.cpp \
	tests/02-midi/04-mtrk/09-mtrk-control-change-tests.cpp \
	tests/02-midi/04-mtrk/10-mtrk-program-change-tests.cpp \
	tests/02-midi/04-mtrk/11-mtrk-channel-pressure-tests.cpp \
	tests/02-midi/04-mtrk/12-mtrk-pitch-wheel-tests.cpp \
	tests/02-midi/04-mtrk/13-mtrk-multiple-events-tests.cpp \
	tests/02-midi/05-notes/01-note-tests.cpp
endef

cumul_objects := $(patsubst %.cpp, %.o, $(cumul_sources))
cumul_deps := $(cumul_objects:.o=.d)

cumul_tests.out: $(cumul_objects)
	g++ -o cumul_tests.out $(cumul_objects)

clean:
	$(RM) $(current_objects)
	$(RM) $(current_deps)
	$(RM) $(cumul_objects)
	$(RM) $(cumul_deps)
	$(RM) current_tests.out cumul_tests.out

.PHONY: autorun clean
