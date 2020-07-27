# Disk-Based File System Search Engine
## Memory-to-File Index Marshaller
| Program Files | | 
| --- | --- | 
| [Utils.h](https://github.com/bellaroseee/SysProg-hw3/blob/master/Utils.h) | utility class for functions and constant to use throughout the program |
| [Utils.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/Utils.cc) | implementation of Utils header file | 
| [LayoutStructs.h](https://github.com/bellaroseee/SysProg-hw3/blob/master/LayoutStructs.h) | header file representing the in-memory structs of on-disk data structure |
| [WriteIndex.h](https://github.com/bellaroseee/SysProg-hw3/blob/master/WriteIndex.h) | Memory Index amd DocTable mapping to index file |
| [WriteIndex.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/WriteIndex.cc) | implementation of WriteIndex header file |

| Test Files | | 
| --- | --- | 
| [test_fileindexutil.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/test_fileindexutil.cc) | unit test for Utils.cc |
| [test_utils.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/test_utils.cc) | unit test for Utils.cc  |
| [test_writeindex.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/test_writeindex.cc) | unit test for WriteIndex implementation | 

## Index Lookup
| Program Files | | 
| --- | --- |
| [FileIndexReader.h](https://github.com/bellaroseee/SysProg-hw3/blob/master/FileIndexReader.h) | Read the index file written with WriteIndex and build hash table accessor for DocTableReader and IndextableReader | 
| [FileIndexReader.cc](https://github.com/bellaroseee/SysProg-hw3/blob/master/FileIndexReader.cc) | implementation of FileIndexReader header file |
| HashTableReader.h | |
| HashTableReader.cc | |
| DocTableReader.h | |
| DocTableReader.cc | |
| IndexTableReader.h | |
| IndexTableReade.cc | |
| DocIDTableReader.h | |
| DocIDTableReader.cc | |
| QueryProcessor.h | |
| QueryProcessor.cc | |

| Test Files | | 
| --- | --- |
| test_fileindexreader.cc | |
| test_hashtablereader.cc | |
| test_doctablereader.cc | |
| test_indextablereader.cc | | 
| test_docidtablereader.cc | |
| test_queryprocessor.cc | | 

## Search Shell
| Program Files | |
| --- | --- |
| filesearchshell.cc | | 

## Memory Check
