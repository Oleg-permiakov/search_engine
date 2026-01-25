//
// Created by Oleg on 26.12.2025.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H
#include "invertedIndex.h"


struct RelativeIndex{
    size_t docs_id;
    float rank;
    bool operator ==(const RelativeIndex &other) const {
        return (docs_id == other.docs_id && rank == other.rank);
    }
};

class SearchServer {
public:
        SearchServer(InvertedIndex  &idx);

    std::vector<std::vector<RelativeIndex>> search(const
    std::vector<std::string>& queries_input);

private:
    InvertedIndex _index;
};

#endif //SEARCH_ENGINE_SEARCHSERVER_H
