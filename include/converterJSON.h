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
     * Проверяет наличие файла config.json
    */
    bool configCheck ();
    
    /**
    * Метод чтения json файлов.
    * @param filePath На вход подается ссылка на строку std::string, где содержится путь к файлу.
    * @return Возвращает содежимое файла в переменную nlohmann::json
    */
    nlohmann::json readJsonFile(const std::string &filePath);

    /**
    * Метод получения содержимого файлов перечисленных в config.json
    * @return Возвращает вектор с содержимым файлов 
    */
    std::vector<std::string> GetTextDocuments();

    /**
    * Метод для определения предельного количества ответов на один запрос
    * @return возвращает содержимое поля max_responses из config.json
    */
    int GetResponsesLimit();

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает вектор содержащий запросы из файла requests.json
    */
    std::vector<std::string> GetRequests();

    /**
    * Метод записывает в файл answers.json результаты поисковых запросов
    * @param вектор с результатами 
    */
    void putAnswers(std::vector<std::vector<RelativeIndex>>answers);
};