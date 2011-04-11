#define BOOST_TEST_MODULE spirit2json test
#include <spirit2json.h>
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace spirit2json;

/*
	Tests for Number
*/
BOOST_AUTO_TEST_CASE(number_basic_usage) {
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("42.0"))), 42.0);
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("-5"))), -5.);
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("42"))), 42.);
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("42"))), 42);
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("1234567890"))), 1234567890.);
	BOOST_CHECK_EQUAL(get<double>(JSONValue(parse("-1234567890"))), -1234567890.);
}

BOOST_AUTO_TEST_CASE(number_notations) {
	//TODO: Test whether Numbers can be entered in all notations specified by the spec
	BOOST_FAIL("Not implemented");
}

BOOST_AUTO_TEST_CASE(number_precision) {
	//TODO: Make sure we meet the precision requirements outlined in the JSON spec
	BOOST_FAIL("Not implemented");
}

/*
	Tests for String
*/
BOOST_AUTO_TEST_CASE(string_basic_usage) {
	BOOST_CHECK_EQUAL(get<string>(JSONValue(parse("\"testing\""))), "testing");
}

BOOST_AUTO_TEST_CASE(string_escape_characters) {
	BOOST_CHECK_EQUAL(get<string>(JSONValue(parse("\"testing\\\"\""))), "testing\"");
	//TODO: Implement others
	BOOST_FAIL("Not implemented");
}

BOOST_AUTO_TEST_CASE(string_unicode) {
	//TODO: Implement Unicode checks
	BOOST_FAIL("Not implemented");
}

/*
	Tests for Bool
*/

BOOST_AUTO_TEST_CASE(boolean) {
	BOOST_CHECK_EQUAL(get<bool>(JSONValue(parse("true"))), true);
	BOOST_CHECK_EQUAL(get<bool>(JSONValue(parse("false"))), false);

	// Make sure we parse case sensitive
	BOOST_CHECK_THROW(parse("False"), ParsingFailed);
	BOOST_CHECK_THROW(parse("FALSE"), ParsingFailed);
	BOOST_CHECK_THROW(parse("True"), ParsingFailed);
	BOOST_CHECK_THROW(parse("TRUE"), ParsingFailed);
}

/*
	Tests for null
*/
BOOST_AUTO_TEST_CASE(null) {
	//TODO: Figure out how to do this in a nice way
	JSONValue val(parse("null"));
	
	unsigned int accumulated = 0;
	unsigned int strings = 0;
	unsigned int objects = 0;
	unsigned int arrays = 0;
	unsigned int bools = 0;
	unsigned int nulls = 0;
	unsigned int doubles = 0;
	get_stats(accumulated, strings, objects, arrays, bools, nulls, doubles, val);
	BOOST_CHECK((nulls == 1) && (accumulated == 1));
	
	// Make sure we don't accept anything used in other languages
	BOOST_CHECK_THROW(parse("nil"), ParsingFailed);
	BOOST_CHECK_THROW(parse("None"), ParsingFailed);

	// Make sure we parse case sensitive
	BOOST_CHECK_THROW(parse("Null"), ParsingFailed);
	BOOST_CHECK_THROW(parse("NULL"), ParsingFailed);
}

/*
	Tests for Array
*/
BOOST_AUTO_TEST_CASE(array_basic_usage) {
	JSONArray arr;
	BOOST_CHECK(JSONValue(arr) == parse("[]"));

	arr.push_back(0.5);
	arr.push_back(nullptr);
	arr.push_back(string("testing"));
	arr.push_back(false);

	BOOST_CHECK(JSONValue(arr) == parse("[ 0.5, null  \t, \n\"testing\",false   ] "));
}

/*
	Tests for Object
*/
BOOST_AUTO_TEST_CASE(object_basic_usage) {
	JSONObject obj;
	BOOST_CHECK(JSONValue(obj) == parse("{}"));

	obj.insert(JSONObject::value_type("test", 0.5));
	BOOST_CHECK(JSONValue(obj) == parse("{\"test\":0.5}"));

	obj.insert(JSONObject::value_type("other", JSONArray()));
	//cout << obj;
	JSONValue v(parse("{\"test\":0.5,\"other\":[]}"));
	//cout << v;
	BOOST_CHECK(JSONValue(obj) == parse("{\"test\":0.5,\"other\":[]}"));

	obj.insert(JSONObject::value_type("NULL", nullptr));
	BOOST_CHECK(JSONValue(obj) == parse(" { \"test\" :0.5,\n\t\t\"other\"  t\n:[],  \"NULL\":null}"));
}
