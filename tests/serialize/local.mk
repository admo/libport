TESTS_BINARIES +=				\
  tests/serialize/serialize.cc

tests_serialize_serialize_SOURCES = tests/serialize/serialize.cc
tests_serialize_serialize_LDFLAGS = $(SERIALIZE_LIBS) $(AM_LDFLAGS)

CHECK_CLEANFILES +=				\
  tests/serialize/test.bin			\
  tests/serialize/test.xml
