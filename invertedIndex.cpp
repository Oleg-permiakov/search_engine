//
// Created by Oleg on 20.12.2025.
//

#include "invertedIndex.h"
#include "ConverterJSON.h"
#include <vector>
#include <map>



/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
* input_docs получим через getTextDocument()
*/
void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    ConverterJSON converter;
    input_docs = converter.GetTextDocuments();
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
    std::vector<Entry> result;
    Entry res;
    for (size_t i = 0; i < docs.size(); ++i) {
        size_t new_count = 0;
        size_t pos = docs[i].find(word);
        while (pos != std::string::npos) {
            new_count++;
            pos = docs[i].find(word, pos + 1);
        }
        res.doc_id = i;
        res.count = new_count;
        result.push_back(res);
    }
    std::pair<std::string, std::vector<Entry> > oPair(word, result);
    freq_dictionary.insert(oPair);
    return result;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::getFreq_dictionary() {
    return freq_dictionary;
}


