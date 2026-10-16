#pragma once
#include <string>
#include <cstdint>
class Event {

  public:
    std::string title;
    int64_t startDate;
    int64_t endDate;
    bool allDay;

};
