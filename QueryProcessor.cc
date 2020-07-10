/*
 * Copyright ©2020 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2020 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

  // Helper function to determine the correct rank of query result.
  // output parameter is the finalresult
  // finalresult is modified
  static void sortRank(vector<QueryProcessor::QueryResult> *finalresult,
  QueryProcessor::QueryResult query_res);

  // Helper function to filter our duplicate of searchresult with finalresult
  // output parameter is finalresult
  // finalresult is modified
  static void deleteDuplicate(vector<QueryProcessor::QueryResult> *finalresult,
  vector<QueryProcessor::QueryResult> searchresult);


QueryProcessor::QueryProcessor(const list<string> &indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = indexlist_.begin();
  for (int i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t docid;  // The document ID within the index file.
  int rank;       // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> finalresult;

  for (uint8_t first = 0; first < query.size(); first++) {
    vector<QueryProcessor::QueryResult> searchresult = finalresult;
    for (int j = 0; j < arraylen_; j++) {
      // get current indices
      DocTableReader *dt_reader = dtr_array_[j];
      IndexTableReader *idt_reader = itr_array_[j];

      // look up the query
      DocIDTableReader *doc_id_table = idt_reader->LookupWord(query[first]);
      // if not match, skip and continue
      if (doc_id_table == NULL) {
        continue;
      }

      // get doc id list
      list<DocIDElementHeader> doc_id_list = doc_id_table->GetDocIDList();

      // for each element (header) in the list
      for (auto header : doc_id_list)  {
        string docname;

        Verify333(dt_reader->LookupDocID(header.docID, &docname));

        QueryResult query_res;
        query_res.documentName = docname;
        query_res.rank = header.numPositions;

        // if see the query for the first time, push to final result list
        if (first == 0) {
          finalresult.push_back(query_res);
        } else {
          // determine the rank of the query result
          sortRank(&finalresult, query_res);
        }
      }
      delete doc_id_table;
    }
    deleteDuplicate(&finalresult, searchresult);
  }


  // Sort the final results.
  sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

  static void sortRank(vector<QueryProcessor::QueryResult> *finalresult,
                       QueryProcessor::QueryResult query_res) {
    // check if this is the first word
    uint32_t count = 0;

    // if the docid alreday in the list, then increase the rank
    while (count < finalresult->size()) {
      if (query_res.documentName.compare(finalresult->at(count).documentName)
                                                                    == 0) {
        finalresult->at(count).rank += query_res.rank;
      }
      count++;
    }
  }

  static void deleteDuplicate(vector<QueryProcessor::QueryResult> *finalresult,
                           vector<QueryProcessor::QueryResult> searchresult) {
    for (QueryProcessor::QueryResult r : searchresult) {
      for (uint8_t i = 0; i < finalresult->size(); i++) {
        if ((r.documentName.compare(finalresult->at(i).documentName) == 0)
            & (r.rank == finalresult->at(i).rank)) {
            finalresult->erase(finalresult->begin() + i);
        }
      }
    }
  }

}  // namespace hw3
