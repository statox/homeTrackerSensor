// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2025, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

#include <string>

using namespace ArduinoJson::detail;

static void testCodepoint(uint32_t codepoint, std::string expected) {
  ResourceManager resources;
  StringBuilder str(&resources);
  str.startString();

  CAPTURE(codepoint);
  Utf8::encodeCodepoint(codepoint, str);

  REQUIRE(str.str().c_str() == expected);
}

TEST_CASE("Utf8::encodeCodepoint()") {
  SECTION("U+0000") {
    testCodepoint(0x0000, "");
  }

  SECTION("U+0001") {
    testCodepoint(0x0001, "\x01");
  }

  SECTION("U+007F") {
    testCodepoint(0x007F, "\x7f");
  }

  SECTION("U+0080") {
    testCodepoint(0x0080, "\xc2\x80");
  }

  SECTION("U+07FF") {
    testCodepoint(0x07FF, "\xdf\xbf");
  }

  SECTION("U+0800") {
    testCodepoint(0x0800, "\xe0\xa0\x80");
  }

  SECTION("U+FFFF") {
    testCodepoint(0xFFFF, "\xef\xbf\xbf");
  }

  SECTION("U+10000") {
    testCodepoint(0x10000, "\xf0\x90\x80\x80");
  }

  SECTION("U+10FFFF") {
    testCodepoint(0x10FFFF, "\xf4\x8f\xbf\xbf");
  }
}
