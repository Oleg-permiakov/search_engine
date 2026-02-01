//
// Created by Oleg on 20.12.2025.
//
#include "invertedIndex.h"
#include <vector>
#include <map>
#include <sstream>


/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
* input_docs получим через getTextDocument()
*/
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
}


/*** Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
* Загружается строка запросов
*
*/
std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    Entry res;
    std::vector<Entry> result;
    size_t new_count = 0;
    std::vector<std::string> docWords;
    /*прогнать по документам и найти количество совпадений слова*/
    for (size_t i = 0; i < docs.size(); ++i) {
        std::string docWord;
        std::stringstream ss(docs[i]);
        while (ss >> docWord) {
            docWords.push_back(docWord);
        }
        for (const auto &doc_word: docWords) {
            if (doc_word == word) new_count++;
        }
        if (new_count > 0) {
            res.doc_id = i;
            res.count = new_count;
            result.push_back(res);
        }
    }
    std::pair<std::string, std::vector<Entry> > oPair(word, result);
    freq_dictionary.insert(oPair);

    return result;
}

std::map<std::string, std::vector<Entry> > InvertedIndex::getFreq_dictionary() {
    return freq_dictionary;
}
