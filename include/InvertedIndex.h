#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>
#include <thread>
#include <mutex>
#include "converterJSON.h"

struct Entry {
	size_t docId, count;
	
	Entry(size_t _docId, size_t _count): docId(_docId),count(_count){}
	~Entry() = default; 

};

class InvertedIndex {

	// Частотный словарь<слово, вектор структур<Entry{docId, count}>>
	std::map<std::string, std::vector<Entry>> freqDictionary;

public:
	InvertedIndex()  = default;
	~InvertedIndex() = default;
	/**
	 * Обновить или заполнить базу документов, по которой будем совершать поиск
	 *
	 * @param &docs содержимое документов
	*/
	void updateDocumentBase(const std::vector<std::string> &docs);

	/**
	 * Метод определяет количество вхождений слова в загруженной базе документов
	 * @param word слово, частоту вхождений которого необходимо определить
	 * @return  возвращает подготовленный список с частотой слов
	*/

	std::vector<Entry> getWordCount(std::string &word);

};