#pragma once

#include <memory>
#include <string>
class People;
class Card
{
public:
    std::string number;
    Card(const std::string &num, std::shared_ptr<People> owner);
    void show_ower() const;

private:
    std::weak_ptr<People> owner;
};
