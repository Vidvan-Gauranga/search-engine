#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

struct RelativeIndex {
    size_t docId;
    float rank;

	RelativeIndex(size_t _docId, float _rank): docId(_docId),rank(_rank){}
	~RelativeIndex() = default; 
};

class ConverterJSON
{
public:
    ConverterJSON() = default;
    ~ConverterJSON() = default;

    /**
    * Метод чтения json файлов.
    * @param filePath На вход подается ссылка на строку, где содержится путь к файлу.
    * @return Возвращает переменную nlohmann::json
    */
    nlohmann::json readJsonFile(const std::string &filePath);

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> GetTextDocuments();
    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit();
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests();
    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(std::vector<std::vector<RelativeIndex>>answers);
};