#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Json4CPP;
using namespace Json4CPP::Detail;

namespace Json4CPP::Test
{
  TEST_CLASS(JsonObjectTest)
  {
  public:
    TEST_METHOD(TestConstructorDefault)
    {
      auto object = JsonObject();
      Assert::AreEqual(0i64, object.Size());
    }

    TEST_METHOD(TestConstructorJsonBuilder)
    {
      JsonObject object;

      Assert::ExpectException<exception>([&]() { object = JsonBuilder(); });

      // JsonBuilder from VALUE
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(VALUE(nullptr_t())); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(VALUE(wstring())); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(VALUE(bool())); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(VALUE(double())); });
      object = JsonBuilder(VALUE(JsonObject({ { L"Key1", 1 }, { L"Key2", 2 } })));
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(VALUE(JsonArray())); });

      // JsonBuilder constructors
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(nullptr_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(L""); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(wstring()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(bool()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(char()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(int8_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(uint8_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(int16_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(uint16_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(int32_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(uint32_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(int64_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(uint64_t()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(float()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(double()); });
      object = JsonBuilder(JsonObject({ { L"Key1", 1 }, { L"Key2", 2 } }));
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(JsonArray()); });
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(Json()); });
      object = JsonBuilder(Json(JsonObject({ { L"Key1", 1 }, { L"Key2", 2 } })));
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);

      // JsonBuilder from initializer_list
      Assert::ExpectException<exception>([&]() { object = JsonBuilder({ L"Key1", 1 }); });
      object = JsonBuilder({ { L"Key1", 1 } });
      Assert::AreEqual(1i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      object = JsonBuilder({ { L"Key1", 1 }, { L"Key2", 2 } });
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);

      // JsonBuilder from vector
      Assert::ExpectException<exception>([&]() { object = JsonBuilder(vector<JsonBuilder>{ L"Key1", 1 }); });
      object = JsonBuilder(vector<JsonBuilder>{ { L"Key1", 1 } });
      Assert::AreEqual(1i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      object = JsonBuilder(vector<JsonBuilder>{ { L"Key1", 1 }, { L"Key2", 2 } });
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);
    }

    TEST_METHOD(TestConstructorInitializerList)
    {
      JsonObject object;

      object = { { L"Key1", 1 } };
      Assert::AreEqual(1i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      object = { { L"Key1", 1 }, { L"Key2", 2 } };
      Assert::AreEqual(2i64, object.Size());
      Assert::AreEqual(L"Key1"s, object.Keys()[0]);
      Assert::AreEqual(L"Key2"s, object.Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Key2"]);
      object = {
        { L"Null", nullptr },
        { L"String", L"Test" },
        { L"Boolean", true },
        { L"Number", 1337 },
        { L"Object", {
          { L"Key1", 1 },
          { L"Key2", 2 } }
        },
        { L"Array", { 1, 2, 3 } },
      };
      Assert::AreEqual(6i64, object.Size());
      Assert::AreEqual(L"Null"s, object.Keys()[0]);
      Assert::AreEqual(L"String"s, object.Keys()[1]);
      Assert::AreEqual(L"Boolean"s, object.Keys()[2]);
      Assert::AreEqual(L"Number"s, object.Keys()[3]);
      Assert::AreEqual(L"Object"s, object.Keys()[4]);
      Assert::AreEqual(L"Array"s, object.Keys()[5]);
      Assert::AreEqual<Json>(nullptr, object[L"Null"]);
      Assert::AreEqual<Json>(L"Test", object[L"String"]);
      Assert::AreEqual<Json>(true, object[L"Boolean"]);
      Assert::AreEqual<Json>(1337, object[L"Number"]);
      Assert::AreEqual<Json>({ { L"Key1", 1 }, { L"Key2", 2 } }, object[L"Object"]);
      Assert::AreEqual<Json>({ 1, 2, 3 }, object[L"Array"]);
      Assert::AreEqual(L"Key1"s, object[L"Object"].Keys()[0]);
      Assert::AreEqual(L"Key2"s, object[L"Object"].Keys()[1]);
      Assert::AreEqual<Json>(1, object[L"Object"][L"Key1"]);
      Assert::AreEqual<Json>(2, object[L"Object"][L"Key2"]);
      Assert::AreEqual(3i64, object[L"Array"].Size());
      Assert::AreEqual<Json>(1, object[L"Array"][0]);
      Assert::AreEqual<Json>(2, object[L"Array"][1]);
      Assert::AreEqual<Json>(3, object[L"Array"][2]);
    }
  };
}