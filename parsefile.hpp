#ifndef _PARSEFILE_H
#define _PARSEFILE_H

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string> attributeMapType;
typedef std::vector<attributeMapType> parseResultType;
void parseFile(const std::string, parseResultType &);

#endif /* _PARSEFILE_H */
