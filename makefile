#
# This makefile is only used for my own compilation!
#

CXX = g++
CXXFLAGS = -Wall -m64 -mtune=native -march=native -O3 -DLINUX_SYSTEM

OBJS_LIB_DIR = objs/NullInfernoCore
SRCS_LIB_DIR = /mnt/z/Development/Projects/sources/NullInfernoCore/NullInfernoCore_Solution/NullInfernoCore
HEADER_LIB_DIR = /mnt/z/Development/Projects/sources/NullInfernoCore/NullInfernoCore_Solution/NullInfernoCore
TARGET_LIB = libNullInfernoCore.a

OBJS_TESTER_DIR = objs/tester
TARGET_TESTER = tester
SRCS_TESTER_DIR = /mnt/z/Development/Projects/sources/NullInfernoCore/NullInfernoCore_Solution/tester


$(TARGET_LIB):
	@echo " "
	@echo "------------------------------------------------------------------"
	@echo "Build library NullInfernoCore"
	@echo "------------------------------------------------------------------"
	@echo " "

	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TEnvironment.cpp -o $(OBJS_LIB_DIR)/TEnvironment.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TStopwatch.cpp -o $(OBJS_LIB_DIR)/TStopwatch.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/CommonFunctions.cpp -o $(OBJS_LIB_DIR)/CommonFunctions.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TString.cpp -o $(OBJS_LIB_DIR)/TString.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TList.cpp -o $(OBJS_LIB_DIR)/TList.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TStringList.cpp -o $(OBJS_LIB_DIR)/TStringList.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TBytes.cpp -o $(OBJS_LIB_DIR)/TBytes.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TParamsList.cpp -o $(OBJS_LIB_DIR)/TParamsList.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TDateTime.cpp -o $(OBJS_LIB_DIR)/TDateTime.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TStream.cpp -o $(OBJS_LIB_DIR)/TStream.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TMemoryStream.cpp -o $(OBJS_LIB_DIR)/TMemoryStream.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TBinaryWriter.cpp -o $(OBJS_LIB_DIR)/TBinaryWriter.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TBinaryReader.cpp -o $(OBJS_LIB_DIR)/TBinaryReader.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TCommandLineParser.cpp -o $(OBJS_LIB_DIR)/TCommandLineParser.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TFileStream.cpp -o $(OBJS_LIB_DIR)/TFileStream.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_LIB_DIR)/TFileSystem.cpp -o $(OBJS_LIB_DIR)/TFileSystem.o
	ar rcs $(TARGET_LIB) $(OBJS_LIB_DIR)/*.o

$(TARGET_TESTER):
	@echo " "
	@echo "------------------------------------------------------------------"
	@echo "Build tester for NullInfernoCore"
	@echo "------------------------------------------------------------------"
	@echo " "

	$(CXX) $(CXXFLAGS) -c $(SRCS_TESTER_DIR)/validity_tests.cpp -I$(HEADER_LIB_DIR) -o $(OBJS_TESTER_DIR)/validity_tests.o
	$(CXX) $(CXXFLAGS) -c $(SRCS_TESTER_DIR)/performance_tests.cpp -I$(HEADER_LIB_DIR) -o $(OBJS_TESTER_DIR)/performance_tests.o
	$(CXX) $(CXXFLAGS) $(SRCS_TESTER_DIR)/tester.cpp -I$(HEADER_LIB_DIR) -L. -o $(TARGET_TESTER) $(OBJS_TESTER_DIR)/*.o -lNullInfernoCore

.PHONY: clean all lib tester clean_lib clean_tester

all: $(TARGET_LIB) $(TARGET_TESTER)

lib: $(TARGET_LIB)

tester: $(TARGET_TESTER)

clean:
	rm -f $(TARGET_LIB) $(TARGET_TESTER) $(OBJS_LIB_DIR)/*.o $(OBJS_TESTER_DIR)/*.o

clean_lib:
	rm -f $(TARGET_LIB) $(OBJS_LIB_DIR)/*.o

clean_tester:
	rm -f $(TARGET_TESTER) $(OBJS_TESTER_DIR)/*.o
