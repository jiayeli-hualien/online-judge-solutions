#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int main()
{
    int hour, minute;
    while(scanf("%d:%d",&hour,&minute)!=EOF)
    {
        if(hour==0&&minute==0)
            break;
        double angleH , angleM;
        angleH = 0.5*minute + hour*30;
        angleM = minute*6;
        double ans = angleH-angleM;

        if(ans < 0)
            ans = -ans;
        if(ans > 180.0)
        {
            ans = 360-ans;
        }

        printf("%.3f\n",ans);
    }
}
