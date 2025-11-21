#
# This makefile is only used for my library compilation!
#

CXX = g++
CXXFLAGS = -Wall -m64 -mtune=native -march=native -O3 -DLINUX_SYSTEM

TARGET_TESTER = /home/nullinferno/projects/NullInfernoCore/tester
SRCS_TESTER = tester.cpp validity_tests.cpp performance_tests.cpp
HEADERS_TESTER = NullInfernoCore

TARGET_LIB = /home/nullinferno/projects/NullInfernoCore/libNullInfernoCore.a

SRCS_LIB = TEnvironment.cpp \
			TStopwatch.cpp \
			CommonFunctions.cpp \

OBJDIR = /home/nullinferno/projects/NullInfernoCore/objs
OBJS_LIB = $(SRCS_LIB:%.cpp=$(OBJDIR)/%.o)
DEPS_LIB = $(SRCS_LIB:%.cpp=$(OBJDIR)/%.d)


all: $(TARGET_LIB) $(TARGET_TESTER)

$(TARGET_LIB): $(OBJS_LIB)
	ar rcs $@ $^

$(OBJDIR)/%.o: NullInfernoCore/%.cpp
	@echo "Compile $< -> $@"
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS_LIB)

$(TARGET_TESTER):
	$(CXX) $(CXXFLAGS) tester/tester.cpp tester/validity_tests.cpp tester/performance_tests.cpp -I$(HEADERS_TESTER) -L/home/nullinferno/projects/NullInfernoCore -o $(TARGET_TESTER) -lNullInfernoCore

clean:
	rm -f $(TARGET_LIB) $(TARGET_TESTER) $(OBJS_LIB) $(DEPS_LIB)
