#include <iostream>
#include "converterJSON.h"

nlohmann::json ConverterJSON::readJsonFile(const std::string &filePath) {
    
    nlohmann::json buffer;
    std::ifstream jsonFile("../" + filePath);
    
    if (jsonFile.is_open()) {
        jsonFile>>buffer;
    } else {
        std::cerr << filePath<<" file is missing" << std::endl;
    }

    jsonFile.close();
    return buffer;

};


std::vector<std::string> ConverterJSON::GetTextDocuments() {
	// Объявляем JSON-словарь, и присваиваем ему извлечённое содержимое файла "config.json"
	nlohmann::json config = readJsonFile("config.json");

	// Создаёт вектор строк для сохранения конкретных строк
	std::vector<std::string> docFilePathList, docTextList;

	// В цикле добавляем в вектор нужные строки из ветки "files"
	for (const auto& it : config["files"]) {
		std::ifstream docFile("../" + std::string(it));
		if (!docFile.is_open()) {
			std::cout << "Wrong Path " << "../" + std::string(it) <<
			" or file doesn't exist!" << std::endl;
			break;
		} else {
			std::string text;
			while (getline(docFile, text));
			
			docFile.close();
			docTextList.push_back(text);
		}
	}

	// Возвращает вектор содержимого файлов
	return docTextList;
}

int ConverterJSON::GetResponsesLimit() {
	
	nlohmann::json config = readJsonFile("config.json");
	return config["config"]["max_responses"];

}

std::vector<std::string> ConverterJSON::GetRequests() {

	nlohmann::json requests = readJsonFile("requests.json");
	std::vector<std::string> requestsList;

	for (const auto& ell : requests["requests"]) {
		requestsList.push_back(ell);
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