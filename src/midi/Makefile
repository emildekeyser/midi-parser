help:
	@echo '       :::    ::: :::::::::: :::        ::::::::: '
	@echo '      :+:    :+: :+:        :+:        :+:    :+: '
	@echo '     +:+    +:+ +:+        +:+        +:+    +:+  '
	@echo '    +#++:++#++ +#++:++#   +#+        +#++:++#+    '
	@echo '   +#+    +#+ +#+        +#+        +#+           '
	@echo '  #+#    #+# #+#        #+#        #+#            '
	@echo ' ###    ### ########## ########## ###             '
	@echo
	@echo 'Take a look inside the Makefile and comment/delete this helptext to start using it.'
	@echo
	@echo '$$ make ==> compile "current sources" into midi.out binary.'
	@echo
	@echo '$$ make autorun ==> watch midi.out with entr for recompilation and run it (easy way to quickly check your tests).'
	@echo
	@echo 'IMPORTANT: comment toggle the g++ command in the .cpp to .o target when you start implementing rendering (you are not making a test build at that point).'
	@echo
	@echo 'ALSO IMPORTANT: check that you always add all needed .cpp files to "current sources" otherwise you will get weird linker errors.'
	@echo
	@echo 'ALSO IMPORTANT: run make clean when switching between TEST_BUILD and the rendering build.'
	@echo
	@echo 'TIP: when you finish with a set of tests, move all .cpp files involved to the "cumul sources" variable. This unlocks the ability to do regression testing once in a while.'
	@echo
	@echo 'NOTE: .d, .o and .out files are gitignored by default.'

# Why ?
# This makefile is designed to efficiently (re)build just the part of the sources needed.
# We do this by using .d and .o files stored in the cache directory.
# It is a bit complex and could be simplified slightly by not using a cache directory.
# Using the cache directory unclutters the source directories though, so it is very nice imo.
# If anyone has a better (simpler) way to do this I would be very interested to know about it.
# emildekeyser@protonmail.ch

current_sources := easylogging++.cpp logging.cpp tests/tests.cpp \
	app.cpp \
	io/endianness.cpp \
	tests/01-io/01-endianness-tests.cpp

current_objects := $(patsubst %.cpp, cache/%.o, $(current_sources))
current_deps := $(current_objects:.o=.d)

midi.out: $(current_objects)
	g++ -o midi.out $(current_objects)

-include $(current_deps)

cache/%.o: %.cpp
	@$(create_cache_dirs)
	@# g++ -I. -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< 
	g++ -I. -DTEST_BUILD -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< 

autorun:
	entr -s 'date; sleep 0.5; ./midi.out' <<< midi.out

define cumul_sources
	app.cpp easylogging++.cpp logging.cpp tests/tests.cpp \
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
	tests/02-midi/05-notes/01-note-tests.cpp \
	midi/channel-note-collector.cpp \
	tests/02-midi/05-notes/02-channel-note-collector-tests.cpp \
	midi/event-multicaster.cpp \
	midi/note-collector.cpp \
	tests/02-midi/05-notes/03-event-multicaster-tests.cpp \
	tests/02-midi/05-notes/04-note-collector-tests.cpp \
	midi/read-notes.cpp \
	tests/02-midi/05-notes/05-read-notes-tests.cpp
endef

cumul_objects := $(patsubst %.cpp, %.o, $(cumul_sources))
cumul_deps := $(cumul_objects:.o=.d)

cumul_tests.out: $(cumul_objects)
	g++ -o cumul_tests.out $(cumul_objects)

render:
	# ./midi.out
	mkdir -p outimg
	ffmpeg -pattern_type glob -i 'outimg/*.bmp' -c:v libx264 -r 30 -pix_fmt yuv420p movie.mp4

# Creates clone of directory structure in cache needed for neat creation ov .d and .o files
create_cache_dirs = [ -d cache ] || find -type d | sed 's/\./cache/' | xargs mkdir -p

clean:
	rm -rf cache
	$(RM) midi.out cumul_tests.out

.PHONY: autorun clean render
