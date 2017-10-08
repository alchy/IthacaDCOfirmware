/*
 * adsr_attacks.h
 *
 *  Created on: 16. 9. 2015
 *      Author: Jindra
 */

#ifndef PROJ_ADSR_V0_18_ADSR_DIVIDERS_H_
#define PROJ_ADSR_V0_18_ADSR_DIVIDERS_H_

signed long const adsr_dividers[1024] = {
		447392426,  441834828,  436346267,  430925887,  425572840,  420286289,  415065409,  409909383,
		404817407,  399788685,  394822430,  389917867,  385074229,  380290760,  375566713,  370901348,
		366293938,  361743761,  357250108,  352812276,  348429571,  344101310,  339826815,  335605418,
		331436461,  327319291,  323253265,  319237749,  315272114,  311355741,  307488017,  303668340,
		299896111,  296170742,  292491650,  288858260,  285270005,  281726324,  278226664,  274770477,
		271357223,  267986369,  264657389,  261369762,  258122975,  254916520,  251749896,  248622609,
		245534169,  242484094,  239471909,  236497141,  233559326,  230658006,  227792726,  224963039,
		222168503,  219408682,  216683144,  213991462,  211333218,  208707994,  206115382,  203554975,
		201026375,  198529185,  196063016,  193627482,  191222203,  188846803,  186500910,  184184158,
		181896186,  179636635,  177405153,  175201391,  173025004,  170875653,  168753002,  166656718,
		164586475,  162541949,  160522821,  158528774,  156559498,  154614685,  152694030,  150797235,
		148924001,  147074038,  145247055,  143442767,  141660892,  139901152,  138163272,  136446980,
		134752009,  133078092,  131424970,  129792383,  128180076,  126587797,  125015298,  123462333,
		121928660,  120414037,  118918230,  117441004,  115982129,  114541376,  113118520,  111713339,
		110325614,  108955127,  107601664,  106265015,  104944970,  103641322,  102353869,  101082409,
		99826743,  98586675,  97362012,  96152562,  94958135,  93778547,  92613611,  91463146,
		90326973,  89204913,  88096792,  87002436,  85921674,  84854338,  83800260,  82759277,
		81731225,  80715943,  79713273,  78723059,  77745146,  76779380,  75825611,  74883690,
		73953470,  73034805,  72127552,  71231570,  70346717,  69472856,  68609850,  67757565,
		66915867,  66084625,  65263708,  64452989,  63652342,  62861639,  62080760,  61309580,
		60547980,  59795841,  59053045,  58319477,  57595020,  56879564,  56172994,  55475202,
		54786078,  54105514,  53433405,  52769645,  52114129,  51466757,  50827427,  50196039,
		49572493,  48956694,  48348544,  47747949,  47154814,  46569048,  45990558,  45419254,
		44855047,  44297849,  43747572,  43204131,  42667440,  42137417,  41613978,  41097040,
		40586525,  40082351,  39584440,  39092714,  38607097,  38127511,  37653884,  37186140,
		36724206,  36268011,  35817482,  35372550,  34933145,  34499199,  34070643,  33647411,
		33229436,  32816653,  32408998,  32006407,  31608817,  31216166,  30828393,  30445436,
		30067237,  29693736,  29324874,  28960595,  28600840,  28245555,  27894683,  27548170,
		27205961,  26868003,  26534243,  26204630,  25879111,  25557635,  25240153,  24926615,
		24616971,  24311174,  24009176,  23710929,  23416388,  23125504,  22838235,  22554534,
		22274357,  21997660,  21724401,  21454536,  21188024,  20924822,  20664889,  20408186,
		20154671,  19904306,  19657051,  19412867,  19171717,  18933562,  18698365,  18466090,
		18236701,  18010161,  17786435,  17565488,  17347286,  17131795,  16918980,  16708809,
		16501249,  16296267,  16093832,  15893911,  15696474,  15501489,  15308926,  15118756,
		14930948,  14745473,  14562301,  14381405,  14202757,  14026327,  13852089,  13680016,
		13510080,  13342255,  13176515,  13012834,  12851186,  12691546,  12533889,  12378190,
		12224426,  12072572,  11922604,  11774499,  11628234,  11483785,  11341132,  11200250,
		11061118,  10923715,  10788018,  10654007,  10521661,  10390959,  10261880,  10134405,
		10008513,  9884186,  9761402,  9640144,  9520392,  9402128,  9285333,  9169989,
		9056077,  8943581,  8832482,  8722763,  8614407,  8507397,  8401717,  8297349,
		8194278,  8092487,  7991960,  7892682,  7794638,  7697811,  7602188,  7507752,
		7414489,  7322385,  7231425,  7141594,  7052880,  6965268,  6878744,  6793295,
		6708907,  6625568,  6543263,  6461982,  6381710,  6302435,  6224145,  6146827,
		6070470,  5995061,  5920590,  5847043,  5774410,  5702679,  5631839,  5561879,
		5492788,  5424556,  5357171,  5290623,  5224902,  5159997,  5095899,  5032596,
		4970080,  4908341,  4847369,  4787154,  4727687,  4668958,  4610960,  4553681,
		4497115,  4441251,  4386081,  4331596,  4277788,  4224648,  4172169,  4120341,
		4069158,  4018610,  3968690,  3919390,  3870702,  3822620,  3775134,  3728239,
		3681926,  3636188,  3591019,  3546411,  3502356,  3458849,  3415883,  3373450,
		3331544,  3290159,  3249288,  3208925,  3169063,  3129696,  3090819,  3052424,
		3014506,  2977059,  2940078,  2903555,  2867487,  2831866,  2796688,  2761947,
		2727638,  2693754,  2660292,  2627245,  2594609,  2562378,  2530548,  2499113,
		2468069,  2437410,  2407132,  2377230,  2347699,  2318536,  2289735,  2261291,
		2233201,  2205460,  2178063,  2151007,  2124286,  2097898,  2071837,  2046101,
		2020684,  1995582,  1970793,  1946311,  1922134,  1898257,  1874676,  1851388,
		1828390,  1805677,  1783247,  1761095,  1739218,  1717614,  1696277,  1675205,
		1654396,  1633844,  1613549,  1593505,  1573710,  1554161,  1534855,  1515789,
		1496959,  1478364,  1459999,  1441863,  1423952,  1406263,  1388794,  1371542,
		1354505,  1337679,  1321062,  1304651,  1288445,  1272439,  1256633,  1241023,
		1225606,  1210382,  1195346,  1180497,  1165833,  1151351,  1137048,  1122924,
		1108974,  1095199,  1081594,  1068158,  1054889,  1041785,  1028844,  1016063,
		1003442,  990977,  978666,  966509,  954503,  942646,  930936,  919372,
		907951,  896673,  885534,  874534,  863670,  852941,  842346,  831882,
		821548,  811343,  801264,  791311,  781481,  771773,  762186,  752718,
		743368,  734133,  725014,  716008,  707113,  698329,  689654,  681087,
		672627,  664271,  656020,  647870,  639822,  631874,  624025,  616273,
		608618,  601057,  593591,  586217,  578935,  571744,  564641,  557627,
		550700,  543859,  537103,  530431,  523842,  517335,  510908,  504562,
		498294,  492104,  485991,  479954,  473992,  468104,  462289,  456546,
		450875,  445274,  439743,  434280,  428886,  423558,  418296,  413100,
		407969,  402901,  397896,  392953,  388072,  383251,  378490,  373788,
		369145,  364560,  360031,  355559,  351142,  346780,  342472,  338218,
		334016,  329867,  325769,  321723,  317726,  313779,  309881,  306032,
		302230,  298476,  294768,  291107,  287490,  283919,  280392,  276909,
		273469,  270072,  266717,  263404,  260132,  256901,  253709,  250558,
		247445,  244371,  241336,  238338,  235377,  232453,  229566,  226714,
		223898,  221116,  218370,  215657,  212978,  210332,  207720,  205139,
		202591,  200074,  197589,  195134,  192710,  190317,  187952,  185618,
		183312,  181035,  178786,  176565,  174372,  172205,  170066,  167954,
		165867,  163807,  161772,  159762,  157778,  155818,  153882,  151971,
		150083,  148219,  146377,  144559,  142763,  140990,  139238,  137509,
		135801,  134114,  132448,  130802,  129178,  127573,  125988,  124423,
		122877,  121351,  119844,  118355,  116885,  115433,  113999,  112583,
		111184,  109803,  108439,  107092,  105762,  104448,  103150,  101869,
		100603,  99354,  98120,  96901,  95697,  94508,  93334,  92175,
		91030,  89899,  88782,  87679,  86590,  85514,  84452,  83403,
		82367,  81344,  80333,  79335,  78350,  77377,  76415,  75466,
		74529,  73603,  72689,  71786,  70894,  70013,  69144,  68285,
		67436,  66599,  65771,  64954,  64147,  63351,  62564,  61786,
		61019,  60261,  59512,  58773,  58043,  57322,  56610,  55907,
		55212,  54526,  53849,  53180,  52519,  51867,  51223,  50586,
		49958,  49337,  48724,  48119,  47521,  46931,  46348,  45772,
		45204,  44642,  44088,  43540,  42999,  42465,  41937,  41416,
		40902,  40394,  39892,  39397,  38907,  38424,  37947,  37475,
		37010,  36550,  36096,  35647,  35205,  34767,  34335,  33909,
		33488,  33072,  32661,  32255,  31854,  31459,  31068,  30682,
		30301,  29924,  29553,  29186,  28823,  28465,  28111,  27762,
		27417,  27077,  26740,  26408,  26080,  25756,  25436,  25120,
		24808,  24500,  24196,  23895,  23598,  23305,  23016,  22730,
		22447,  22168,  21893,  21621,  21352,  21087,  20825,  20567,
		20311,  20059,  19810,  19564,  19320,  19080,  18843,  18609,
		18378,  18150,  17924,  17702,  17482,  17265,  17050,  16838,
		16629,  16423,  16219,  16017,  15818,  15622,  15428,  15236,
		15047,  14860,  14675,  14493,  14313,  14135,  13959,  13786,
		13615,  13446,  13279,  13114,  12951,  12790,  12631,  12474,
		12319,  12166,  12015,  11866,  11718,  11573,  11429,  11287,
		11147,  11008,  10872,  10736,  10603,  10471,  10341,  10213,
		10086,  9961,  9837,  9715,  9594,  9475,  9357,  9241,
		9126,  9013,  8901,  8790,  8681,  8573,  8467,  8361,
		8258,  8155,  8054,  7954,  7855,  7757,  7661,  7566,
		7472,  7379,  7287,  7197,  7107,  7019,  6932,  6846,
		6761,  6677,  6594,  6512,  6431,  6351,  6272,  6194,
		6117,  6041,  5966,  5892,  5819,  5747,  5675,  5605,
		5535,  5466,  5398,  5331,  5265,  5200,  5135,  5071,
		5008,  4946,  4885,  4824,  4764,  4705,  4646,  4589,
		4532,  4475,  4420,  4365,  4311,  4257,  4204,  4152,
		4100,  4049,  3999,  3949,  3900,  3852,  3804,  3757,
		3710,  3664,  3618,  3574,  3529,  3485,  3442,  3399,
		3357,  3315,  3274,  3233,  3193,  3154,  3114,  3076,
		3037,  3000,  2962,  2926,  2889,  2853,  2818,  2783,
		2748,  2714,  2681,  2647,  2614,  2582,  2550,  2518,
		2487,  2456,  2425,  2395,  2365,  2336,  2307,  2278,
		2250,  2222,  2195,  2167,  2140,  2114,  2087,  2062,
		2036,  2011,  1986,  1961,  1937,  1913,  1889,  1865,
		1842,  1819,  1797,  1774,  1752,  1730,  1709,  1688,
		1667,  1646,  1626,  1605,  1585,  1566,  1546,  1527,
		1508,  1489,  1471,  1453,  1435,  1417,  1399,  1382,
		1365,  1348,  1331,  1314,  1298,  1282,  1266,  1250
};

#endif /* PROJ_ADSR_V0_18_ADSR_DIVIDERS_H_ */
