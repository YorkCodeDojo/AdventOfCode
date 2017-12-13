#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include "StringUtils.h"
#include <chrono>
#include "ringitr.h"

template<typename C, typename count, typename Op>
count accumulate_pairs(C& container, count c, Op fun)
{
    for (auto it = container.begin(); it != container.end(); it++)
    {
        for (auto it2 = it + 1; it2 != container.end(); it2++)
        {
            c = fun(c, *it, *it2);
            c = fun(c, *it2, *it);
        }
    }
    return c;
}

static std::vector<std::vector<int>> GetIntegerGrid(const std::string& str)
{
    // Gather into array
    std::vector<std::string> lines = StringUtils::SplitLines(str);
    std::vector<std::vector<int>> arrayLines;
    for (auto& line : lines)
    {
        std::vector<int> vals;
        auto strVals = StringUtils::Split(line, "\t ");
        std::transform(strVals.begin(), strVals.end(), back_inserter(vals), [](const std::string& str) { return stoi(str); });
        if (!vals.empty())
        {
            arrayLines.push_back(vals);
        }
    }
    return arrayLines;
}

class Timer
{
public:
    Timer(const std::string& strName)
        : m_strName(strName)
    {
        start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    void Stop()
    {
        if (!finished)
        {
            auto now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            std::cout << m_strName << ": " << (now - start) << "us" << std::endl;
            finished = true;
        }
    }

    ~Timer()
    {
        Stop();
    }
private:
    bool finished = false;
    int64_t start;
    int64_t now;
    std::string m_strName;
};
