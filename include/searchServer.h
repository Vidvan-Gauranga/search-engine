#pragma once
#include <set>
#include "converterJSON.h"
#include "invertedIndex.h"

class SearchServer {

    InvertedIndex index;

public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
    */
    SearchServer(InvertedIndex& idx) : index(idx){ };

    std::set<std::string> getUniqueWord(std::string &query);
    /**
    * Метод обработки поисковых запросов
    * @param queries поисковые запросы взятые из файла
    requests.json
    * @return возвращает отсортированный список релевантных ответов для заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search( const std::vector<std::string>& queries, 
                                                    const int& responsesLimit);
};