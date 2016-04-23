// aplphabet definition

enum{ PD, PU, FW, TR, TL };
/*
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
	{FW,5}, {PD,0},  {FW,30},   {TR,45}, {FW,7,}, {TR,45},  {FW,20},
	{PU,0}, {TR,90}, {FW,40,},  {TR,90}, {PD,0},  {FW,20,}, {TR,45},
	{FW,7}, {PU,0,}, {TR,180,}, {FW,7},  {TL,45}, {FW,25},  {TL,90}
};

byte letter_D[][2]={
	{PD,0}, {FW,40}, {TR,90}, {FW,20}, {TR,45}, {FW,7}, {TR,45},
	{FW,30}, {TR,45}, {FW,7}, {TR,45}, {FW,20}, {PU,0}, {TR,180},
	{FW,30}, {TL,90}
};

byte letter_E[][2]={
  {PD,0},  {FW,40}, {TR,90}, {FW,25}, {PU, 0},
  {TR,90}, {FW,20}, {TR,90}, {PD,0},  {FW,25},
  {PU, 0}, {TL,90}, {FW,20}, {TL,90}, {PD,0},
  {FW,25}, {PU, 0}, {FW,5},  {TL,90}
}; //19 cdes

byte letter_F[][2]={
  {PD,0}, {FW,40}, {TR,90},
  {FW,25}, {PU, 0}, {TR,90}, {FW,20},
  {TR,90}, {PD,0}, {FW,25}, {PU, 0}, {TL,90},
  {FW,20}, {TL,90},
  {FW,30}, {TL,90}
};

byte letter_G[][2]={
	{TR,90}, {FW,12}, {TL,90}, {FW,20}, {TR,90},
	{PD,0},  {FW,8},  {TR,45}, {FW,7},  {TR,45},
	{FW,10}, {TR,45}, {FW,7},  {TR,45}, {FW,15}, {TR,45}, {FW,7},
	{TR,45}, {FW,30}, {TR,45}, {FW,7},  {TR,45},
	{FW,20}, {PU,0},  {TR,90}, {FW,40}, {TL,90},
	{FW,5}, {TL,90}
}; //29 cdes

byte letter_H[][2]={
	{PD,0}, {FW,40}, {PU,0}, {TR,180}, {FW,20},
	{TL,90}, {PD,0}, {FW,25}, {PU,0},  {TL,90},
	{FW,20}, {TR,180}, {PD,0}, {FW,40}, {PU,0},
	{TL,90}, {FW,5}, {TL,90}
}; //18 cdes

byte letter_I[][2]={
	{TR,90}, {FW,12}, {TL,90}, {PD,0}, {FW,40},
	{PU,0}, {TR,180}, {FW,40}, {TL,90}, {FW,18},
	{TL,90}
}; //11 cdes

byte letter_J[][2]={
	{FW,40}, {TR,90}, {FW,12}, {PD,0}, {FW,13},
	{TR,90}, {FW,35}, {TR,45}, {FW,7}, {TR,45},
	{FW,15}, {TR,45}, {FW,7}, {TR,45}, {FW,10}, {PU,0},
	{TL,180}, {FW,15}, {TL,90}, {FW,30}, {TL,90}
}; //21 cdes

byte letter_K[][2]={
	{PD,0}, {FW,40}, {PU,0}, {TL,180}, {FW,20},
	{TL,129}, {PD,0}, {FW,32}, {PU,0}, {TL,180},
	{FW,32}, {TL,102}, {PD,0}, {FW,32}, {PU,0},
	{TL,39}, {FW,5}, {TL,90}
}; //18 cdes

byte letter_L[][2]={
	{PD,0},  {FW,40}, {PU,0},  {TL,180}, {FW,40},
	{TL,90}, {PD,0},  {FW,25}, {PU,0},   {FW,5},
	{TL,90}
}; //11 cdes


byte letter_M[][2]={
	{PD,0},  {FW,40},  {TR,140}, {FW,19}, {TL,100},
	{FW,19}, {TR,140}, {FW,40},  {PU,0},  {TL,90},
	{FW,5},  {TL,90}
}; //12 cdes

byte letter_N[][2]={
	{PD,0}, {FW,40}, {TR,148,}, {FW,47}, {TL,148},
	{FW,40}, {PU,0}, {TL,180}, {FW,40}, {TL,90},
	{FW,5}, {TL,90}
}; //17 cdes

byte letter_O[][2]={
	{FW,5}, {PD,0}, {FW,30}, {TR,45}, {FW,7},
	{TR,45}, {FW,15}, {TR,45}, {FW,7}, {TR,45},
	{FW,30}, {TR,45}, {FW,7}, {TR,45}, {FW,15},
	{TR,45}, {FW,7}, {TR,45}, {PU,0}, {TL,180},
	{FW,5}, {TL,90}, {FW,30}, {TL,90}
}; //19 cdes

byte letter_P[][2]={
	{PD,0}, {FW,40}, {TR,90}, {FW,20,}, {TR,45},
	{FW,7}, {TR,45}, {FW,15,}, {TR,45}, {FW,7},
	{TR,45}, {FW,20}, {PU,0}, {TL,90}, {FW,20},
	{TL,90}, {FW,30}, {TL,90}
}; //18 cdes

byte letter_Q[][2]={
	{FW,5}, {PD,0}, {FW,30}, {TR,45}, {FW,7},
	{TR,45}, {FW,15}, {TR,45}, {FW,7}, {TR,45},
	{FW,30}, {TR,45}, {FW,7}, {TR,45}, {FW,15},
	{TR,45}, {FW,7}, {TR,45}, {PU,0}, {TL,180},
	{FW,5}, {TL,90}, {FW,20}, {TL,90}, {FW,5},
	{TR,135}, {PD,0}, {FW,7}, {PU,0}, {TL,45},
	{FW,5}, {TL,90}
}; //32 cdes

byte letter_R[][2]={
	{PD,0}, {FW,40}, {TR,90}, {FW,20,}, {TR,45},
	{FW,7}, {TR,45}, {FW,10}, {TR,45}, {FW,7},
	{TR,45}, {FW,20}, {TL,141}, {FW,29}, {PU,0},
	{TL,39}, {FW,5},  {TL,90}
}; //18 cdes

byte letter_S[][2]={
	{TR,90}, {PD,0}, {FW,20}, {TL,45}, {FW,7},
	{TL,45}, {FW,10}, {TL,45}, {FW,7}, {TL,45},
	{FW,15}, {TR,45}, {FW,7}, {TR,45}, {FW,10},
	{TR,45}, {FW,7}, {TR,45}, {FW,20}, {PU,0},
	{TR,90}, {FW,40}, {TL,90}, {FW,5}, {TL,90}
}; //25 cdes

byte letter_T[][2]={
	{FW,40}, {TR,90}, {PD,0},  {FW,25}, {PU,0},
	{TL,180}, {FW,13}, {TL,90}, {PD,0},  {FW,40},
	{PU,0},   {TL,90}, {FW,18}, {TL,90}
}; //14 cdes

byte letter_U[][2]={
	{FW,40}, {TL,180}, {PD,0}, {FW,35}, {TL,45},
	{FW,7}, {TL,45}, {FW,15}, {TL,45}, {FW,7},
	{TL,45}, {FW,35}, {PU,0}, {TR,180}, {FW,40},
	{TL,90}, {FW,5}, {TL,90}
}; //18 cdes

byte letter_V[][2]={
	{FW,40}, {TR,163}, {PD,0}, {FW,42}, {TL,147},
	{FW,42}, {PU,0}, {TR,163}, {FW,40}, {TL,90},
	{FW,5}, {TL,90}
}; //17 cdes

byte letter_W[][2]={
	{FW,40}, {TR,173}, {PD,0}, {FW,41}, {TL,153},
	{FW,21}, {TR,140}, {FW,21}, {TL,153}, {FW,41},
	{PU,0}, {TR,173}, {FW,40}, {TL,90}, {FW,5},
	{TL,90}
}; //16 cdes

byte letter_X[][2]={
	{FW,40}, {TR,148}, {PD,0}, {FW,47}, {PU,0},
	{TL,148}, {FW,40}, {TL,148}, {PD,0}, {FW,47},
	{PU,0}, {TL,122}, {FW,30}, {TL,90}
}; //14 cdes

byte letter_Y[][2]={
	{TR,90}, {FW,12}, {TL,90}, {PD,0}, {FW,20},
	{TL,30}, {FW,21}, {PU,0}, {TL,180}, {FW,21},
	{TL,120}, {PD,0}, {FW,21}, {PU,0}, {TR,180},
	{FW,21}, {TL,30}, {FW,20}, {TL,90}, {FW,18},
	{TL,90}
}; //21 cdes

byte letter_Z[][2]={
	{FW,40}, {TR,90}, {PD,0}, {FW,25}, {TR,122},
	{FW,47}, {TL,122}, {FW,25}, {PU,0}, {FW,5},
	{TL,90}
}; //11 cdes
*/
