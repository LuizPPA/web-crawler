#include<sstream>
#include<iostream>
#include<codecvt>
#include <locale>
#include<algorithm>

#include"../include/term-sanitizer.hpp"

namespace web_crawler {

    bool TermSanitizer::char_is_in(wchar_t c, const std::pair<int, int> intervals[], int n){
        for(int i = 0; i < n; i++){
            if(c >= intervals[i].first && c <= intervals[i].second){
                return true;
            }
        }
        return false;
    }

    bool TermSanitizer::char_is_in(wchar_t c, const std::pair<int, int> interval){
        return (c >= interval.first && c <= interval.second);
    }

    char TermSanitizer::map(wchar_t c, const std::pair<std::pair<int, int>, char> intervals[], int n){
        if(c >= 160){
            std::cout << c;
        }
        for(int i = 0; i < n; i++){
            if(TermSanitizer::char_is_in(c, intervals[i].first)){
                return intervals[i].second;
            }
        }
        return (char)c;
    }

    std::wstring TermSanitizer::to_wstring(std::string str){
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wstr = converter.from_bytes(str);
        return wstr;
    }

    std::string TermSanitizer::sanitize(std::string term){
        std::transform(term.begin(), term.end(), term.begin(), ::tolower);
        std::wstring ws_term = TermSanitizer::to_wstring(term);
        std::stringstream stream;
        std::wstring::iterator it = ws_term.begin();
        while(it != ws_term.end()){
            if(!TermSanitizer::char_is_in(*it, TermSanitizer::exclude_intervals, EXCLUDE_INTERVALS_SIZE)){
                stream << TermSanitizer::map(*it, TermSanitizer::mapings, MAPINGS_SIZE);
            }
            ++it;
        }
        return stream.str();
    }
}