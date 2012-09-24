#include "tests.h"
#include "yaml.h"

namespace Test
{
	namespace Emitter {
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// correct emitting

		void SimpleScalar(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << "Hello, World!";
			desiredOutput = "Hello, World!";
		}

		void SimpleSeq(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginSeq;
			out << "eggs";
			out << "bread";
			out << "milk";
			out << SK_YAML::EndSeq;

			desiredOutput = "- eggs\n- bread\n- milk";
		}

		void SimpleFlowSeq(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::Flow;
			out << SK_YAML::BeginSeq;
			out << "Larry";
			out << "Curly";
			out << "Moe";
			out << SK_YAML::EndSeq;

			desiredOutput = "[Larry, Curly, Moe]";
		}

		void EmptyFlowSeq(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::Flow;
			out << SK_YAML::BeginSeq;
			out << SK_YAML::EndSeq;

			desiredOutput = "[]";
		}

		void NestedBlockSeq(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginSeq;
			out << "item 1";
			out << SK_YAML::BeginSeq << "subitem 1" << "subitem 2" << SK_YAML::EndSeq;
			out << SK_YAML::EndSeq;

			desiredOutput = "- item 1\n-\n  - subitem 1\n  - subitem 2";
		}

		void NestedFlowSeq(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginSeq;
			out << "one";
			out << SK_YAML::Flow << SK_YAML::BeginSeq << "two" << "three" << SK_YAML::EndSeq;
			out << SK_YAML::EndSeq;

			desiredOutput = "- one\n- [two, three]";
		}

		void SimpleMap(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name";
			out << SK_YAML::Value << "Ryan Braun";
			out << SK_YAML::Key << "position";
			out << SK_YAML::Value << "3B";
			out << SK_YAML::EndMap;

			desiredOutput = "name: Ryan Braun\nposition: 3B";
		}

		void SimpleFlowMap(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::Flow;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "shape";
			out << SK_YAML::Value << "square";
			out << SK_YAML::Key << "color";
			out << SK_YAML::Value << "blue";
			out << SK_YAML::EndMap;

			desiredOutput = "{shape: square, color: blue}";
		}

		void MapAndList(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name";
			out << SK_YAML::Value << "Barack Obama";
			out << SK_YAML::Key << "children";
			out << SK_YAML::Value << SK_YAML::BeginSeq << "Sasha" << "Malia" << SK_YAML::EndSeq;
			out << SK_YAML::EndMap;

			desiredOutput = "name: Barack Obama\nchildren:\n  - Sasha\n  - Malia";
		}

		void ListAndMap(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginSeq;
			out << "item 1";
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "pens" << SK_YAML::Value << 8;
			out << SK_YAML::Key << "pencils" << SK_YAML::Value << 14;
			out << SK_YAML::EndMap;
			out << "item 2";
			out << SK_YAML::EndSeq;

			desiredOutput = "- item 1\n-\n  pens: 8\n  pencils: 14\n- item 2";
		}

		void NestedBlockMap(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name";
			out << SK_YAML::Value << "Fred";
			out << SK_YAML::Key << "grades";
			out << SK_YAML::Value;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "algebra" << SK_YAML::Value << "A";
			out << SK_YAML::Key << "physics" << SK_YAML::Value << "C+";
			out << SK_YAML::Key << "literature" << SK_YAML::Value << "B";
			out << SK_YAML::EndMap;
			out << SK_YAML::EndMap;

			desiredOutput = "name: Fred\ngrades:\n  algebra: A\n  physics: C+\n  literature: B";
		}

		void NestedFlowMap(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::Flow;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name";
			out << SK_YAML::Value << "Fred";
			out << SK_YAML::Key << "grades";
			out << SK_YAML::Value;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "algebra" << SK_YAML::Value << "A";
			out << SK_YAML::Key << "physics" << SK_YAML::Value << "C+";
			out << SK_YAML::Key << "literature" << SK_YAML::Value << "B";
			out << SK_YAML::EndMap;
			out << SK_YAML::EndMap;

			desiredOutput = "{name: Fred, grades: {algebra: A, physics: C+, literature: B}}";
		}

		void MapListMix(SK_YAML::Emitter& out, std::string& desiredOutput) {
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name";
			out << SK_YAML::Value << "Bob";
			out << SK_YAML::Key << "position";
			out << SK_YAML::Value;
			out << SK_YAML::Flow << SK_YAML::BeginSeq << 2 << 4 << SK_YAML::EndSeq;
			out << SK_YAML::Key << "invincible" << SK_YAML::Value << SK_YAML::OnOffBool << false;
			out << SK_YAML::EndMap;

			desiredOutput = "name: Bob\nposition: [2, 4]\ninvincible: off";
		}

		void SimpleLongKey(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::LongKey;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "height";
			out << SK_YAML::Value << "5'9\"";
			out << SK_YAML::Key << "weight";
			out << SK_YAML::Value << 145;
			out << SK_YAML::EndMap;

			desiredOutput = "? height\n: 5'9\"\n? weight\n: 145";
		}

		void SingleLongKey(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "age";
			out << SK_YAML::Value << "24";
			out << SK_YAML::LongKey << SK_YAML::Key << "height";
			out << SK_YAML::Value << "5'9\"";
			out << SK_YAML::Key << "weight";
			out << SK_YAML::Value << 145;
			out << SK_YAML::EndMap;

			desiredOutput = "age: 24\n? height\n: 5'9\"\nweight: 145";
		}

		void ComplexLongKey(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::LongKey;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << SK_YAML::BeginSeq << 1 << 3 << SK_YAML::EndSeq;
			out << SK_YAML::Value << "monster";
			out << SK_YAML::Key << SK_YAML::Flow << SK_YAML::BeginSeq << 2 << 0 << SK_YAML::EndSeq;
			out << SK_YAML::Value << "demon";
			out << SK_YAML::EndMap;

			desiredOutput = "?\n  - 1\n  - 3\n: monster\n? [2, 0]\n: demon";
		}

		void AutoLongKey(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << SK_YAML::BeginSeq << 1 << 3 << SK_YAML::EndSeq;
			out << SK_YAML::Value << "monster";
			out << SK_YAML::Key << SK_YAML::Flow << SK_YAML::BeginSeq << 2 << 0 << SK_YAML::EndSeq;
			out << SK_YAML::Value << "demon";
			out << SK_YAML::Key << "the origin";
			out << SK_YAML::Value << "angel";
			out << SK_YAML::EndMap;

			desiredOutput = "?\n  - 1\n  - 3\n: monster\n? [2, 0]\n: demon\nthe origin: angel";
		}

		void ScalarFormat(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << "simple scalar";
			out << SK_YAML::SingleQuoted << "explicit single-quoted scalar";
			out << SK_YAML::DoubleQuoted << "explicit double-quoted scalar";
			out << "auto-detected\ndouble-quoted scalar";
			out << "a non-\"auto-detected\" double-quoted scalar";
			out << SK_YAML::Literal << "literal scalar\nthat may span\nmany, many\nlines and have \"whatever\" crazy\tsymbols that we like";
			out << SK_YAML::EndSeq;

			desiredOutput = "- simple scalar\n- 'explicit single-quoted scalar'\n- \"explicit double-quoted scalar\"\n- \"auto-detected\\x0adouble-quoted scalar\"\n- a non-\"auto-detected\" double-quoted scalar\n- |\n  literal scalar\n  that may span\n  many, many\n  lines and have \"whatever\" crazy\tsymbols that we like";
		}

		void AutoLongKeyScalar(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << SK_YAML::Literal << "multi-line\nscalar";
			out << SK_YAML::Value << "and its value";
			out << SK_YAML::EndMap;

			desiredOutput = "? |\n  multi-line\n  scalar\n: and its value";
		}

		void LongKeyFlowMap(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::Flow;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "simple key";
			out << SK_YAML::Value << "and value";
			out << SK_YAML::LongKey << SK_YAML::Key << "long key";
			out << SK_YAML::Value << "and its value";
			out << SK_YAML::EndMap;

			desiredOutput = "{simple key: and value, ? long key: and its value}";
		}

		void BlockMapAsKey(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key" << SK_YAML::Value << "value";
			out << SK_YAML::Key << "next key" << SK_YAML::Value << "next value";
			out << SK_YAML::EndMap;
			out << SK_YAML::Value;
			out << "total value";
			out << SK_YAML::EndMap;

			desiredOutput = "?\n  key: value\n  next key: next value\n: total value";
		}

		void AliasAndAnchor(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << SK_YAML::Anchor("fred");
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "name" << SK_YAML::Value << "Fred";
			out << SK_YAML::Key << "age" << SK_YAML::Value << 42;
			out << SK_YAML::EndMap;
			out << SK_YAML::Alias("fred");
			out << SK_YAML::EndSeq;

			desiredOutput = "- &fred\n  name: Fred\n  age: 42\n- *fred";
		}

		void AliasAndAnchorWithNull(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << SK_YAML::Anchor("fred") << SK_YAML::Null;
			out << SK_YAML::Alias("fred");
			out << SK_YAML::EndSeq;

			desiredOutput = "- &fred ~\n- *fred";
		}

		void ComplexDoc(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "receipt";
			out << SK_YAML::Value << "Oz-Ware Purchase Invoice";
			out << SK_YAML::Key << "date";
			out << SK_YAML::Value << "2007-08-06";
			out << SK_YAML::Key << "customer";
			out << SK_YAML::Value;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "given";
			out << SK_YAML::Value << "Dorothy";
			out << SK_YAML::Key << "family";
			out << SK_YAML::Value << "Gale";
			out << SK_YAML::EndMap;
			out << SK_YAML::Key << "items";
			out << SK_YAML::Value;
			out << SK_YAML::BeginSeq;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "part_no";
			out << SK_YAML::Value << "A4786";
			out << SK_YAML::Key << "descrip";
			out << SK_YAML::Value << "Water Bucket (Filled)";
			out << SK_YAML::Key << "price";
			out << SK_YAML::Value << 1.47;
			out << SK_YAML::Key << "quantity";
			out << SK_YAML::Value << 4;
			out << SK_YAML::EndMap;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "part_no";
			out << SK_YAML::Value << "E1628";
			out << SK_YAML::Key << "descrip";
			out << SK_YAML::Value << "High Heeled \"Ruby\" Slippers";
			out << SK_YAML::Key << "price";
			out << SK_YAML::Value << 100.27;
			out << SK_YAML::Key << "quantity";
			out << SK_YAML::Value << 1;
			out << SK_YAML::EndMap;
			out << SK_YAML::EndSeq;
			out << SK_YAML::Key << "bill-to";
			out << SK_YAML::Value << SK_YAML::Anchor("id001");
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "street";
			out << SK_YAML::Value << SK_YAML::Literal << "123 Tornado Alley\nSuite 16";
			out << SK_YAML::Key << "city";
			out << SK_YAML::Value << "East Westville";
			out << SK_YAML::Key << "state";
			out << SK_YAML::Value << "KS";
			out << SK_YAML::EndMap;
			out << SK_YAML::Key << "ship-to";
			out << SK_YAML::Value << SK_YAML::Alias("id001");
			out << SK_YAML::EndMap;

			desiredOutput = "receipt: Oz-Ware Purchase Invoice\ndate: 2007-08-06\ncustomer:\n  given: Dorothy\n  family: Gale\nitems:\n  -\n    part_no: A4786\n    descrip: Water Bucket (Filled)\n    price: 1.47\n    quantity: 4\n  -\n    part_no: E1628\n    descrip: High Heeled \"Ruby\" Slippers\n    price: 100.27\n    quantity: 1\nbill-to: &id001\n  street: |\n    123 Tornado Alley\n    Suite 16\n  city: East Westville\n  state: KS\nship-to: *id001";
		}

		void STLContainers(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			std::vector <int> primes;
			primes.push_back(2);
			primes.push_back(3);
			primes.push_back(5);
			primes.push_back(7);
			primes.push_back(11);
			primes.push_back(13);
			out << SK_YAML::Flow << primes;
			std::map <std::string, int> ages;
			ages["Daniel"] = 26;
			ages["Jesse"] = 24;
			out << ages;
			out << SK_YAML::EndSeq;

			desiredOutput = "- [2, 3, 5, 7, 11, 13]\n-\n  Daniel: 26\n  Jesse: 24";
		}

		void SimpleComment(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "method";
			out << SK_YAML::Value << "least squares" << SK_YAML::Comment("should we change this method?");
			out << SK_YAML::EndMap;

			desiredOutput = "method: least squares  # should we change this method?";
		}

		void MultiLineComment(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << "item 1" << SK_YAML::Comment("really really long\ncomment that couldn't possibly\nfit on one line");
			out << "item 2";
			out << SK_YAML::EndSeq;

			desiredOutput = "- item 1  # really really long\n          # comment that couldn't possibly\n          # fit on one line\n- item 2";
		}

		void ComplexComments(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginMap;
			out << SK_YAML::LongKey << SK_YAML::Key << "long key" << SK_YAML::Comment("long key");
			out << SK_YAML::Value << "value";
			out << SK_YAML::EndMap;

			desiredOutput = "? long key  # long key\n: value";
		}

		void Indentation(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::Indent(4);
			out << SK_YAML::BeginSeq;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key 1" << SK_YAML::Value << "value 1";
			out << SK_YAML::Key << "key 2" << SK_YAML::Value << SK_YAML::BeginSeq << "a" << "b" << "c" << SK_YAML::EndSeq;
			out << SK_YAML::EndMap;
			out << SK_YAML::EndSeq;

			desiredOutput = "-\n    key 1: value 1\n    key 2:\n        - a\n        - b\n        - c";
		}

		void SimpleGlobalSettings(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out.SetIndent(4);
			out.SetMapFormat(SK_YAML::LongKey);

			out << SK_YAML::BeginSeq;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key 1" << SK_YAML::Value << "value 1";
			out << SK_YAML::Key << "key 2" << SK_YAML::Value << SK_YAML::Flow << SK_YAML::BeginSeq << "a" << "b" << "c" << SK_YAML::EndSeq;
			out << SK_YAML::EndMap;
			out << SK_YAML::EndSeq;

			desiredOutput = "-\n    ? key 1\n    : value 1\n    ? key 2\n    : [a, b, c]";
		}

		void ComplexGlobalSettings(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << SK_YAML::Block;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key 1" << SK_YAML::Value << "value 1";
			out << SK_YAML::Key << "key 2" << SK_YAML::Value;
			out.SetSeqFormat(SK_YAML::Flow);
			out << SK_YAML::BeginSeq << "a" << "b" << "c" << SK_YAML::EndSeq;
			out << SK_YAML::EndMap;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << SK_YAML::BeginSeq << 1 << 2 << SK_YAML::EndSeq;
			out << SK_YAML::Value << SK_YAML::BeginMap << SK_YAML::Key << "a" << SK_YAML::Value << "b" << SK_YAML::EndMap;
			out << SK_YAML::EndMap;
			out << SK_YAML::EndSeq;

			desiredOutput = "-\n  key 1: value 1\n  key 2: [a, b, c]\n-\n  ? [1, 2]\n  :\n    a: b";
		}

		void Null(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::BeginSeq;
			out << SK_YAML::Null;
			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "null value" << SK_YAML::Value << SK_YAML::Null;
			out << SK_YAML::Key << SK_YAML::Null << SK_YAML::Value << "null key";
			out << SK_YAML::EndMap;
			out << SK_YAML::EndSeq;

			desiredOutput = "- ~\n-\n  null value: ~\n  ~: null key";
		}

		void EscapedUnicode(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::EscapeNonAscii << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";

			desiredOutput = "\"$ \\xa2 \\u20ac \\U00024b62\"";
		}

		void Unicode(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
			desiredOutput = "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
		}

		void DoubleQuotedUnicode(SK_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << SK_YAML::DoubleQuoted << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
			desiredOutput = "\"\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2\"";
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// incorrect emitting

		void ExtraEndSeq(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::UNEXPECTED_END_SEQ;

			out << SK_YAML::BeginSeq;
			out << "Hello";
			out << "World";
			out << SK_YAML::EndSeq;
			out << SK_YAML::EndSeq;
		}

		void ExtraEndMap(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::UNEXPECTED_END_MAP;

			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "Hello" << SK_YAML::Value << "World";
			out << SK_YAML::EndMap;
			out << SK_YAML::EndMap;
		}

		void BadSingleQuoted(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::SINGLE_QUOTED_CHAR;

			out << SK_YAML::SingleQuoted << "Hello\nWorld";
		}

		void InvalidAnchor(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::INVALID_ANCHOR;

			out << SK_YAML::BeginSeq;
			out << SK_YAML::Anchor("new\nline") << "Test";
			out << SK_YAML::EndSeq;
		}

		void InvalidAlias(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::INVALID_ALIAS;

			out << SK_YAML::BeginSeq;
			out << SK_YAML::Alias("new\nline");
			out << SK_YAML::EndSeq;
		}

		void MissingKey(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::EXPECTED_KEY_TOKEN;

			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key" << SK_YAML::Value << "value";
			out << "missing key" << SK_YAML::Value << "value";
			out << SK_YAML::EndMap;
		}

		void MissingValue(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::EXPECTED_VALUE_TOKEN;

			out << SK_YAML::BeginMap;
			out << SK_YAML::Key << "key" << "value";
			out << SK_YAML::EndMap;
		}

		void UnexpectedKey(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::UNEXPECTED_KEY_TOKEN;

			out << SK_YAML::BeginSeq;
			out << SK_YAML::Key << "hi";
			out << SK_YAML::EndSeq;
		}

		void UnexpectedValue(SK_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = SK_YAML::ErrorMsg::UNEXPECTED_VALUE_TOKEN;

			out << SK_YAML::BeginSeq;
			out << SK_YAML::Value << "hi";
			out << SK_YAML::EndSeq;
		}
	}

	namespace {
		void RunEmitterTest(void (*test)(SK_YAML::Emitter&, std::string&), const std::string& name, int& passed, int& total) {
			SK_YAML::Emitter out;
			std::string desiredOutput;
			test(out, desiredOutput);
			std::string output = out.c_str();

			if(output == desiredOutput) {
				passed++;
			} else {
				std::cout << "Emitter test failed: " << name << "\n";
				std::cout << "Output:\n";
				std::cout << output << "<<<\n";
				std::cout << "Desired output:\n";
				std::cout << desiredOutput << "<<<\n";
			}
			total++;
		}

		void RunEmitterErrorTest(void (*test)(SK_YAML::Emitter&, std::string&), const std::string& name, int& passed, int& total) {
			SK_YAML::Emitter out;
			std::string desiredError;
			test(out, desiredError);
			std::string lastError = out.GetLastError();
			if(!out.good() && lastError == desiredError) {
				passed++;
			} else {
				std::cout << "Emitter test failed: " << name << "\n";
				if(out.good())
					std::cout << "No error detected\n";
				else
					std::cout << "Detected error: " << lastError << "\n";
				std::cout << "Expected error: " << desiredError << "\n";
			}
			total++;
		}
	}

	bool RunEmitterTests()
	{
		int passed = 0;
		int total = 0;
		RunEmitterTest(&Emitter::SimpleScalar, "simple scalar", passed, total);
		RunEmitterTest(&Emitter::SimpleSeq, "simple seq", passed, total);
		RunEmitterTest(&Emitter::SimpleFlowSeq, "simple flow seq", passed, total);
		RunEmitterTest(&Emitter::EmptyFlowSeq, "empty flow seq", passed, total);
		RunEmitterTest(&Emitter::NestedBlockSeq, "nested block seq", passed, total);
		RunEmitterTest(&Emitter::NestedFlowSeq, "nested flow seq", passed, total);
		RunEmitterTest(&Emitter::SimpleMap, "simple map", passed, total);
		RunEmitterTest(&Emitter::SimpleFlowMap, "simple flow map", passed, total);
		RunEmitterTest(&Emitter::MapAndList, "map and list", passed, total);
		RunEmitterTest(&Emitter::ListAndMap, "list and map", passed, total);
		RunEmitterTest(&Emitter::NestedBlockMap, "nested block map", passed, total);
		RunEmitterTest(&Emitter::NestedFlowMap, "nested flow map", passed, total);
		RunEmitterTest(&Emitter::MapListMix, "map list mix", passed, total);
		RunEmitterTest(&Emitter::SimpleLongKey, "simple long key", passed, total);
		RunEmitterTest(&Emitter::SingleLongKey, "single long key", passed, total);
		RunEmitterTest(&Emitter::ComplexLongKey, "complex long key", passed, total);
		RunEmitterTest(&Emitter::AutoLongKey, "auto long key", passed, total);
		RunEmitterTest(&Emitter::ScalarFormat, "scalar format", passed, total);
		RunEmitterTest(&Emitter::AutoLongKeyScalar, "auto long key scalar", passed, total);
		RunEmitterTest(&Emitter::LongKeyFlowMap, "long key flow map", passed, total);
		RunEmitterTest(&Emitter::BlockMapAsKey, "block map as key", passed, total);
		RunEmitterTest(&Emitter::AliasAndAnchor, "alias and anchor", passed, total);
		RunEmitterTest(&Emitter::AliasAndAnchorWithNull, "alias and anchor with null", passed, total);
		RunEmitterTest(&Emitter::ComplexDoc, "complex doc", passed, total);
		RunEmitterTest(&Emitter::STLContainers, "STL containers", passed, total);
		RunEmitterTest(&Emitter::SimpleComment, "simple comment", passed, total);
		RunEmitterTest(&Emitter::MultiLineComment, "multi-line comment", passed, total);
		RunEmitterTest(&Emitter::ComplexComments, "complex comments", passed, total);
		RunEmitterTest(&Emitter::Indentation, "indentation", passed, total);
		RunEmitterTest(&Emitter::SimpleGlobalSettings, "simple global settings", passed, total);
		RunEmitterTest(&Emitter::ComplexGlobalSettings, "complex global settings", passed, total);
		RunEmitterTest(&Emitter::Null, "null", passed, total);
		RunEmitterTest(&Emitter::EscapedUnicode, "escaped unicode", passed, total);
		RunEmitterTest(&Emitter::Unicode, "unicode", passed, total);
		RunEmitterTest(&Emitter::DoubleQuotedUnicode, "double quoted unicode", passed, total);

		RunEmitterErrorTest(&Emitter::ExtraEndSeq, "extra EndSeq", passed, total);
		RunEmitterErrorTest(&Emitter::ExtraEndMap, "extra EndMap", passed, total);
		RunEmitterErrorTest(&Emitter::BadSingleQuoted, "bad single quoted string", passed, total);
		RunEmitterErrorTest(&Emitter::InvalidAnchor, "invalid anchor", passed, total);
		RunEmitterErrorTest(&Emitter::InvalidAlias, "invalid alias", passed, total);
		RunEmitterErrorTest(&Emitter::MissingKey, "missing key", passed, total);
		RunEmitterErrorTest(&Emitter::MissingValue, "missing value", passed, total);
		RunEmitterErrorTest(&Emitter::UnexpectedKey, "unexpected key", passed, total);
		RunEmitterErrorTest(&Emitter::UnexpectedValue, "unexpected value", passed, total);

		std::cout << "Emitter tests: " << passed << "/" << total << " passed\n";
		return passed == total;
	}
}

