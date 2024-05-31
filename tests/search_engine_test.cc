#include "InvertedIndex.h"
#include "searchServer.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(sample_test_case, sample_test)
{
	EXPECT_EQ(1+2, 3);
}


void TestInvertedIndexFunctionality(const std::vector<std::string>& docs,
									const std::vector<std::string>& requests,
									const std::string& expected) {
	std::string result;
	InvertedIndex idx;
	idx.updateDocumentBase(docs);

	for(auto request : requests) {
		result+=request;
		std::vector<Entry> word_count = idx.getWordCount(request);
		
		std::sort(begin(word_count),end(word_count), [](Entry a, Entry b){

                return (a.docId < b.docId);

            });

		for (auto& ell:word_count){
			result+='('+std::to_string(ell.docId)+','+ std::to_string(ell.count)+')';
		}
	}

	ASSERT_EQ(result,expected);
}

void TestSearchServerFunctionality(const std::vector<std::string>& docs,
									const std::vector<std::string>& requests,
									const std::string& expected) {
	std::string result;
	InvertedIndex idx;
	idx.updateDocumentBase(docs);

	SearchServer srv(idx);
	std::vector<std::vector<RelativeIndex>> answers = srv.search(requests,5);

	for(auto answer : answers) {
		result+='[';

		for (auto& ell:answer){
			result+='('+std::to_string(ell.docId)+','+ std::to_string(ell.rank)+')';
		}
		result+=']';
	}

	ASSERT_EQ(result,expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
	const std::vector<std::string> docs = {
		"london is the capital of great britain",
		"big ben is the nickname for the Great bell of the striking clock"
	};
	const std::vector<std::string> requests = {"london", "the"};
	const std::string expected = "london(0,1)the(0,1)(1,3)";
	TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
	const std::vector<std::string> docs = {
		"milk milk milk milk water water water",
		"milk water water",
		"milk milk milk milk milk water water water water water",
		"americano cappuccino"
	};
	const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
	const std::string expected ="milk(0,4)(1,1)(2,5)water(0,3)(1,2)(2,5)cappuccino(3,1)";
	TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
	const std::vector<std::string> docs = {
		"a b c d e f g h i j k l",
		"statement"
	};
	const std::vector<std::string> requests = {"m", "statement"};
	const std::string expected = "mstatement(1,1)";
	TestInvertedIndexFunctionality(docs, requests, expected);
}


TEST(TestCaseSearchServer, TestSimple) {
	const std::vector<std::string> docs = {
		"milk milk milk milk water water water",
		"milk water water",
		"milk milk milk milk milk water water water water water",
		"americano cappuccino"
	};
	const std::vector<std::string> request = {"milk water", "sugar"};
	const std::string expected = "[(2,1.000000)(0,0.700000)(1,0.300000)][]";
	TestSearchServerFunctionality(docs,request,expected);

}

TEST(TestCaseSearchServer, TestTop5) {
	const std::vector<std::string> docs = {
		"london is the capital of great britain",
		"paris is the capital of france",
		"berlin is the capital of germany",
		"rome is the capital of italy",
		"madrid is the capital of spain",
		"lisboa is the capital of portugal",
		"bern is the capital of switzerland",
		"moscow is the capital of russia",
		"moscow is the capital of our homeland",
		"minsk is the capital of belarus",
		"astana is the capital of kazakhstan",
		"beijing is the capital of china",
		"tokyo is the capital of japan",
		"bangkok is the capital of thailand",
		"welcome to moscow the capital of russia the third rome",
		"amsterdam is the capital of netherlands",
		"helsinki is the capital of finland",
		"oslo is the capital of norway",
		"stockholm is the capital of sweden",
		"riga is the capital of latvia",
		"tallinn is the capital of estonia",
		"st. petersburg is the northern capital of russia",
	};
	const std::vector<std::string> request = {"moscow is the capital of russia"};
	const std::string expected = "[(7,1.000000)(14,1.000000)(21,0.833333)(8,0.833333)(11,0.666667)]";
	TestSearchServerFunctionality(docs,request,expected);
}

int main(int args, char** argv) {
	testing::InitGoogleTest(&args, argv);
	return RUN_ALL_TESTS();
}