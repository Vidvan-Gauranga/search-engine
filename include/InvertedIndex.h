#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>
#include <thread>
#include <mutex>
#include "converterJSON.h"

/**
 * docId - id документа
 * count - колличество вхождений слова в документе
*/
struct Entry {
	size_t docId, count;
	
	Entry(size_t _docId, size_t _count): docId(_docId),count(_count){}
	~Entry() = default; 

};

class InvertedIndex {
	/**
	 * Частотный словарь уникальных слов
	*/
	std::map<std::string, std::vector<Entry>> freqDictionary; 

public:
	InvertedIndex()  = default;
	~InvertedIndex() = default;
	/**
	 * Метод выделяет из документов уникальные слова, и помещает их в словарь freqDictionary .
	 * В роли ключа выступает само слово, а в значение записывается вектор содержащий 
	 * id документов и количество повторений этого слова в них.
	 * @param &docs ссылка на вектор с содержимым документов по которым осуществляется поиск.
	*/
	void updateDocumentBase(const std::vector<std::string> &docs);

	/**
	 * Метод поиска по словарю уникальных слов
	 * @param word искомое слово
	 * @return  возвращает вектор содержащий информацию о колличестве 
	 * вхождений слова в документы по которым осуществляется поиск.
	*/
	std::vector<Entry> getWordCount(std::string &word);

};