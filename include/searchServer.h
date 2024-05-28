#pragma once
#include <set>
#include "converterJSON.h"
#include "invertedIndex.h"

class SearchServer {

    InvertedIndex index;

    /**
    * Метод возвращает список уникальных слов из запроса
    */
    std::set<std::string> getUniqueWord(std::string &query);

    /**
    * Метод расчета абсолютной релевантности по запросу
    */
    void calcAbsoluteRelevance (std::map<size_t,size_t>& absRel, 
                                std::string& querie, 
                                size_t& maxRel);

    /**
    * Метод расчета относительной релевантности по запросу
    */                            
    void calcRelativeRelevance (std::vector<RelativeIndex>& queryResults,
                                std::map<size_t,size_t>& absRel,
                                size_t& maxRel);
public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
    */
    SearchServer(InvertedIndex& idx) : index(idx){ };

    /**
    * Метод обработки поисковых запросов
    * @param queries поисковые запросы взятые из файла
    requests.json
    * @return возвращает отсортированный список релевантных ответов для заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search( const std::vector<std::string>& queries, 
                                                    const int& responsesLimit);
};