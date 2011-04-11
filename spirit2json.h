#ifndef SPIRIT2JSON_H
#define SPIRIT2JSON_H

#include <string>
#include <stdexcept>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>

struct boost::recursive_variant_ {};

namespace spirit2json {

typedef boost::make_recursive_variant<
	std::string,
	double,
	bool,
	std::nullptr_t,
	std::vector<boost::recursive_variant_ >,
	std::unordered_map<std::string, boost::recursive_variant_ > >::type JSONValue;

typedef std::vector<JSONValue> JSONArray;
typedef std::unordered_map<std::string, JSONValue> JSONObject;

class Exception : public std::exception {};
class ParsingFailed : public Exception {};

JSONValue parse(std::string str);

void get_stats(unsigned int &accumulated, 
			unsigned int &strings,
			unsigned int &objects,
			unsigned int &arrays,
			unsigned int &bools,
			unsigned int &nulls,
			unsigned int &doubles,
			JSONValue &val);


}

std::ostream& operator<<(std::ostream& output, spirit2json::JSONValue& val);
std::ostream& operator<<(std::ostream& output, spirit2json::JSONArray& arr);
std::ostream& operator<<(std::ostream& output, spirit2json::JSONObject& obj);

#endif