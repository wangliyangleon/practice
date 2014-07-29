#include <iostream>
#include <string>
#include <assert.h>
#include <regex>

const std::string SPLIT_EXP  = "/";
const std::string YEAR_EXP = "(?!0000)[0-9]{4}";

// 4 6 9 11
const std::string MMM_30DAYS = "(Apr|Jun|Sep|Nov)";
const std::string DD_30DAYS = "(0[1-9]|[1-2][0-9]|30)";
// 1 3 5 7 8 10 12
const std::string MMM_31DAYS = "(Jan|Mar|May|Jul|Aug|Oct|Dec)";
const std::string DD_31DAYS = "(0[1-9]|[1-2][0-9]|3[01])";
// 2
const std::string MMM_FEB = "(Feb)";
const std::string DD_28DAYS = "(0[1-9]|1[0-9]|2[0-8])";

// leap year
const std::string LEAP_YEAR_EXP = "([0-9]{2}(0[48]|[2468][048]|[13579][26])|"
        "(0[48]|[2468][048]|[13579][26])00)";
const std::string FEB_29TH = MMM_FEB + SPLIT_EXP + std::string("29");

const std::string YYYYMMMDD_EXP = std::string("^((") + YEAR_EXP + SPLIT_EXP +
        std::string("((") + MMM_30DAYS + SPLIT_EXP + DD_30DAYS + std::string(")|") +
        std::string("(") + MMM_31DAYS + SPLIT_EXP + DD_31DAYS + std::string(")|") +
        std::string("(") + MMM_FEB + SPLIT_EXP + DD_28DAYS + std::string(")))|") + 
        std::string("(") + LEAP_YEAR_EXP + SPLIT_EXP + FEB_29TH + std::string("))$");

        /*
^(((?!0000)[0-9]{4}/(((Apr|Jun|Sep|Nov)/(0[1-9]|[1-2][0-9]|30))|((Jan|Mar|May|Jul|Aug|Oct|Dec)/(0[1-9]|[1-2][0-9]|3[01]))|((Feb)/(0[1-9]|1[0-9]|2[0-8]))))|(([0-9]{2}(0[48]|[2468][048]|[13579][26])|(0[48]|[2468][048]|[13579][26])00)/(Feb)/29))$
         */

int main() {
    const std::regex date_pattern(YYYYMMMDD_EXP.c_str());
    auto is_date_valid = [&date_pattern] (const char* str) -> bool {
        return std::regex_match(str, date_pattern);
    };
    // good cases
    assert(is_date_valid("0001/Jan/31"));
    assert(is_date_valid("1990/Apr/30"));
    assert(is_date_valid("2003/Feb/28"));
    assert(is_date_valid("2000/Feb/29"));
    assert(is_date_valid("2014/Jul/06"));
    // bad cases
    assert(!is_date_valid("0000/Jan/31"));
    assert(!is_date_valid("1990/Mar/00"));
    assert(!is_date_valid("1900/Feb/29"));
    assert(!is_date_valid("2000/Apr/31"));
    assert(!is_date_valid("2014/abc/01"));
    assert(!is_date_valid("1997/Jun/1"));

    std::cout << "All test cases passed ;-P" << std::endl;

    return 0;
}
