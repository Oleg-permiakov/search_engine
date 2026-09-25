//
// Created by Oleg on 20.12.2025.
//
#include "invertedIndex.h"

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <set>


/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
* input_docs получим через getTextDocument()
*/
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    std::set<std::string> words;
    for (auto &stringWord: input_docs) {
        std::stringstream ss(stringWord);
        std::string word;
        while (ss >> word) {
            words.insert(word);
        }
    }
    for (auto stringWord: words) {
        docs.push_back(stringWord);
    }

    std::pair<std::string, std::vector<Entry> > resultEntries;
    for (const auto wordUnic: docs) {
        resultEntries.first = wordUnic;
        auto numEntry = GetWordCount(wordUnic, input_docs);
        resultEntries.second = numEntry;
        freq_dictionary.insert(resultEntries);
    }
}

/*** Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
* Загружается строка запросов
*
*/
std::vector<Entry> InvertedIndex::GetWordCount(const std::string word, std::vector<std::string> input_docs) {
    Entry res;
    std::vector<Entry> resultEntries;
    /*прогнать по документам и найти количество совпадений слова*/
    for (int i = 0; i < input_docs.size(); ++i) {
        std::string docWord;
        size_t new_count = 0;
        res.doc_id = i;
        std::vector<std::string> words;
        std::stringstream ss(input_docs[i]);
        while (ss >> docWord) {
            words.push_back(docWord);
        }
        for (auto docWord: words) {
            if (docWord == word) {
                new_count++;
            }
        }
        res.count = new_count;
        resultEntries.push_back(res);
    }
    return resultEntries;
}

std::map<std::string, std::vector<Entry> > InvertedIndex::GetFreqDictionary() {
    return freq_dictionary;
}
