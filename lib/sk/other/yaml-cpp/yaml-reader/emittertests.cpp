#include "tests.h"
#include "yaml.h"

namespace Test
{
	namespace Emitter {
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// correct emitting

		void SimpleScalar(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << "Hello, World!";
			desiredOutput = "Hello, World!";
		}

		void SimpleSeq(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginSeq;
			out << "eggs";
			out << "bread";
			out << "milk";
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- eggs\n- bread\n- milk";
		}

		void SimpleFlowSeq(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::Flow;
			out << LOCAL_YAML::BeginSeq;
			out << "Larry";
			out << "Curly";
			out << "Moe";
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "[Larry, Curly, Moe]";
		}

		void EmptyFlowSeq(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::Flow;
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "[]";
		}

		void NestedBlockSeq(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginSeq;
			out << "item 1";
			out << LOCAL_YAML::BeginSeq << "subitem 1" << "subitem 2" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- item 1\n-\n  - subitem 1\n  - subitem 2";
		}

		void NestedFlowSeq(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginSeq;
			out << "one";
			out << LOCAL_YAML::Flow << LOCAL_YAML::BeginSeq << "two" << "three" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- one\n- [two, three]";
		}

		void SimpleMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name";
			out << LOCAL_YAML::Value << "Ryan Braun";
			out << LOCAL_YAML::Key << "position";
			out << LOCAL_YAML::Value << "3B";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "name: Ryan Braun\nposition: 3B";
		}

		void SimpleFlowMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::Flow;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "shape";
			out << LOCAL_YAML::Value << "square";
			out << LOCAL_YAML::Key << "color";
			out << LOCAL_YAML::Value << "blue";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "{shape: square, color: blue}";
		}

		void MapAndList(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name";
			out << LOCAL_YAML::Value << "Barack Obama";
			out << LOCAL_YAML::Key << "children";
			out << LOCAL_YAML::Value << LOCAL_YAML::BeginSeq << "Sasha" << "Malia" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "name: Barack Obama\nchildren:\n  - Sasha\n  - Malia";
		}

		void ListAndMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginSeq;
			out << "item 1";
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "pens" << LOCAL_YAML::Value << 8;
			out << LOCAL_YAML::Key << "pencils" << LOCAL_YAML::Value << 14;
			out << LOCAL_YAML::EndMap;
			out << "item 2";
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- item 1\n-\n  pens: 8\n  pencils: 14\n- item 2";
		}

		void NestedBlockMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name";
			out << LOCAL_YAML::Value << "Fred";
			out << LOCAL_YAML::Key << "grades";
			out << LOCAL_YAML::Value;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "algebra" << LOCAL_YAML::Value << "A";
			out << LOCAL_YAML::Key << "physics" << LOCAL_YAML::Value << "C+";
			out << LOCAL_YAML::Key << "literature" << LOCAL_YAML::Value << "B";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "name: Fred\ngrades:\n  algebra: A\n  physics: C+\n  literature: B";
		}

		void NestedFlowMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::Flow;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name";
			out << LOCAL_YAML::Value << "Fred";
			out << LOCAL_YAML::Key << "grades";
			out << LOCAL_YAML::Value;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "algebra" << LOCAL_YAML::Value << "A";
			out << LOCAL_YAML::Key << "physics" << LOCAL_YAML::Value << "C+";
			out << LOCAL_YAML::Key << "literature" << LOCAL_YAML::Value << "B";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "{name: Fred, grades: {algebra: A, physics: C+, literature: B}}";
		}

		void MapListMix(LOCAL_YAML::Emitter& out, std::string& desiredOutput) {
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name";
			out << LOCAL_YAML::Value << "Bob";
			out << LOCAL_YAML::Key << "position";
			out << LOCAL_YAML::Value;
			out << LOCAL_YAML::Flow << LOCAL_YAML::BeginSeq << 2 << 4 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Key << "invincible" << LOCAL_YAML::Value << LOCAL_YAML::OnOffBool << false;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "name: Bob\nposition: [2, 4]\ninvincible: off";
		}

		void SimpleLongKey(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::LongKey;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "height";
			out << LOCAL_YAML::Value << "5'9\"";
			out << LOCAL_YAML::Key << "weight";
			out << LOCAL_YAML::Value << 145;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "? height\n: 5'9\"\n? weight\n: 145";
		}

		void SingleLongKey(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "age";
			out << LOCAL_YAML::Value << "24";
			out << LOCAL_YAML::LongKey << LOCAL_YAML::Key << "height";
			out << LOCAL_YAML::Value << "5'9\"";
			out << LOCAL_YAML::Key << "weight";
			out << LOCAL_YAML::Value << 145;
			out << LOCAL_YAML::EndMap;

			desiredOutput = "age: 24\n? height\n: 5'9\"\nweight: 145";
		}

		void ComplexLongKey(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::LongKey;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << LOCAL_YAML::BeginSeq << 1 << 3 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Value << "monster";
			out << LOCAL_YAML::Key << LOCAL_YAML::Flow << LOCAL_YAML::BeginSeq << 2 << 0 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Value << "demon";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "?\n  - 1\n  - 3\n: monster\n? [2, 0]\n: demon";
		}

		void AutoLongKey(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << LOCAL_YAML::BeginSeq << 1 << 3 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Value << "monster";
			out << LOCAL_YAML::Key << LOCAL_YAML::Flow << LOCAL_YAML::BeginSeq << 2 << 0 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Value << "demon";
			out << LOCAL_YAML::Key << "the origin";
			out << LOCAL_YAML::Value << "angel";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "?\n  - 1\n  - 3\n: monster\n? [2, 0]\n: demon\nthe origin: angel";
		}

		void ScalarFormat(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << "simple scalar";
			out << LOCAL_YAML::SingleQuoted << "explicit single-quoted scalar";
			out << LOCAL_YAML::DoubleQuoted << "explicit double-quoted scalar";
			out << "auto-detected\ndouble-quoted scalar";
			out << "a non-\"auto-detected\" double-quoted scalar";
			out << LOCAL_YAML::Literal << "literal scalar\nthat may span\nmany, many\nlines and have \"whatever\" crazy\tsymbols that we like";
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- simple scalar\n- 'explicit single-quoted scalar'\n- \"explicit double-quoted scalar\"\n- \"auto-detected\\x0adouble-quoted scalar\"\n- a non-\"auto-detected\" double-quoted scalar\n- |\n  literal scalar\n  that may span\n  many, many\n  lines and have \"whatever\" crazy\tsymbols that we like";
		}

		void AutoLongKeyScalar(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << LOCAL_YAML::Literal << "multi-line\nscalar";
			out << LOCAL_YAML::Value << "and its value";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "? |\n  multi-line\n  scalar\n: and its value";
		}

		void LongKeyFlowMap(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::Flow;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "simple key";
			out << LOCAL_YAML::Value << "and value";
			out << LOCAL_YAML::LongKey << LOCAL_YAML::Key << "long key";
			out << LOCAL_YAML::Value << "and its value";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "{simple key: and value, ? long key: and its value}";
		}

		void BlockMapAsKey(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key" << LOCAL_YAML::Value << "value";
			out << LOCAL_YAML::Key << "next key" << LOCAL_YAML::Value << "next value";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::Value;
			out << "total value";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "?\n  key: value\n  next key: next value\n: total value";
		}

		void AliasAndAnchor(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Anchor("fred");
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "name" << LOCAL_YAML::Value << "Fred";
			out << LOCAL_YAML::Key << "age" << LOCAL_YAML::Value << 42;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::Alias("fred");
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- &fred\n  name: Fred\n  age: 42\n- *fred";
		}

		void AliasAndAnchorWithNull(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Anchor("fred") << LOCAL_YAML::Null;
			out << LOCAL_YAML::Alias("fred");
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- &fred ~\n- *fred";
		}

		void ComplexDoc(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "receipt";
			out << LOCAL_YAML::Value << "Oz-Ware Purchase Invoice";
			out << LOCAL_YAML::Key << "date";
			out << LOCAL_YAML::Value << "2007-08-06";
			out << LOCAL_YAML::Key << "customer";
			out << LOCAL_YAML::Value;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "given";
			out << LOCAL_YAML::Value << "Dorothy";
			out << LOCAL_YAML::Key << "family";
			out << LOCAL_YAML::Value << "Gale";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::Key << "items";
			out << LOCAL_YAML::Value;
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "part_no";
			out << LOCAL_YAML::Value << "A4786";
			out << LOCAL_YAML::Key << "descrip";
			out << LOCAL_YAML::Value << "Water Bucket (Filled)";
			out << LOCAL_YAML::Key << "price";
			out << LOCAL_YAML::Value << 1.47;
			out << LOCAL_YAML::Key << "quantity";
			out << LOCAL_YAML::Value << 4;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "part_no";
			out << LOCAL_YAML::Value << "E1628";
			out << LOCAL_YAML::Key << "descrip";
			out << LOCAL_YAML::Value << "High Heeled \"Ruby\" Slippers";
			out << LOCAL_YAML::Key << "price";
			out << LOCAL_YAML::Value << 100.27;
			out << LOCAL_YAML::Key << "quantity";
			out << LOCAL_YAML::Value << 1;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Key << "bill-to";
			out << LOCAL_YAML::Value << LOCAL_YAML::Anchor("id001");
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "street";
			out << LOCAL_YAML::Value << LOCAL_YAML::Literal << "123 Tornado Alley\nSuite 16";
			out << LOCAL_YAML::Key << "city";
			out << LOCAL_YAML::Value << "East Westville";
			out << LOCAL_YAML::Key << "state";
			out << LOCAL_YAML::Value << "KS";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::Key << "ship-to";
			out << LOCAL_YAML::Value << LOCAL_YAML::Alias("id001");
			out << LOCAL_YAML::EndMap;

			desiredOutput = "receipt: Oz-Ware Purchase Invoice\ndate: 2007-08-06\ncustomer:\n  given: Dorothy\n  family: Gale\nitems:\n  -\n    part_no: A4786\n    descrip: Water Bucket (Filled)\n    price: 1.47\n    quantity: 4\n  -\n    part_no: E1628\n    descrip: High Heeled \"Ruby\" Slippers\n    price: 100.27\n    quantity: 1\nbill-to: &id001\n  street: |\n    123 Tornado Alley\n    Suite 16\n  city: East Westville\n  state: KS\nship-to: *id001";
		}

		void STLContainers(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			std::vector <int> primes;
			primes.push_back(2);
			primes.push_back(3);
			primes.push_back(5);
			primes.push_back(7);
			primes.push_back(11);
			primes.push_back(13);
			out << LOCAL_YAML::Flow << primes;
			std::map <std::string, int> ages;
			ages["Daniel"] = 26;
			ages["Jesse"] = 24;
			out << ages;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- [2, 3, 5, 7, 11, 13]\n-\n  Daniel: 26\n  Jesse: 24";
		}

		void SimpleComment(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "method";
			out << LOCAL_YAML::Value << "least squares" << LOCAL_YAML::Comment("should we change this method?");
			out << LOCAL_YAML::EndMap;

			desiredOutput = "method: least squares  # should we change this method?";
		}

		void MultiLineComment(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << "item 1" << LOCAL_YAML::Comment("really really long\ncomment that couldn't possibly\nfit on one line");
			out << "item 2";
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- item 1  # really really long\n          # comment that couldn't possibly\n          # fit on one line\n- item 2";
		}

		void ComplexComments(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::LongKey << LOCAL_YAML::Key << "long key" << LOCAL_YAML::Comment("long key");
			out << LOCAL_YAML::Value << "value";
			out << LOCAL_YAML::EndMap;

			desiredOutput = "? long key  # long key\n: value";
		}

		void Indentation(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::Indent(4);
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key 1" << LOCAL_YAML::Value << "value 1";
			out << LOCAL_YAML::Key << "key 2" << LOCAL_YAML::Value << LOCAL_YAML::BeginSeq << "a" << "b" << "c" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "-\n    key 1: value 1\n    key 2:\n        - a\n        - b\n        - c";
		}

		void SimpleGlobalSettings(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out.SetIndent(4);
			out.SetMapFormat(LOCAL_YAML::LongKey);

			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key 1" << LOCAL_YAML::Value << "value 1";
			out << LOCAL_YAML::Key << "key 2" << LOCAL_YAML::Value << LOCAL_YAML::Flow << LOCAL_YAML::BeginSeq << "a" << "b" << "c" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "-\n    ? key 1\n    : value 1\n    ? key 2\n    : [a, b, c]";
		}

		void ComplexGlobalSettings(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Block;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key 1" << LOCAL_YAML::Value << "value 1";
			out << LOCAL_YAML::Key << "key 2" << LOCAL_YAML::Value;
			out.SetSeqFormat(LOCAL_YAML::Flow);
			out << LOCAL_YAML::BeginSeq << "a" << "b" << "c" << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << LOCAL_YAML::BeginSeq << 1 << 2 << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::Value << LOCAL_YAML::BeginMap << LOCAL_YAML::Key << "a" << LOCAL_YAML::Value << "b" << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "-\n  key 1: value 1\n  key 2: [a, b, c]\n-\n  ? [1, 2]\n  :\n    a: b";
		}

		void Null(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Null;
			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "null value" << LOCAL_YAML::Value << LOCAL_YAML::Null;
			out << LOCAL_YAML::Key << LOCAL_YAML::Null << LOCAL_YAML::Value << "null key";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndSeq;

			desiredOutput = "- ~\n-\n  null value: ~\n  ~: null key";
		}

		void EscapedUnicode(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::EscapeNonAscii << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";

			desiredOutput = "\"$ \\xa2 \\u20ac \\U00024b62\"";
		}

		void Unicode(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
			desiredOutput = "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
		}

		void DoubleQuotedUnicode(LOCAL_YAML::Emitter& out, std::string& desiredOutput)
		{
			out << LOCAL_YAML::DoubleQuoted << "\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2";
			desiredOutput = "\"\x24 \xC2\xA2 \xE2\x82\xAC \xF0\xA4\xAD\xA2\"";
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////////
		// incorrect emitting

		void ExtraEndSeq(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::UNEXPECTED_END_SEQ;

			out << LOCAL_YAML::BeginSeq;
			out << "Hello";
			out << "World";
			out << LOCAL_YAML::EndSeq;
			out << LOCAL_YAML::EndSeq;
		}

		void ExtraEndMap(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::UNEXPECTED_END_MAP;

			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "Hello" << LOCAL_YAML::Value << "World";
			out << LOCAL_YAML::EndMap;
			out << LOCAL_YAML::EndMap;
		}

		void BadSingleQuoted(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::SINGLE_QUOTED_CHAR;

			out << LOCAL_YAML::SingleQuoted << "Hello\nWorld";
		}

		void InvalidAnchor(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::INVALID_ANCHOR;

			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Anchor("new\nline") << "Test";
			out << LOCAL_YAML::EndSeq;
		}

		void InvalidAlias(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::INVALID_ALIAS;

			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Alias("new\nline");
			out << LOCAL_YAML::EndSeq;
		}

		void MissingKey(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::EXPECTED_KEY_TOKEN;

			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key" << LOCAL_YAML::Value << "value";
			out << "missing key" << LOCAL_YAML::Value << "value";
			out << LOCAL_YAML::EndMap;
		}

		void MissingValue(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::EXPECTED_VALUE_TOKEN;

			out << LOCAL_YAML::BeginMap;
			out << LOCAL_YAML::Key << "key" << "value";
			out << LOCAL_YAML::EndMap;
		}

		void UnexpectedKey(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::UNEXPECTED_KEY_TOKEN;

			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Key << "hi";
			out << LOCAL_YAML::EndSeq;
		}

		void UnexpectedValue(LOCAL_YAML::Emitter& out, std::string& desiredError)
		{
			desiredError = LOCAL_YAML::ErrorMsg::UNEXPECTED_VALUE_TOKEN;

			out << LOCAL_YAML::BeginSeq;
			out << LOCAL_YAML::Value << "hi";
			out << LOCAL_YAML::EndSeq;
		}
	}

	namespace {
		void RunEmitterTest(void (*test)(LOCAL_YAML::Emitter&, std::string&), const std::string& name, int& passed, int& total) {
			LOCAL_YAML::Emitter out;
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

		void RunEmitterErrorTest(void (*test)(LOCAL_YAML::Emitter&, std::string&), const std::string& name, int& passed, int& total) {
			LOCAL_YAML::Emitter out;
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

