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

#include <cstdio>     // for getline().
#include <cstdlib>    // for EXIT_SUCCESS, EXIT_FAILURE, free().
#include <cstring>    // for strlen().
#include <iostream>   // for std::cout, std::cerr, etc.
#include <sstream>    // for std::stringstream.
#include <vector>     // for std::vector.
#include <list>       // for std::list.
#include <algorithm>  // for std::transform and ::tolower.

#include "./QueryProcessor.h"

using namespace std;  // NOLINT(build/namespaces)
using namespace hw3;  // NOLINT(build/namespaces)

static void Usage(char *progname) {
  std::cerr << "Usage: " << progname << " [index files+]" << std::endl;
  exit(EXIT_FAILURE);
}

// Prints out the query result according to format
static void Print(vector<QueryProcessor::QueryResult> result);

// Your job is to implement the entire filesearchshell.cc
// functionality. We're essentially giving you a blank screen to work
// with; you need to figure out an appropriate design, to decompose
// the problem into multiple functions or classes if that will help,
// to pick good interfaces to those functions/classes, and to make
// sure that you don't leak any memory.
//
// Here are the requirements for a working solution:
//
// The user must be able to run the program using a command like:
//
//   ./filesearchshell ./foo.idx ./bar/baz.idx /tmp/blah.idx [etc]
//
// i.e., to pass a set of filenames of indices as command line
// arguments. Then, your program needs to implement a loop where
// each loop iteration it:
//
//  (a) prints to the console a prompt telling the user to input the
//      next query.
//
//  (b) reads a white-space separated list of query words from
//      std::cin, converts them to lowercase, and constructs
//      a vector of c++ strings out of them.
//
//  (c) uses QueryProcessor.cc/.h's QueryProcessor class to
//      process the query against the indices and get back a set of
//      query results.  Note that you should instantiate a single
//      QueryProcessor  object for the lifetime of the program, rather
//      than  instantiating a new one for every query.
//
//  (d) print the query results to std::cout in the format shown in
//      the transcript on the hw3 web page.
//
// Also, you're required to quit out of the loop when std::cin
// experiences EOF, which a user passes by pressing "control-D"
// on the console.  As well, users should be able to type in an
// arbitrarily long query -- you shouldn't assume anything about
// a maximum line length.  Finally, when you break out of the
// loop and quit the program, you need to make sure you deallocate
// all dynamically allocated memory.  We will be running valgrind
// on your filesearchshell implementation to verify there are no
// leaks or errors.
//
// You might find the following technique useful, but you aren't
// required to use it if you have a different way of getting the
// job done.  To split a std::string into a vector of words, you
// can use a std::stringstream to get the job done and the ">>"
// operator. See, for example, "gnomed"'s post on stackoverflow for
// his example on how to do this:
//
//   http://stackoverflow.com/questions/236129/c-how-to-split-a-string
//
// (Search for "gnomed" on that page.  He uses an istringstream, but
// a stringstream gets the job done too.)
//
// Good luck, and write beautiful code!

int main(int argc, char **argv) {
  if (argc < 2) {
    Usage(argv[0]);
  }

  // STEP 1:
  // Implement filesearchshell!
  list<string> idx_list;
  // store the input index to index list
  for (int i = 1; i < argc; i++) {
    idx_list.push_back(string(argv[i]));
  }

  // create query processor to process user's query
  QueryProcessor queryprocessor(idx_list, true);
  while (1) {
    string s, tkn;
    vector<string> token;

    cout << "Enter query: " << endl;
    // get query input and check if it's valid
    getline(cin, s);
    if (!cin.good() || s.empty()) {
      break;
    }

    // convert query input into all lowecase
    // i.e. for query like DEfeNcE ANteLOpE and defence antelope
    for (int i = 0; s[i]; i++) {
      s[i] = tolower(s[i]);
    }

    // use stringstream to push the query input to a vector
    stringstream ss(s, stringstream::in);
    while (ss >> tkn) {
      token.push_back(tkn);
    }

    // process the query
    vector<QueryProcessor::QueryResult> result =
                                 queryprocessor.ProcessQuery(token);
    // print result
    Print(result);
  }
  return EXIT_SUCCESS;
}

static void Print(vector<QueryProcessor::QueryResult> result) {
  if (result.empty()) {
    cout << "  [no results]" << endl;
    return;
  }
  for (auto r : result) {
    cout << "  " << r.documentName << " (" << r.rank << ")" << endl;
  }
}