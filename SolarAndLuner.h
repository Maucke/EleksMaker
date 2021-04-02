//下面是具体的代码项目中采用过的，可以直接集成.h

#ifndef SolarAndLuner_h
#define SolarAndLuner_h
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int year;
    int month;
    int day;
    int reserved;
} Mydate;

Mydate toSolar(Mydate lunar);
Mydate toLunar(Mydate solar);

#ifdef __cplusplus
}
#endif
#endif
