//
// Created by Oleg on 26.12.2025.
//
#include "searchServer.h"
#include "invertedIndex.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <map>
#include <utility>
#include <set>

#include "ConverterJSON.h"


/**
    * @param idx в конструктор класса передаётся ссылка на класс
    InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в
    запросе
    */
SearchServer::SearchServer(InvertedIndex &idx) : _index(idx) {
}

// /**
//    * Метод обработки поисковых запросов
//    * @param queries_input поисковые запросы взятые из файла
//    requests.json
//    * @return возвращает отсортированный список релевантных ответов для
//    заданных запросов
//    */
std::vector<std::vector<RelativeIndex> > SearchServer::search(const std::vector<std::string> &queries_input) {
    auto dict = _index.GetFreqDictionary();
    ConverterJSON converter;
    RelativeIndex genIndex;
    std::vector<RelativeIndex> genIndexes;
    std::vector<std::vector<RelativeIndex> > result;
    Entry queryEntr;
    std::vector<Entry> queryEntres;
    float genRank; /*наибольшее значение совпадений*/

    if (converter.GetResponsesLimit() <= queries_input.size()) {
        for (const auto &query: queries_input) {
            genRank = 1;
            genIndexes.clear();
            std::set<std::string> queryWords;
            std::string querryWord;
            std::stringstream ss(query);
            while (ss >> querryWord) {
                queryWords.insert(querryWord);
            }

            if (!dict.empty()) {
                for (int i = 0; i < dict.begin()->second.size(); ++i) {
                    queryEntr.doc_id = i, queryEntr.count = 0;
                    queryEntres.push_back(queryEntr);
                }
            }

            for (const auto &word: queryWords) {
                /*смотрим в map как делается запрос по ключу*/
                if (dict.count(word) > 0) {
                    for (int i = 0; i < dict.at(word).size(); i++) {
                        if (dict.at(word)[i].doc_id == i && queryEntres[i].doc_id == i) {
                            queryEntres[i].doc_id = i;
                            queryEntres[i].count += dict.at(word)[i].count;
                            if (queryEntres[i].count > genRank) {
                                genRank = queryEntres[i].count;
                            }
                        }
                    }
                }
            }

            for (auto &queryEntr: queryEntres) {
                genIndex.docs_id = queryEntr.doc_id;
                genIndex.rank = (queryEntr.count) / genRank;
                genIndexes.push_back(genIndex);
            }
            queryEntres.clear();
            result.push_back(genIndexes);
        }
    } else {
        std::cout << "The number of requests exceeds the limit" << std::endl;
    }
    return result;
}
