/* Private includes ----------------------------------------------------------*/
#include "ntc.h"

/* Private Varibles ----------------------------------------------------------*/
const uint16_t NTC_Lookup_Table[210]={
3974,  // -40C
3967,
3961,
3954,
3946,
3938,
3929,
3918,
3906,
3893,
3877,
3868,
3857,
3845,
3832,
3818,
3802,
3784,
3764,
3741,
3714,
3699,
3682,
3664,
3644,
3622,
3598,
3571,
3541,
3508,
3471,
3448,
3424,
3398,
3370,
3339,
3306,
3270,
3230,
3186,
3137,
3082,
3045,
3007,
2965,
2919,
2882,
2841,
2798,
2752,
2703,
2664,
2622,
2578,
2531,
2481,
2441,
2399,
2355,
2308,
2259,
2217,
2174,
2128,
2080,
2028,
1989,
1947,
1903,
1857,
1809,
1770,
1730,
1689,
1646,
1601,
1564,
1527,
1488,
1448,
1406,
1372,
1337,
1301,
1264,
1226,
1196,
1165,
1133,
1100,
1059,
1039,
1011,
983,
954,
924,
900,
875,
851,
825,
800,
778,
757,
735,
713,
691,
672,
653,
635,
615,
596,
580,
564,
548,
532,
501,
487,
473,
459,
445,
431,
419,
408,
396,
384,
373,
363,
352,
343,
333,
322,
314,
305,
297,
288,
279,
272,
265,
257,
250,
243,
236,
230,
223,
217,
211,
205,
200,
195,
189,
184,
179,
174,
170,
165,
160,
156,
152,
149,
145,
141,
137,
134,
130,
127,
123,
120,
117,
114,
111,
108,
106,
103,
100,
97,
95,
93,
90,
88,
86,
84,
82,
80,
78,
76,
74,
73,
71,
69,
68,
66,
64,
63,
62,
60,
59,
58,
56,
55,
53,
52,
51,
50,
49,
48,
47,
46,
45,
44,
42 // 169C
};

/* External Varibles ---------------------------------------------------------*/
extern ADC_HandleTypeDef NTC_ADC;

/* Private function prototypes -----------------------------------------------*/
static uint16_t  Get_NTC_ADC(void);

/* function Definition -------------------------------------------------------*/

static uint16_t Get_NTC_ADC(void)
{
	uint16_t ADC_Val = 0;
	uint32_t sum = 0;
	uint8_t Sample_Cnt = 0;
	
	HAL_ADC_Start(&NTC_ADC);
	
		for(uint8_t i=0; i<10; i++)  
			{
				if(HAL_ADC_PollForConversion(&NTC_ADC,1) == HAL_OK)
					{
						sum += HAL_ADC_GetValue(&NTC_ADC);
						Sample_Cnt++;
					}
			}
	if(Sample_Cnt > 0)ADC_Val = (uint16_t)(sum/Sample_Cnt);
	
	return ADC_Val;
	
}

int16_t Get_NTC_Temp(void)
{
	int16_t  Temp = 0;
	uint16_t ADC_Val = 0;
	int16_t Temp_Index = 0;
	
	ADC_Val = Get_NTC_ADC();
	
	while( (ADC_Val < NTC_Lookup_Table[Temp_Index]) && (Temp_Index < 210) )
	{
		Temp_Index++;
	}
	
	Temp = Temp_Index - 40;
	
	return Temp;
}