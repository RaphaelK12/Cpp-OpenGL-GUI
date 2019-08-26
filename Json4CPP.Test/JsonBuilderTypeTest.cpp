#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Json4CPP;
using namespace Json4CPP::Detail;

namespace Json4CPP::Test
{
  TEST_CLASS(JsonBuilderTypeTest)
  {
  public:
    TEST_METHOD(TestOperatorInsertion)
    {
      auto pairs = vector<pair<JsonBuilderType, wstring>>
      {
        { JsonBuilderType::Null   , L"Null"    },
        { JsonBuilderType::String , L"String"  },
        { JsonBuilderType::Boolean, L"Boolean" },
        { JsonBuilderType::Number , L"Number"  },
        { JsonBuilderType::Object , L"Object"  },
        { JsonBuilderType::Array  , L"Array"   },
        { JsonBuilderType::Pair   , L"Pair"    },
        { JsonBuilderType::Empty  , L"Empty"   },
        { JsonBuilderType::Simple , L"Simple"  },
        { JsonBuilderType::Complex, L"Complex" },
        { JsonBuilderType::Invalid, L"Invalid" },
      };
      for (auto& [input, expected] : pairs)
      {
        wostringstream os;
        os << input;
        Assert::AreEqual(expected, os.str());
      }
    }

    TEST_METHOD(TestOperatorEqual)
    {
      auto pairs = vector<tuple<JsonBuilderType, JsonBuilderType, bool>>
      {
        { JsonBuilderType::Null   , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Null   , JsonBuilderType::String , false },
        { JsonBuilderType::Null   , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Null   , JsonBuilderType::Number , false },
        { JsonBuilderType::Null   , JsonBuilderType::Object , false },
        { JsonBuilderType::Null   , JsonBuilderType::Array  , false },
        { JsonBuilderType::Null   , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Null   , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Null   , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Complex, false },
        { JsonBuilderType::Null   , JsonBuilderType::Invalid, false },
        { JsonBuilderType::String , JsonBuilderType::Null   , false },
        { JsonBuilderType::String , JsonBuilderType::String , true  },
        { JsonBuilderType::String , JsonBuilderType::Boolean, false },
        { JsonBuilderType::String , JsonBuilderType::Number , false },
        { JsonBuilderType::String , JsonBuilderType::Object , false },
        { JsonBuilderType::String , JsonBuilderType::Array  , false },
        { JsonBuilderType::String , JsonBuilderType::Pair   , false },
        { JsonBuilderType::String , JsonBuilderType::Empty  , false },
        { JsonBuilderType::String , JsonBuilderType::Simple , true  },
        { JsonBuilderType::String , JsonBuilderType::Complex, false },
        { JsonBuilderType::String , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Boolean, JsonBuilderType::Null   , false },
        { JsonBuilderType::Boolean, JsonBuilderType::String , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Number , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Object , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Array  , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Pair   , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Empty  , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Simple , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Complex, false },
        { JsonBuilderType::Boolean, JsonBuilderType::Invalid, false },
        { JsonBuilderType::Number , JsonBuilderType::Null   , false },
        { JsonBuilderType::Number , JsonBuilderType::String , false },
        { JsonBuilderType::Number , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Number , JsonBuilderType::Number , true  },
        { JsonBuilderType::Number , JsonBuilderType::Object , false },
        { JsonBuilderType::Number , JsonBuilderType::Array  , false },
        { JsonBuilderType::Number , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Number , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Number , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Number , JsonBuilderType::Complex, false },
        { JsonBuilderType::Number , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Object , JsonBuilderType::Null   , false },
        { JsonBuilderType::Object , JsonBuilderType::String , false },
        { JsonBuilderType::Object , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Object , JsonBuilderType::Number , false },
        { JsonBuilderType::Object , JsonBuilderType::Object , true  },
        { JsonBuilderType::Object , JsonBuilderType::Array  , false },
        { JsonBuilderType::Object , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Object , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Object , JsonBuilderType::Simple , false },
        { JsonBuilderType::Object , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Object , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Array  , JsonBuilderType::Null   , false },
        { JsonBuilderType::Array  , JsonBuilderType::String , false },
        { JsonBuilderType::Array  , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Array  , JsonBuilderType::Number , false },
        { JsonBuilderType::Array  , JsonBuilderType::Object , false },
        { JsonBuilderType::Array  , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Array  , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Array  , JsonBuilderType::Simple , false },
        { JsonBuilderType::Array  , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Array  , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Pair   , JsonBuilderType::Null   , false },
        { JsonBuilderType::Pair   , JsonBuilderType::String , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Pair   , JsonBuilderType::Number , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Object , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Array  , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Simple , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Empty  , JsonBuilderType::Null   , false },
        { JsonBuilderType::Empty  , JsonBuilderType::String , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Empty  , JsonBuilderType::Number , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Object , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Array  , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Simple , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Simple , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Simple , JsonBuilderType::String , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Simple , JsonBuilderType::Number , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Object , false },
        { JsonBuilderType::Simple , JsonBuilderType::Array  , false },
        { JsonBuilderType::Simple , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Simple , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Simple , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Complex, false },
        { JsonBuilderType::Simple , JsonBuilderType::Invalid, false },
        { JsonBuilderType::Complex, JsonBuilderType::Null   , false },
        { JsonBuilderType::Complex, JsonBuilderType::String , false },
        { JsonBuilderType::Complex, JsonBuilderType::Boolean, false },
        { JsonBuilderType::Complex, JsonBuilderType::Number , false },
        { JsonBuilderType::Complex, JsonBuilderType::Object , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Array  , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Simple , false },
        { JsonBuilderType::Complex, JsonBuilderType::Complex, true  },
        { JsonBuilderType::Complex, JsonBuilderType::Invalid, false },
        { JsonBuilderType::Invalid, JsonBuilderType::Null   , false },
        { JsonBuilderType::Invalid, JsonBuilderType::String , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Boolean, false },
        { JsonBuilderType::Invalid, JsonBuilderType::Number , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Object , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Array  , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Pair   , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Empty  , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Simple , false },
        { JsonBuilderType::Invalid, JsonBuilderType::Complex, false },
        { JsonBuilderType::Invalid, JsonBuilderType::Invalid, true  },
      };
      for (auto& [left, right, expected] : pairs)
      {
        Assert::AreEqual(expected, left == right);
      }
    }

    TEST_METHOD(TestOperatorNotEqual)
    {
      auto pairs = vector<tuple<JsonBuilderType, JsonBuilderType, bool>>
      {
        { JsonBuilderType::Null   , JsonBuilderType::Null   , false },
        { JsonBuilderType::Null   , JsonBuilderType::String , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Null   , JsonBuilderType::Number , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Object , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Null   , JsonBuilderType::Simple , false },
        { JsonBuilderType::Null   , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Null   , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::String , JsonBuilderType::Null   , true  },
        { JsonBuilderType::String , JsonBuilderType::String , false },
        { JsonBuilderType::String , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::String , JsonBuilderType::Number , true  },
        { JsonBuilderType::String , JsonBuilderType::Object , true  },
        { JsonBuilderType::String , JsonBuilderType::Array  , true  },
        { JsonBuilderType::String , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::String , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::String , JsonBuilderType::Simple , false },
        { JsonBuilderType::String , JsonBuilderType::Complex, true  },
        { JsonBuilderType::String , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Null   , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::String , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Boolean, false },
        { JsonBuilderType::Boolean, JsonBuilderType::Number , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Object , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Array  , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Simple , false },
        { JsonBuilderType::Boolean, JsonBuilderType::Complex, true  },
        { JsonBuilderType::Boolean, JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Number , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Number , JsonBuilderType::String , true  },
        { JsonBuilderType::Number , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Number , JsonBuilderType::Number , false },
        { JsonBuilderType::Number , JsonBuilderType::Object , true  },
        { JsonBuilderType::Number , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Number , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Number , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Number , JsonBuilderType::Simple , false },
        { JsonBuilderType::Number , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Number , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Object , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Object , JsonBuilderType::String , true  },
        { JsonBuilderType::Object , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Object , JsonBuilderType::Number , true  },
        { JsonBuilderType::Object , JsonBuilderType::Object , false },
        { JsonBuilderType::Object , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Object , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Object , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Object , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Object , JsonBuilderType::Complex, false },
        { JsonBuilderType::Object , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Array  , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Array  , JsonBuilderType::String , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Array  , JsonBuilderType::Number , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Object , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Array  , false },
        { JsonBuilderType::Array  , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Array  , JsonBuilderType::Complex, false },
        { JsonBuilderType::Array  , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::String , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Number , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Object , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Pair   , false },
        { JsonBuilderType::Pair   , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Pair   , JsonBuilderType::Complex, false },
        { JsonBuilderType::Pair   , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Null   , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::String , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Number , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Object , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Empty  , false },
        { JsonBuilderType::Empty  , JsonBuilderType::Simple , true  },
        { JsonBuilderType::Empty  , JsonBuilderType::Complex, false },
        { JsonBuilderType::Empty  , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Simple , JsonBuilderType::Null   , false },
        { JsonBuilderType::Simple , JsonBuilderType::String , false },
        { JsonBuilderType::Simple , JsonBuilderType::Boolean, false },
        { JsonBuilderType::Simple , JsonBuilderType::Number , false },
        { JsonBuilderType::Simple , JsonBuilderType::Object , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Array  , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Simple , JsonBuilderType::Simple , false },
        { JsonBuilderType::Simple , JsonBuilderType::Complex, true  },
        { JsonBuilderType::Simple , JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Complex, JsonBuilderType::Null   , true  },
        { JsonBuilderType::Complex, JsonBuilderType::String , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Complex, JsonBuilderType::Number , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Object , false },
        { JsonBuilderType::Complex, JsonBuilderType::Array  , false },
        { JsonBuilderType::Complex, JsonBuilderType::Pair   , false },
        { JsonBuilderType::Complex, JsonBuilderType::Empty  , false },
        { JsonBuilderType::Complex, JsonBuilderType::Simple , true  },
        { JsonBuilderType::Complex, JsonBuilderType::Complex, false },
        { JsonBuilderType::Complex, JsonBuilderType::Invalid, true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Null   , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::String , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Boolean, true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Number , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Object , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Array  , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Pair   , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Empty  , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Simple , true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Complex, true  },
        { JsonBuilderType::Invalid, JsonBuilderType::Invalid, false },
      };
      for (auto& [left, right, expected] : pairs)
      {
        Assert::AreEqual(expected, left != right);
      }
    }
  };
}