// aplphabet definition

enum{ PD, PU, FW, TR, TL };

byte letter_A[][2]={
  {TR,17}, {PD,0}, {FW,42}, {TR,146},
  {FW,42}, {PU,0}, {TR,180}, {FW,12},
  {TL,72}, {PD,0}, {FW,17}, {PU,0}, {TL,72},
  {FW,12}, {TL,108}, {FW,30}, {TL,90}
};

byte letter_B[][2]={
  {PD,0}, {FW,40}, {TR,90},
  {FW,20}, {TR,45}, {FW,7},
  {TR,45}, {FW,10}, {TR,45},
  {FW,7}, {TL,90}, {FW,7}, {TR,45},
  {FW,10}, {TR,45}, {FW,7}, {TR,45}, {FW,20},
  {PU,0}, {TR,90}, {FW,20}, {TR,90}, {PD,0}, {FW,20}, {PU, 0},
  {TR,90}, {FW,20}, {TL,90}, {FW,10}, {TL,90}
};

byte letter_C[][2]={
	{FW,5}, {PD,0}, {FW,30}, {TR,45}, {FW,7,}, {TR,45}, {FW,20},
	{PU,0}, {TR,90}, {FW,40,}, {TR,90}, {PD,0}, {FW,20,}, {TR,45},
	{FW,7}, {PU,0,}, {TR,180,}, {FW,7}, {TL,45,}, {FW,25}, {TL,90}
};

byte letter_E[][2]={
  {PD,0}, {FW,40}, {TR,90},
  {FW,20}, {PU, 0}, {TR,90}, {FW,20},
  {TR,90}, {PD,0}, {FW,20}, {PU, 0}, {TL,90},
  {FW,20}, {TL,90}, {PD,0}, {FW,20}, {PU, 0},
  {FW,5}, {TL,90}
};
