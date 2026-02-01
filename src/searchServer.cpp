//
// Created by Oleg on 26.12.2025.
//
#include "searchServer.h"
#include "invertedIndex.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <utility>


/**
    * @param idx в конструктор класса передаётся ссылка на класс
    InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в
    запросе
    */
SearchServer::SearchServer(InvertedIndex &idx) : _index(idx) {
}

/**
   * Метод обработки поисковых запросов
   * @param queries_input поисковые запросы взятые из файла
   requests.json
   * @return возвращает отсортированный список релевантных ответов для
   заданных запросов
   */
std::vector<std::vector<RelativeIndex> > SearchServer::search(const std::vector<std::string> &queries_input) {
    auto freq_dict = _index.getFreq_dictionary();
    std::vector<RelativeIndex> genIndex;
    std::vector<std::vector<RelativeIndex> > answer;

    for (int i = 0; i < queries_input.size(); ++i) {
        for (auto it = freq_dict.begin(); it != freq_dict.end(); ++it) {
            if (it->first == queries_input[i] && !(it->second.empty())) {
                auto freq = it->second;
                for (const auto &value: freq) {
                    genIndex.resize(genIndex.size() + 1);
                    genIndex[value.doc_id].docs_id = value.doc_id;
                    genIndex[value.doc_id].rank = genIndex[value.doc_id].rank + value.count;
                }
            }
        }
        std::vector<float> numberRank;
        for (int i = 0; i < genIndex.size(); ++i) {
            numberRank.push_back(genIndex[i].rank);
        }
        auto max_iterator = std::max_element(numberRank.begin(), numberRank.end());
        auto maxNumIndex = *max_iterator;
        for (auto &gen_index: genIndex) {
            gen_index.rank = gen_index.rank / maxNumIndex;
        }
        answer.push_back(genIndex);
    }

    return answer;
}
