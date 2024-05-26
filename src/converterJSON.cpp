#include <iostream>
#include "converterJSON.h"

bool ConverterJSON::configCheck(){
	
	return !readJsonFile("config.json").empty();
};


nlohmann::json ConverterJSON::readJsonFile(const std::string &filePath) {
    
    nlohmann::json buffer;
    std::ifstream jsonFile("../" + filePath);
    
    if (jsonFile.is_open()) {
        jsonFile>>buffer;
    } else {
        std::cerr << "Error! File ../"<<filePath <<" is missing" << std::endl;
    }
    jsonFile.close();
    return buffer;
};


std::vector<std::string> ConverterJSON::GetTextDocuments() {

	nlohmann::json config = readJsonFile("config.json");
	std::vector<std::string> docTextList;

	for (const auto& fileName : config["files"]) {
		std::ifstream docFile("../" + std::string(fileName));
		if (!docFile.is_open()) {
			std::cerr << "Invalid path ../" 
					  << std::string(fileName) 
					  << " or there is no such file!" 
					  << std::endl;
		} else {
			std::string text;
			while (getline(docFile, text));
			docFile.close();
			docTextList.push_back(text);
		}
	}
	return docTextList;
}


int ConverterJSON::GetResponsesLimit() {
	
	nlohmann::json config = readJsonFile("config.json");
	return config["config"]["max_responses"];

}


std::vector<std::string> ConverterJSON::GetRequests() {

	nlohmann::json requests = readJsonFile("requests.json");
	std::vector<std::string> requestsList;

	for (const auto& request : requests["requests"]) {
		requestsList.push_back(request);
	}
	
	return requestsList;
}


void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>>answers) {

    std::ofstream file ("answers.json");
	nlohmann::json answersJSON;
	size_t requestCount=1;

	for (auto answer:answers){

		std::string requestNumber = "request_"+std::to_string(requestCount);

		if (answer.empty()){

			answersJSON["answers"][requestNumber]["result"]=false;

		} else {

			answersJSON["answers"][requestNumber]["result"]=true;

			nlohmann::json answersList;
			for (auto relevantDoc:answer){
				nlohmann::json data ={
					{"docid", relevantDoc.docId},
					{"rank", relevantDoc.rank}
				};
				answersList.push_back(data);
			}

			if (answer.size()==1){
				answersJSON["answers"][requestNumber]=answersList;
			} else {
				answersJSON["answers"][requestNumber]["relevance"]=answersList;
			}

		}
		
		requestCount++;

	}

	file << answersJSON;
	file.close();
}