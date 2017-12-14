// adventofcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <cassert>

#include "utils.h"
#include "glm/glm.hpp"

using namespace std;

void ShowResult(const std::string& strName, int val)
{
    std::cout << strName << ": " << val << std::endl;
}



int main()
{
    using ringItr = RingIterator<char, string>;
    using ringItrVec = RingIterator<string, std::vector<string>>;

    // Part 1:1
    // Find matching pairs, wrap at the end
    string str1("21752342814933766938172121674976879111362417653261522357855816893656462449168377359285244818489723869987861247912289729579296691684761143544956991583942215236568961875851755854977946147178746464675227699149925227227137557479769948569788884399379821111382536722699575759474473273939756348992714667963596189765734743169489599125771443348193383566159843593541134749392569865481578359825844394454173219857919349341442148282229689541561169341622222354651397342928678496478671339383923769856425795211323673389723181967933933832711545885653952861879231537976292517866354812943192728263269524735698423336673735158993853556148833861327959262254756647827739145283577793481526768156921138428318939361859721778556264519643435871835744859243167227889562738712953651128317624673985213525897522378259178625416722152155728615936587369515254936828668564857283226439881266871945998796488472249182538883354186573925183152663862683995449671663285775397453876262722567452435914777363522817594741946638986571793655889466419895996924122915777224499481496837343194149123735355268151941712871245863553836953349887831949788869852929147849489265325843934669999391846286319268686789372513976522282587526866148166337215961493536262851512218794139272361292811529888161198799297966893366553115353639298256788819385272471187213579185523521341651117947676785341146235441411441813242514813227821843819424619974979886871646621918865274574538951761567855845681272364646138584716333599843835167373525248547542442942583122624534494442516259616973235858469131159773167334953658673271599748942956981954699444528689628848694446818825465485122869742839711471129862632128635779658365756362863627135983617613332849756371986376967117549251566281992964573929655589313871976556784849231916513831538254812347116253949818633527185174221565279775766742262687713114114344843534958833372634182176866315441583887177759222598853735114191874277711434653854816841589229914164681364497429324463193669337827467661773833517841763711156376147664749175267212562321567728575765844893232718971471289841171642868948852136818661741238178676857381583155547755219837116125995361896562498721571413742");
    ShowResult("P1,1", inner_product(str1.begin(),       // Start of string
        str1.end(),                           // End of string
        ringItr(str1, 1),                     // Start + 1, with wrap
        0,                                    // Start sum
        [](int a, int b) { return a + b; },   // Accumulate function
        [](const char& ch1, const char& ch2) { return ch1 == ch2 ? (ch1 - '0') : 0;  }));  // Compare function

    // Part 1:2
    // Find matching half size away, with wrap
    ShowResult("P1,2", inner_product(str1.begin(),
        str1.end(),
        ringItr(str1, (str1.size() / 2)),
        0,
        [](int a, int b) { return a + b; },
        [](const char& ch1, const char& ch2) { return ch1 == ch2 ? (ch1 - '0') : 0;  }));

    // Part 2:1
    string str2 = R"(
    116	1259	1045	679	1334	157	277	1217	218	641	1089	136	247	1195	239	834
    269	1751	732	3016	260	6440	5773	4677	306	230	6928	7182	231	2942	2738	3617
    644	128	89	361	530	97	35	604	535	297	599	121	567	106	114	480
    105	408	120	363	430	102	137	283	123	258	19	101	181	477	463	279
    873	116	840	105	285	238	540	22	117	125	699	953	920	106	113	259
    3695	161	186	2188	3611	2802	157	2154	3394	145	2725	1327	3741	2493	3607	4041
    140	1401	110	119	112	1586	125	937	1469	1015	879	1798	122	1151	100	926
    2401	191	219	607	267	2362	932	2283	889	2567	2171	2409	1078	2247	2441	245
    928	1142	957	1155	922	1039	452	285	467	305	506	221	281	59	667	232
    3882	1698	170	5796	2557	173	1228	4630	174	3508	5629	4395	180	5100	2814	2247
    396	311	223	227	340	313	355	469	229	162	107	76	363	132	453	161
    627	1331	1143	1572	966	388	198	2068	201	239	176	1805	1506	1890	1980	1887
    3390	5336	1730	4072	5342	216	3823	85	5408	5774	247	5308	232	256	5214	787
    176	1694	1787	1586	3798	4243	157	4224	3603	2121	3733	851	2493	4136	148	153
    2432	4030	3397	4032	3952	2727	157	3284	3450	3229	4169	3471	4255	155	127	186
    919	615	335	816	138	97	881	790	855	89	451	789	423	108	95	116
    )";

    // P2, 1: Find max/min for each array line, sum the min/max range into a total for all lines
    auto arrayLines = GetIntegerGrid(str2);
    ShowResult("P2,1", accumulate(arrayLines.begin(), arrayLines.end(), 0, [](int range, const vector<int>& vals)
    {
        // Gather min max for row
        auto minMax = minmax_element(vals.begin(), vals.end());
        return range + int(*minMax.second - *minMax.first);
    }));

    // Find even divisors
    // Find the pair of numbers that divides and sum it
    ShowResult("P2,2", accumulate(arrayLines.begin(), arrayLines.end(), 0, [](int total, vector<int>& vals)
    {
        return total + accumulate_pairs(vals, 0, [](auto ret, auto v1, auto v2)
        {
            return ret + ((v1 % v2 == 0) ? (v1 / v2) : 0);
        });
    }));

    // P3, 1: Spiral Memory
    auto coord = UlamIndexToCoords(368078);
    ShowResult("P3,1", std::abs(coord.x) + std::abs(coord.y));

    system("pause");
    return 0;
}

