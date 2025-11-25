#
# This makefile is only used for my library compilation!
#

CXX = g++
CXXFLAGS = -Wall -m64 -mtune=native -march=native -O3 -DLINUX_SYSTEM

TARGET_TESTER = /home/nullinferno/projects/NullInfernoCore/tester
SRCS_TESTER = validity_tests.cpp performance_tests.cpp
HEADERS_TESTER = NullInfernoCore

TARGET_LIB = /home/nullinferno/projects/NullInfernoCore/libNullInfernoCore.a

SRCS_LIB = TEnvironment.cpp \
			TStopwatch.cpp \
			CommonFunctions.cpp \
			TString.cpp \
			TList.cpp \
			TBytes.cpp \
			TParamsList.cpp \
			TDateTime.cpp

OBJDIR = /home/nullinferno/projects/NullInfernoCore/objs
OBJDIR_TESTER = /home/nullinferno/projects/NullInfernoCore/objs
OBJS_LIB = $(SRCS_LIB:%.cpp=$(OBJDIR)/%.o)
DEPS_LIB = $(SRCS_LIB:%.cpp=$(OBJDIR)/%.d)

OBJS_TESTER = $(SRCS_TESTER:%.cpp=$(OBJDIR)/%.o)
DEPS_TESTER = $(SRCS_TESTER:%.cpp=$(OBJDIR)/%.d)

all: $(TARGET_LIB) $(TARGET_TESTER)

$(TARGET_LIB): $(OBJS_LIB)
	ar rcs $@ $^

$(OBJDIR)/%.o: NullInfernoCore/%.cpp
	@echo "Compile $< -> $@"
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/validity_tests.o: tester/validity_tests.cpp
	@echo "Compile $< -> $@"
	$(CXX) $(CXXFLAGS) -I$(HEADERS_TESTER) -MMD -MP -c $< -o $@
$(OBJDIR)/performance_tests.o: tester/performance_tests.cpp
	@echo "Compile $< -> $@"
	$(CXX) $(CXXFLAGS) -I$(HEADERS_TESTER) -MMD -MP -c $< -o $@

-include $(DEPS_LIB)
-include $(DEPS_TESTER)

$(TARGET_TESTER): $(OBJS_TESTER)
	$(CXX) $(CXXFLAGS) tester/tester.cpp -I$(HEADERS_TESTER) -L/home/nullinferno/projects/NullInfernoCore -o $(TARGET_TESTER) $(OBJS_TESTER) -lNullInfernoCore

clean:
	rm -f $(TARGET_LIB) $(TARGET_TESTER) $(OBJS_LIB) $(DEPS_LIB)
