int GETX (int t)
{
int x;

x=V_inix * t;

return x;
}

int GETY (int t)
{
int y;

y= V_iniy * t - ( ( 9.8 ) * t^2 ) / 2;

return y;
}