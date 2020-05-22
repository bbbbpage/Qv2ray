#include "libs/QJsonStruct/QJsonIO.hpp"

#include <QJsonObject>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("QJsonIO Get Simple Value")
{
    const auto obj = QJsonObject{
        { "string", "a quick brown fox jumps over the lazy dog" }, //
        { "integer", -32767 },                                     //
        { "boolean", true },                                       //
        { "decimal", 0.618 },                                      //
    };
    const auto arr = QJsonArray{ obj };

    SECTION("Get Array Object")
    {
        const auto val = QJsonIO::GetValue(arr, 0);
        REQUIRE(val.isObject());
        REQUIRE(val.toObject() == obj);
    }

    SECTION("Get Object String")
    {
        const auto val = QJsonIO::GetValue(obj, "string");
        REQUIRE(val.isString());
        REQUIRE(val.toString() == obj["string"].toString());
    }

    SECTION("Get Object Integer")
    {
        const auto val = QJsonIO::GetValue(obj, "integer");
        REQUIRE(val.toInt() == obj["integer"].toInt());
    }

    SECTION("Get Object Boolean")
    {
        const auto val = QJsonIO::GetValue(obj, "boolean");
        REQUIRE(val.isBool());
        REQUIRE(val.toBool() == obj["boolean"].toBool());
    }

    SECTION("Get Object Decimal")
    {
        const auto val = QJsonIO::GetValue(obj, "decimal");
        REQUIRE(val.isDouble());
        REQUIRE(val.toDouble() == obj["decimal"].toDouble());
    }
}

TEST_CASE("QJsonIO Set Simple Value")
{
    auto obj = QJsonObject{};
    auto arr = QJsonArray{ obj };

    SECTION("Set Object String")
    {
        QJsonIO::SetValue(obj, "coel loves felix", "string");
        const auto val = QJsonIO::GetValue(obj, "string");
        REQUIRE(val.isString());
        REQUIRE(val.toString().toStdString() == "coel loves felix");
    }

    SECTION("Set Object Decimal")
    {
        QJsonIO::SetValue(obj, 13.14, "decimal");
        const auto val = QJsonIO::GetValue(obj, "decimal");
        REQUIRE(val.isDouble());
        REQUIRE(val.toDouble() == 13.14);
    }

    SECTION("Set Object Integer")
    {
        QJsonIO::SetValue(obj, 114514, "integer");
        const auto val = QJsonIO::GetValue(obj, "integer");
        REQUIRE(val.toInt() == 114514);
    }

    SECTION("Set Object Boolean")
    {
        QJsonIO::SetValue(obj, true, "boolean");
        const auto val = QJsonIO::GetValue(obj, "boolean");
        REQUIRE(val.isBool());
        REQUIRE(val.toBool() == true);
    }
}
